#include <iostream>
#include <cmath>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"


void	Emulator::Halt()
{
  mIsHalted = true;
}

void	Emulator::Stop()
{
  mIsStop = true;
}

void	Emulator::ToggleInt(bool on)
{
  mMasterIntFlag = on;
}

void	Emulator::ToggleIntAfter(bool on)
{
  on = on;
}

void	Emulator::Load16bitHL()
{
  SBYTE tmp = (SBYTE)ReadMem(mPC++);
  WORD res;

  Z_F = 0;
  N_F = 0;
  H_F = 0;
  C_F = 0;
  if (tmp >= 0)
    {
    if (((tmp & 0xF) + (mSP & 0xF)) > 0xF)
      H_F = 1;
    if (mSP + tmp > 0xFFFF)
      C_F = 1;
    }
  else
    {
      if (((tmp & 0xF) + (mSP & 0xF)) < 0)
	H_F = 1;
      if (mSP + tmp < 0)
	C_F = 1;
    }
  res = mSP + tmp;
  REG_HL = res;
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



