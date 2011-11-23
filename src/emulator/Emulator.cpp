#include <iostream>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"

Emulator::Emulator(App *app) :
  mCartridgeMem(0),
  mApp(app),
  mPause(true)
{
  std::cout << "Emulator created" << std::endl;
  mDIVCounter = DIV_NBCYCLE_TO_UPDATE;
  mTIMACounter = 1024;
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
      // UpdateScreen()
      UpdateTimer(nbCycles);
      // HandleInterupt()
      nbCycles += curCycles;
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
	    mIOPorts[TIMA] = mIOPorts[TMA];
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
    return mExtRAM[SIZE_BANK * mCurRAMBank + (addr - 0x8000)];
  else if (addr <= 0xDFFF) // RAM BANK 0 and 1
    return mWRAM[addr - 0xD000];
  else if (addr <= 0xFDFF) // ECHO
    return mWRAM[addr - 0xE000];
  else if (addr <= 0xFEFF) // Not used
    return 0x00;
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
    mExtRAM[SIZE_BANK * mCurRAMBank + (addr - 0x8000)] = value;
  else if (addr <= 0xDFFF) // RAM BANK 0 and 1
    mWRAM[addr - 0xD000] = value;
  else if (addr <= 0xFDFF) // ECHO
    mWRAM[addr - 0xE000] = value;
  else if (addr <= 0xFEFF); // Not used
  else if (addr <= 0xFF7F) // I/O ports
    mIOPorts[addr - 0xFF00] = value;
  else if (addr != 0xFFFF) // HRAM
    mHRAM[addr - 0xFF80] = value;
  else // Interrupt
    mInterrupEnable = value;
}
