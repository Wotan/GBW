#include <iostream>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"

Emulator::Emulator(App *app) :
  mCartridgeMem(0),
  mApp(app)
{
  std::cout << "Emulator created" << std::endl;
}

Emulator::~Emulator()
{
  if (mCartridgeMem)
    delete[] mCartridgeMem;
  std::cout << "Emulator deleted" << std::endl;
}

bool	Emulator::Init(const char *fileName)
{
  InitMem();
  InitReg();
  if (!LoadFile(fileName))
    {
      std::cerr << "Fail to open file " << fileName << std::endl;
      return false;
    }
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

  strcpy(mInfos.Title, (const char *)&mCartridgeMem[0x134]);
  std::cout << "Title : " << mInfos.Title << std::endl;
  return true;
}

void	Emulator::InitMem()
{
  // All mem to 0 for avoid random effects

  mCartridgeMem = new BYTE[MAX_SIZE_CARTRIDGE];
  for (int i = 0; i < MAX_SIZE_CARTRIDGE; i++)
    mCartridgeMem[i] = 0;

  for (int i = 0; i < 0x2000 * 4; i++)
    mExtRAM[i] = 0;

  for (int i = 0; i < 0x1000; i++)
    mWRAM1[i] = 0;

  for (int i = 0; i < 0x1000; i++)
    mWRAM2[i] = 0;

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
