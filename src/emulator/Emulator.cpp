#include <iostream>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"

Emulator::Emulator(App *app, GraphicsEngine *graphics) :
  mCartridgeMem(0),
  mApp(app),
  mGraphics(graphics),
  mPause(true),
  mCyclesCounter(0),
  mOpCounter(0)
{
  std::cout << "Emulator created" << std::endl;
  mDIVCounter = DIV_NBCYCLE_TO_UPDATE;
  mTIMACounter = 1024;
  mLYCounter = 456;
  mMasterIntFlag = true;
}

Emulator::~Emulator()
{
  if (mCartridgeMem)
    delete[] mCartridgeMem;
  std::cout << "Emulator deleted" << std::endl;
}

void	Emulator::DoFrame()
{
  int	nbCycles = 0;
  int	curCycles;

  if (mPause)
    return ;
  while (nbCycles < CYCLE_BY_FRAME)
    {
      curCycles = DoOpcode();
      UpdateLCD(nbCycles);
      UpdateTimer(nbCycles);
      HandleInterupt();
      nbCycles += curCycles;

      // DEBUG //
      mCyclesCounter += curCycles;
      mOpCounter++;
      if (mPause)
	break ;
    }
}

void	Emulator::UpdateTimer(int nbCycles)
{
  mDIVCounter -= nbCycles;
  if (mDIVCounter <= 0)
    {
      mIOPorts[DIV]++;
      mDIVCounter = DIV_NBCYCLE_TO_UPDATE;
    }

  if (IS_BIT_SET(mIOPorts[TAC], 2)) // Clock on
    {
      mTIMACounter -= nbCycles;
      if (mTIMACounter <= 0)
	{
	  if (mIOPorts[TIMA] == 0xFF) // Overflow
	    {
	      mIOPorts[TIMA] = mIOPorts[TMA];
	      REQ_INT(TIMER);
	    }
	  else
	    mIOPorts[TIMA]++;
	  switch (mIOPorts[TAC] & 0x03) // 3 = 11
	    {
	    case 0: mTIMACounter = 1024; break; // 69905 / (4194Hz / 60)
	    case 1: mTIMACounter = 16; break; // 69905 / (268400Hz / 60)
	    case 2: mTIMACounter = 64; break; // 69905 / (65536Hz / 60)
	    case 3: mTIMACounter = 256; break; // 69905 / (16384Hz / 60)
	    }
	}
    }
}

void	Emulator::HandleInterupt()
{
  std::cout << mMasterIntFlag << std::endl;
  if (!mMasterIntFlag)
    return ;

  BYTE regIntEnable = mInterrupEnable;
  BYTE regIntReq = mIOPorts[0x0F];

  for (int i = 0; i < 5; i++)
    {
      if (IS_BIT_SET(regIntReq, i) && IS_BIT_SET(regIntEnable, i))
	{
	  std::cout << "Interrupt handle " << i << std::endl;
	  printf("PC : %X\n", mPC);
	  Push(mPC);
	  switch (i)
	    {
	    case 0: mPC = 0x40; break;
	    case 1: mPC = 0x48; break;
	    case 2: mPC = 0x50; break;
	    case 3: mPC = 0x58; break;
	    case 4: mPC = 0x60; break;
	    }
	  RESET_BIT(regIntReq, i);
	  mMasterIntFlag = false;
	}
    }
}


void	Emulator::Play()
{
  mPause = false;
}

void	Emulator::Pause()
{
  mPause = true;
}

BYTE	Emulator::ReadMem(WORD addr)
{
  if (addr <= 0x3FFF) // ROM Bank 00
    return mCartridgeMem[addr];
  else if (addr <= 0x7FFF) // ROM bank 01..NN
    return mCartridgeMem[SIZE_BANK * mCurROMBank + (addr - 0x4000)];
  else if (addr <= 0x9FFF) // VRAM
    return mVRAM[addr - 0x8000];
  else if (addr <= 0xBFFF) // ExtRAM
    return mExtRAM[SIZE_BANK * mCurRAMBank + (addr - 0xA000)];
  else if (addr <= 0xDFFF) // RAM BANK 0 and 1
    return mWRAM[addr - 0xC000];
  else if (addr <= 0xFDFF) // ECHO
    return mWRAM[addr - 0xE000];
  else if (addr <= 0xFE9F) // OAM Sprite attribute table
    return mOAM[addr - 0xFE00];
  else if (addr <= 0xFEFF)
    return 0x0;
  else if (addr <= 0xFF7F) // I/O ports
    return mIOPorts[addr - 0xFF00];
  else if (addr != 0xFFFF) // HRAM
    return mHRAM[addr - 0xFF80];
  else // Interrupt
    return mInterrupEnable;
}


inline void ChangeROMBankLo(BYTE value, BYTE &curROMBank, BYTE cardType)
{
  if (cardType == MCB1)
    {
      curROMBank &= 0xE0; // 11100000
      curROMBank |= (value & 0x1F); // 00011111
      if (curROMBank == 0 || curROMBank == 0x20 ||
	  curROMBank == 0x40 || curROMBank == 0x60)
	curROMBank++;
    }
}

inline void ChangeROMBankHi(BYTE value, BYTE &curROMBank)
{
  curROMBank &= 0x1F; // 00011111
  value &= 0xE0; // 11100000
  curROMBank |= value;
  if (curROMBank == 0x0) // Wtf if 0x20 0x40 0x60 ?
    curROMBank = 0x1;
}

void	Emulator::WriteMem(WORD addr, BYTE value)
{
  if (addr <= 0x1FFF)
    {
      if (mInfos.CartridgeType == MCB1)
	mRAMEnable = ((value & 0xF) == 0xA);
    }
  else if (addr <= 0x7FFF)
    {
      ChangeROMBankLo(value, mCurROMBank, mInfos.CartridgeType);
    }
  else if (addr <= 0x5FFF)
    {
      if (mMode == ROM)
	ChangeROMBankHi(value, mCurROMBank);
      else
	mCurRAMBank = value & 0x3;
    }
  else if (addr <= 0x7FFF)
    {
      mMode = (value & 0x1) ? ROM : RAM;
      if (mMode == ROM)
	mCurRAMBank = 0;
    }
  else if (addr <= 0x9FFF) // VRAM
    mVRAM[addr - 0x8000] = value;
  else if (addr <= 0xBFFF) // ExtRAM
    mExtRAM[SIZE_BANK * mCurRAMBank + (addr - 0xA000)] = value;
  else if (addr <= 0xDFFF) // RAM BANK 0 and 1
    mWRAM[addr - 0xC000] = value;
  else if (addr <= 0xFDFF) // ECHO
    mWRAM[addr - 0xE000] = value;
  else if (addr <= 0xFE9F) // OAM Sprite attribute table
    mOAM[addr - 0xFE00] = value;
  else if (addr <= 0xFEFF)
    return ;
  else if (addr <= 0xFF7F) // I/O ports
    {
      if (addr == 0xFF04)
	mIOPorts[0x04] = 0;
      else
	mIOPorts[addr - 0xFF00] = value;
    }
  else if (addr != 0xFFFF) // HRAM
    mHRAM[addr - 0xFF80] = value;
  else // Interrupt
    mInterrupEnable = value;
}
