#include <iostream>
#include <cmath>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"

bool	Emulator::Init(const char *fileName)
{
  InitMem();
  InitReg();
  if (!LoadFile(fileName))
    {
      std::cerr << "Fail to open file " << fileName << std::endl;
      return false;
    }
  mCurROMBank = 1;
  mCurRAMBank = 0;
  mRAMEnable = false;
  mMode = 0;
  return true;
}

bool	Emulator::LoadFile(const char *fileName)
{
  std::ifstream file;

  // Load file in cartdrige mem
  file.open(fileName, std::ifstream::in | std::ifstream::binary);
  if (!file.is_open())
    return false;
  file.read((char *)mCartridgeMem, MAX_SIZE_CARTRIDGE);
  file.close();
  ReadCartridgeInfos();

  std::cout << "File " << fileName <<
    " read, it seems to be valid" << std::endl;
  return true;
}

void	Emulator::ReadCartridgeInfos()
{
  strncpy(mInfos.Title, (const char *)&mCartridgeMem[0x134], 0xF);
  std::cout << "Title : " << mInfos.Title << std::endl;

  mInfos.CartridgeType = 0;
  BYTE ct = mCartridgeMem[0x147];
  if (ct == 0)
    {
      mInfos.CartridgeType = ONLY_ROM;
      std::cout << "ROM ONLY" << std::endl;
    }
  else if (ct >= 0x01 && ct <= 0x3)
    {
      mInfos.CartridgeType = MCB1;
      std::cout << "MCB1" << std::endl;
    }
  else if (ct == 0x08 || ct == 0x09)
    {
      mInfos.CartridgeType = MCB2;
      std::cout << "MCB2" << std::endl;
    }
  else if (ct >= 0x0F && ct <= 0x013)
    {
      mInfos.CartridgeType = MCB3;
      std::cout << "MCB3" << std::endl;
    }

  BYTE ramSize = mCartridgeMem[0x149];
  if (ramSize == 1)
    mInfos.ExtRAMSize = 2;
  else if (ramSize == 2)
    mInfos.ExtRAMSize = 8;
  else if (ramSize == 3)
    mInfos.ExtRAMSize = 32;
  else
    mInfos.ExtRAMSize = 0;
  std::cout << "Ram size : " << static_cast<int>(ramSize) << std::endl;

  BYTE romBanks = mCartridgeMem[0x148];
  if (romBanks <= 6)
    mInfos.ROMBanks = pow(2, romBanks + 1);
  else if (romBanks == 0x52)
    mInfos.ROMBanks = 72;
  else if (romBanks == 0x53)
    mInfos.ROMBanks = 80;
  else if (romBanks == 0x54)
    mInfos.ROMBanks = 96;
  else
    std::cerr << "Unknown ROM Bank value" << std::endl;
  std::cout << "ROM Banks : " << static_cast<int>(mInfos.ROMBanks) << std::endl;
}

void	Emulator::InitMem()
{
  // All mem to 0 for avoid random effects

  mCartridgeMem = new BYTE[MAX_SIZE_CARTRIDGE];
  for (int i = 0; i < MAX_SIZE_CARTRIDGE; i++)
    mCartridgeMem[i] = 0;

  for (int i = 0; i < 0x2000 * 4; i++)
    mExtRAM[i] = 0;

  for (int i = 0; i < 0x2000; i++)
    mVRAM[i] = 0;

  for (int i = 0; i < 0x1000; i++)
    mWRAM[i] = 0;

  for (int i = 0; i < 0x100; i++)
    mOAM[i] = 0;

  for (int i = 0; i < 0x80; i++)
    mIOPorts[i] = 0;

  for (int i = 0; i < 0x7F; i++)
    mHRAM[i] = 0;

  // Init I/O ports (0xFF00)
  mIOPorts[0xFF05 - 0xFF00] = 0x00;
  mIOPorts[0xFF06 - 0xFF00] = 0x00;
  mIOPorts[0xFF07 - 0xFF00] = 0x00;
  mIOPorts[0xFF10 - 0xFF00] = 0x80;
  mIOPorts[0xFF11 - 0xFF00] = 0xBF;
  mIOPorts[0xFF12 - 0xFF00] = 0xF3;
  mIOPorts[0xFF14 - 0xFF00] = 0xBF;
  mIOPorts[0xFF16 - 0xFF00] = 0x3F;
  mIOPorts[0xFF17 - 0xFF00] = 0x00;
  mIOPorts[0xFF19 - 0xFF00] = 0xBF;
  mIOPorts[0xFF1A - 0xFF00] = 0x7F;
  mIOPorts[0xFF1B - 0xFF00] = 0xFF;
  mIOPorts[0xFF1C - 0xFF00] = 0x9F;
  mIOPorts[0xFF1E - 0xFF00] = 0xBF;
  mIOPorts[0xFF20 - 0xFF00] = 0xFF;
  mIOPorts[0xFF21 - 0xFF00] = 0x00;
  mIOPorts[0xFF22 - 0xFF00] = 0x00;
  mIOPorts[0xFF23 - 0xFF00] = 0xBF;
  mIOPorts[0xFF24 - 0xFF00] = 0x77;
  mIOPorts[0xFF25 - 0xFF00] = 0xF3;
  mIOPorts[0xFF26 - 0xFF00] = 0xF1;
  mIOPorts[0xFF40 - 0xFF00] = 0x91;
  mIOPorts[0xFF42 - 0xFF00] = 0x00;
  mIOPorts[0xFF43 - 0xFF00] = 0x00;
  mIOPorts[0xFF45 - 0xFF00] = 0x00;
  mIOPorts[0xFF47 - 0xFF00] = 0xFC;
  mIOPorts[0xFF48 - 0xFF00] = 0xFF;
  mIOPorts[0xFF49 - 0xFF00] = 0xFF;
  mIOPorts[0xFF4A - 0xFF00] = 0x00;
  mIOPorts[0xFF4B - 0xFF00] = 0x00;

  // 0xFFFF
  mInterrupEnable = 0x00;
}

void	Emulator::InitReg()
{
  mAF.a = 0x01B0;
  mBC.a = 0x0013;
  mDE.a = 0x00D8;
  mHL.a = 0x014D;

  mSP = 0xFFFE;
  mPC = 0x100;
}
