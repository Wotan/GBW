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

  if (((tmp & 0xFF) + (mSP & 0xFF)) > 0xFF)
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
  int	adding;

  RESET_BIT(REG_F, F_N);

  adding = add;
  if (addCarry)
    adding += (IS_BIT_SET(REG_F, F_C) ? 1 : 0);

  if (((toAdd & 0xF) + (adding & 0xF)) > 0xF)
    SET_BIT(REG_F, F_H);
  if (adding + toAdd > 0xFF)
    SET_BIT(REG_F, F_C);

  toAdd += adding;
  if (toAdd == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::SUB_8Bit(BYTE &toSub, BYTE sub, bool addCarry)
{
  int	nbSub;

  RESET_BIT(REG_F, F_N);

  nbSub = sub;
  if (addCarry)
    nbSub += (IS_BIT_SET(REG_F, F_C) ? 1 : 0);

  if (((toSub & 0xFF) >= (nbSub & 0xFF))) // >= or > ???
    SET_BIT(REG_F, F_H);

  if (toSub >= nbSub)
    SET_BIT(REG_F, F_C);
  toSub -= nbSub;
}

void	Emulator::AND_8Bit(BYTE &toAnd, BYTE src)
{
  RESET_BIT(REG_F, F_N);
  SET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);

  toAnd &= src;
  if (toAnd == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::OR_8Bit(BYTE &toOr, BYTE src)
{
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);

  toOr |= src;
  if (toOr == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::XOR_8Bit(BYTE &toXor, BYTE src)
{
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);

  toXor ^= src;
  if (toXor == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::CP_8Bit(BYTE cp1, BYTE cp2)
{
  SET_BIT(REG_F, F_N);

  if (cp1 == cp2)
    SET_BIT(REG_F, F_Z);
  if ((cp1 & 0xFF) < (cp2 & 0xFF))
    SET_BIT(REG_F, F_H);
  if (cp1 < cp2)
    SET_BIT(REG_F, F_C);
}

void	Emulator::INC_8Bit(BYTE &toInc)
{
  RESET_BIT(REG_F, F_N);
  if (!((toInc & 0xFF) + 1 > 0xF))
    SET_BIT(REG_F, F_H);
  toInc++;
  if (toInc == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::DEC_8Bit(BYTE &toDec)
{
  SET_BIT(REG_F, F_N);
  if (!((toDec & 0xFF) - 1 < 0x0))
    SET_BIT(REG_F, F_H);
  toDec--;
  if (toDec == 0)
    SET_BIT(REG_F, F_Z);
}
