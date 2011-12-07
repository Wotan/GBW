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
  Play();
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
  mIOPorts[0x05] = 0x00;
  mIOPorts[0x06] = 0x00;
  mIOPorts[0x07] = 0x00;
  mIOPorts[0x10] = 0x80;
  mIOPorts[0x11] = 0xBF;
  mIOPorts[0x12] = 0xF3;
  mIOPorts[0x14] = 0xBF;
  mIOPorts[0x16] = 0x3F;
  mIOPorts[0x17] = 0x00;
  mIOPorts[0x19] = 0xBF;
  mIOPorts[0x1A] = 0x7F;
  mIOPorts[0x1B] = 0xFF;
  mIOPorts[0x1C] = 0x9F;
  mIOPorts[0x1E] = 0xBF;
  mIOPorts[0x20] = 0xFF;
  mIOPorts[0x21] = 0x00;
  mIOPorts[0x22] = 0x00;
  mIOPorts[0x23] = 0xBF;
  mIOPorts[0x24] = 0x77;
  mIOPorts[0x25] = 0xF3;
  mIOPorts[0x26] = 0xF1;
  mIOPorts[0x40] = 0x91;
  mIOPorts[0x42] = 0x00;
  mIOPorts[0x43] = 0x00;
  mIOPorts[0x45] = 0x00;
  mIOPorts[0x47] = 0xFC;
  mIOPorts[0x48] = 0xFF;
  mIOPorts[0x49] = 0xFF;
  mIOPorts[0x4A] = 0x00;
  mIOPorts[0x4B] = 0x00;

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
