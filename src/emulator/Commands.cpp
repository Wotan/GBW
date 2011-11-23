#include <iostream>
#include <cmath>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"


void	Emulator::Halt()
{


}

void	Emulator::Stop()
{


}

void	Emulator::ToggleInt(bool on)
{

}

void	Emulator::ToggleIntAfter(bool on)
{
  on = on;
}

void	Emulator::Load16bitHL()
{
  BYTE tmp = ReadMem(mPC++);
  WORD res;

  RESET_BIT(REG_F, F_Z);
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);

  if (((tmp & 0xFF) + (mSP & 0xFF)) > 0xFF)
    SET_BIT(REG_F, F_H);

  if (tmp + mSP > 0xFFF) // TO SEE
    SET_BIT(REG_F, F_C);
  res = tmp + mSP;
  mHL.a = res;
}

void	Emulator::Push(WORD value)
{
  UWORD tmp;

  tmp.a = value;

  WriteMem(mSP, tmp.lo);
  WriteMem(mSP - 1, tmp.hi);
  mSP -= 2;
}

WORD	Emulator::Pop()
{
  UWORD tmp;

  tmp.hi = ReadMem(mSP + 1);
  tmp.lo = ReadMem(mSP + 2);
  mSP += 2;
  return tmp.a;
}

void	Emulator::ADD_8Bit(BYTE &toAdd, BYTE add, bool addCarry)
{
  int	adding;

  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);
  RESET_BIT(REG_F, F_Z);

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
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);

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
  RESET_BIT(REG_F, F_Z);

  toAnd &= src;
  if (toAnd == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::OR_8Bit(BYTE &toOr, BYTE src)
{
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);
  RESET_BIT(REG_F, F_Z);

  toOr |= src;
  if (toOr == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::XOR_8Bit(BYTE &toXor, BYTE src)
{
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);
  RESET_BIT(REG_F, F_Z);

  toXor ^= src;
  if (toXor == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::CP_8Bit(BYTE cp1, BYTE cp2)
{
  SET_BIT(REG_F, F_N);

  RESET_BIT(REG_F, F_Z);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);
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
  RESET_BIT(REG_F, F_Z);
  RESET_BIT(REG_F, F_H);
  if (!((toInc & 0xFF) + 1 > 0xF))
    SET_BIT(REG_F, F_H);
  toInc++;
  if (toInc == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::DEC_8Bit(BYTE &toDec)
{
  SET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_Z);
  RESET_BIT(REG_F, F_H);
  if (!((toDec & 0xFF) - 1 < 0x0))
    SET_BIT(REG_F, F_H);
  toDec--;
  if (toDec == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::ADD_16bit(WORD &toAdd, WORD add)
{
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_C);
  RESET_BIT(REG_F, F_H);

  if (toAdd + add > 0xFFFF)
    SET_BIT(REG_F, F_C);
  if ((((toAdd & 0xF000) >> 12) + ((add & 0xF000) >> 12)) > 0xF)
    SET_BIT(REG_F, F_H);
  toAdd += add;
}

void	Emulator::ADD_16bitSigned(WORD &toAdd, SBYTE add)
{
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);

  if (toAdd + add > 0xFFFF)
    SET_BIT(REG_F, F_C);
    RESET_BIT(REG_F, F_C);
  if ((((toAdd & 0xF000) >> 12) + ((add & 0xF000) >> 12)) > 0xF)
    SET_BIT(REG_F, F_H);

  toAdd += add;
}

void	Emulator::SWAP_8bit(BYTE &toSwap)
{
  BYTE	save;

  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_C);
  RESET_BIT(REG_F, F_Z);
  save = toSwap;
  save = save >> 4;
  save |= toSwap << 4;
  toSwap = save;
  if (toSwap == 0)
    SET_BIT(REG_F, F_Z);

}

void	Emulator::DDA_8Bit(BYTE &nbr)
{
  int	first = nbr / 10;
  int	second = nbr % 10;

  RESET_BIT(REG_F, F_Z);
  RESET_BIT(REG_F, F_C);
  RESET_BIT(REG_F, F_H);
  if (first >= 10)
    {
      SET_BIT(REG_F, F_C);
      first /= 10;
    }

  nbr = 0;
  nbr = second;
  nbr |= first << 4;
  if (nbr == 0)
    SET_BIT(REG_F, F_Z);

}

void	Emulator::RotateRight_8bit(BYTE &data, bool throughtCarry)
{
  bool	oldBit;
  bool	oldCarry;

  oldBit = IS_BIT_SET(data, 0);
  oldCarry = IS_BIT_SET(REG_F, F_C);

  RESET_BIT(REG_F, F_C);
  RESET_BIT(REG_F, F_Z);
  if (oldBit)
    SET_BIT(REG_F, F_C);
  data >>= 1;
  if (throughtCarry) // bit7 == Oldcarry
    {
      if (oldCarry)
	SET_BIT(data, 7);
    }
  else // bit7 == oldBit
    {
      if (oldBit)
	SET_BIT(data, 7);
    }
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  if (data == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::RotateLeft_8bit(BYTE &data, bool throughtCarry)
{
  bool	oldBit;
  bool	oldCarry;

  RESET_BIT(REG_F, F_Z);
  oldBit = IS_BIT_SET(data, 7);
  oldCarry = IS_BIT_SET(REG_F, F_C);

  if (oldBit)
    SET_BIT(REG_F, F_C);
  else
    RESET_BIT(REG_F, F_C);
  data <<= 1;
  if (throughtCarry) // bit0 == Oldcarry
    {
      if (oldCarry)
	SET_BIT(data, 0);
    }
  else // bit0 == oldBit
    {
      if (oldBit)
	SET_BIT(data, 0);
    }
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  if (data == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::ShiftLeft_8bit(BYTE &data)
{
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_Z);
  if (IS_BIT_SET(data, 7))
    SET_BIT(REG_F, F_C);
  else
    RESET_BIT(REG_F, F_C);

  data <<= 1;
  if (data == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::ShiftRight_8bit(BYTE &data, bool MSB)
{
  bool	save;
  save = IS_BIT_SET(data, 7);
  RESET_BIT(REG_F, F_N);
  RESET_BIT(REG_F, F_H);
  RESET_BIT(REG_F, F_Z);

  if (IS_BIT_SET(data, 0))
    SET_BIT(REG_F, F_C);
  else
    RESET_BIT(REG_F, F_C);
  if (MSB && save)
    SET_BIT(data, 7);
  data >>= 1;
  if (data == 0)
    SET_BIT(REG_F, F_Z);
}

void	Emulator::TestBit(BYTE totest, BYTE n)
{
   RESET_BIT(REG_F, F_Z);
   if (!IS_BIT_SET(totest, n)) // == 0
     SET_BIT(REG_F, F_Z);
  RESET_BIT(REG_F, F_N);
  SET_BIT(REG_F, F_H);
}
