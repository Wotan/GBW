#include <iostream>
#include <fstream>
#include "Emulator.hpp"

void	Emulator::SaveState(const char *fileName)
{
  std::ofstream file;

  file.open(fileName);
  file.write(mInfos.Title, 0xF);
  file.write((char *)&mDIVCounter, sizeof(mDIVCounter));
  file.write((char *)&mTIMACounter, sizeof(mTIMACounter));
  file.write((char *)&mMasterIntFlag, sizeof(mMasterIntFlag));
  file.write((char *)&mAF.a, sizeof(mAF.a));
  file.write((char *)&mBC.a, sizeof(mBC.a));
  file.write((char *)&mDE.a, sizeof(mDE.a));
  file.write((char *)&mHL.a, sizeof(mHL.a));
  file.write((char *)&mPC, sizeof(mPC));
  file.write((char *)&mSP, sizeof(mSP));
  file.write((char *)&mJoypadMask, sizeof(mJoypadMask));
  file.write((char *)&mLYCounter, sizeof(mLYCounter));
  file.write((char *)&mCurROMBank, sizeof(mCurROMBank));
  file.write((char *)&mMode, sizeof(mMode));
  file.write((char *)&mCurRAMBank, sizeof(mCurRAMBank));
  file.write((char *)&mRAMEnable, sizeof(mRAMEnable));
  file.write((char *)mVRAM, sizeof(mVRAM));
  file.write((char *)mExtRAM, sizeof(mExtRAM));
  file.write((char *)mWRAM, sizeof(mWRAM));
  file.write((char *)mOAM, sizeof(mOAM));
  file.write((char *)mIOPorts, sizeof(mIOPorts));
  file.write((char *)mHRAM, sizeof(mHRAM));
  file.write((char *)&mInterrupEnable, sizeof(mInterrupEnable));
  file.write((char *)&mIsHalted, sizeof(mIsHalted));
  file.write((char *)&mIsStop, sizeof(mIsStop));
  file.close();
}

bool	Emulator::LoadState(const char *fileName)
{
  std::ifstream file;
  char		Title[0xF];

  file.open(fileName);
  if (!file.is_open())
    return false;
  file.read(Title, 0xF);
  if (strncmp(Title, mInfos.Title, 0xF) != 0)
    {
      std::cerr << "Error : Save is from " << Title << std::endl;
      file.close();
      return false;
    }
  file.read((char *)&mDIVCounter, sizeof(mDIVCounter));
  file.read((char *)&mTIMACounter, sizeof(mTIMACounter));
  file.read((char *)&mMasterIntFlag, sizeof(mMasterIntFlag));
  file.read((char *)&mAF.a, sizeof(mAF.a));
  file.read((char *)&mBC.a, sizeof(mBC.a));
  file.read((char *)&mDE.a, sizeof(mDE.a));
  file.read((char *)&mHL.a, sizeof(mHL.a));
  file.read((char *)&mPC, sizeof(mPC));
  file.read((char *)&mSP, sizeof(mSP));
  file.read((char *)&mJoypadMask, sizeof(mJoypadMask));
  file.read((char *)&mLYCounter, sizeof(mLYCounter));
  file.read((char *)&mCurROMBank, sizeof(mCurROMBank));
  file.read((char *)&mMode, sizeof(mMode));
  file.read((char *)&mCurRAMBank, sizeof(mCurRAMBank));
  file.read((char *)&mRAMEnable, sizeof(mRAMEnable));
  file.read((char *)mVRAM, sizeof(mVRAM));
  file.read((char *)mExtRAM, sizeof(mExtRAM));
  file.read((char *)mWRAM, sizeof(mWRAM));
  file.read((char *)mOAM, sizeof(mOAM));
  file.read((char *)mIOPorts, sizeof(mIOPorts));
  file.read((char *)mHRAM, sizeof(mHRAM));
  file.read((char *)&mInterrupEnable, sizeof(mInterrupEnable));
  file.read((char *)&mIsHalted, sizeof(mIsHalted));
  file.read((char *)&mIsStop, sizeof(mIsStop));
  file.close();
  return true;
}

