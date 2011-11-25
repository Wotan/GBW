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

void	Emulator::ADD_8Bit(BYTE &toAdd, BYTE add, bool addCarry)
{
  int	adding;

  N_F = 0;
  adding = add;
  if (addCarry)
    adding += C_F ? 1 : 0;
  H_F = (((toAdd & 0xF) + (adding & 0xF)) > 0xF);
  C_F = (adding + toAdd > 0xFF);
  toAdd += adding;
  Z_F = (toAdd == 0);
}

void	Emulator::SUB_8Bit(BYTE &toSub, BYTE sub, bool addCarry)
{
  int	nbSub;

  N_F = 0;
  H_F = 0;
  C_F = 0;

  nbSub = sub;
  if (addCarry)
    nbSub += (IS_BIT_SET(REG_F, F_C) ? 1 : 0);

  if (((toSub & 0xFF) >= (nbSub & 0xFF))) // >= or > ???
    H_F = 1;

  if (toSub >= nbSub)
    SET_BIT(REG_F, F_C);
  toSub -= nbSub;
}

void	Emulator::AND_8Bit(BYTE &toAnd, BYTE src)
{
  N_F = 0;
  H_F = 1;
  C_F = 0;
  Z_F = 0;

  toAnd &= src;
  Z_F = (toAnd == 0);
}

void	Emulator::OR_8Bit(BYTE &toOr, BYTE src)
{
  N_F = 0;
  H_F = 0;
  C_F = 0;
  Z_F = 0;

  toOr |= src;
  Z_F = (toOr == 0);
}

void	Emulator::XOR_8Bit(BYTE &toXor, BYTE src)
{
  N_F = H_F = C_F = 0;
  toXor ^= src;
  Z_F = !toXor;
}

void	Emulator::CP_8Bit(BYTE cp1, BYTE cp2)
{
  N_F = 1;
  Z_F = (cp1 == cp2);
  H_F = ((cp1 & 0xFF) < (cp2 & 0xFF));
  C_F = (cp1 < cp2);
}

void	Emulator::INC_8Bit(BYTE &toInc)
{
  N_F = 0;
  toInc++;
  H_F = ((toInc & 0x0F) == 0x0);
  Z_F = (toInc == 0);
}

void	Emulator::DEC_8Bit(BYTE &toDec)
{
  N_F = 1;
  toDec--;
  H_F = ((toDec & 0x0F) == 0xF);
  Z_F = (toDec == 0);
}

void	Emulator::ADD_16bit(WORD &toAdd, WORD add)
{
  N_F = 0;
  C_F = (toAdd + add > 0xFFFF);
  H_F = (((toAdd & 0x000F) + (add & 0x000F)) > 0x000F);
  toAdd += add;
}

void	Emulator::ADD_16bitSigned(WORD &toAdd, SBYTE add)
{
  N_F = 0;
  Z_F = 0;
  C_F = (toAdd + add > 0xFFFF);
  if (add > 0)
    H_F = (((toAdd & 0x000F) + (add & 0x000F)) > 0x000F);
  else
    H_F = (((toAdd & 0x000F) + (add & 0x000F)) < 0x0000);
  toAdd += add;
}

void	Emulator::SWAP_8bit(BYTE &toSwap)
{
  BYTE	save;

  N_F = 0;
  H_F = 0;
  N_F = 0;
  save = toSwap;
  save = save >> 4;
  save |= toSwap << 4;
  toSwap = save;

  Z_F = (toSwap == 0);
}

void	Emulator::DDA_8Bit(BYTE &nbr)
{
  int	first = nbr / 10;
  int	second = nbr % 10;

  C_F = 0;
  H_F = 0;
  if (first >= 10)
    {
      C_F = 1;
      first /= 10;
    }
  nbr = 0;
  nbr = second;
  nbr |= first << 4;
  Z_F = (nbr == 0);
}

void	Emulator::RotateRight_8bit(BYTE &data, bool throughtCarry)
{
  bool	oldBit;
  bool	oldCarry;

  oldBit = IS_BIT_SET(data, 0);
  oldCarry = C_F;

  C_F = 0;
  Z_F = 0;
  if (oldBit)
    C_F = 1;
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
  N_F = 0;
  H_F = 0;
  if (data == 0)
    Z_F = 1;
}

void	Emulator::RotateLeft_8bit(BYTE &data, bool throughtCarry)
{
  bool	oldBit;
  bool	oldCarry;

  oldBit = IS_BIT_SET(data, 7);
  oldCarry = IS_BIT_SET(REG_F, F_C);

  C_F = oldBit;
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
  N_F = 0;
  H_F = 0;
  Z_F = (data == 0);
}

void	Emulator::ShiftLeft_8bit(BYTE &data)
{
  N_F = 0;
  H_F = 0;
  Z_F = 0;
  C_F = IS_BIT_SET(data, 7);
  data <<= 1;
  Z_F = (data == 0);
}

void	Emulator::ShiftRight_8bit(BYTE &data, bool MSB)
{
  bool	save;
  save = IS_BIT_SET(data, 7);
  N_F = 0;
  H_F = 0;
  Z_F = 0;

  C_F = (IS_BIT_SET(data, 0));
  data >>= 1;
  if (MSB && save)
    SET_BIT(data, 7);
  Z_F = (data == 0);
}

void	Emulator::TestBit(BYTE totest, BYTE n)
{
  Z_F = !IS_BIT_SET(totest, n);
  N_F = 0;
  H_F = 1;
}
