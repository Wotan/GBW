#include <iostream>
#include <cmath>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"

void	Emulator::Load16bitHL()
{
  BYTE tmp = ReadMem(mPC++);
  WORD res;

  RESET_BIT(mAF.hi, F_Z);
  RESET_BIT(mAF.hi, F_N);
  if (((tmp + mSP) & 0xFF) > 0xFF)
    SET_BIT(mAF.hi, F_H);
  if (tmp + mSP > 0xFFF)
    SET_BIT(mAF.hi, F_C);
  res = tmp + mSP;
  mHL.a = res;
}

void	Emulator::Push(WORD value)
{
  WriteMem(mSP, value);
  mSP -= 2;
}

WORD	Emulator::Pop()
{
  UWORD tmp;

  tmp.lo = ReadMem(mPC++);
  tmp.hi = ReadMem(mPC++);
  mSP += 2;
  return tmp.a;
}

void	Emulator::ADD_8Bit(BYTE &toAdd, BYTE add, bool addCarry)
{
  // WORD	testh;
  // int	adding;

  // RESET_BIT(REG_F, F_N);

  // adding = add;
  // if (addCarry)
  //   adding += (IS_BIT_SET(REG_F, F_C) ? 1 : 0);

  // if ((toadd & 0xF) + (adding & 0xF)) > 0xF
  // if (adding + toAdd > 0xFF)
  //   SET_BIT(REG_F, F_C);

  // toAdd += add;

  // if (toAdd == 0)
  //   SET_BIT(REG_F, F_Z);
}
