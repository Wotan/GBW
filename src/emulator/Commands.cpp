#include <iostream>
#include <cmath>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"


void	Emulator::Halt()
{
  std::cout << "HALT" << std::endl;
  exit(0);
}

void	Emulator::Stop()
{
  std::cout << "STOP" << std::endl;
  exit(0);
}

void	Emulator::ToggleInt(bool on)
{
  mMasterIntFlag = on;
}

void	Emulator::ToggleIntAfter(bool on)
{

}

void	Emulator::Load16bitHL()
{
  BYTE tmp = ReadMem(mPC++);
  WORD res;

  Z_F = 0;
  N_F = 0;
  H_F = 0;
  C_F = 0;
  if (((tmp & 0xF) + (mSP & 0xF)) > 0xF)
    H_F = 1;
  if (tmp + mSP > 0xFFF)
    C_F = 1;
  res = tmp + mSP;
  mHL.a = res;
}

void	Emulator::Push(WORD value)
{
  UWORD tmp;

  tmp.a = value;
  WriteMem(mSP--, tmp.hi);
  WriteMem(mSP--, tmp.lo);
}

WORD	Emulator::Pop()
{
  UWORD tmp;

  mSP++;
  tmp.lo = ReadMem(mSP);
  mSP++;
  tmp.hi = ReadMem(mSP);
  return tmp.a;
}



