#include <iostream>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"

int	Emulator::DoOpcode()
{
  UWORD tmp;
  BYTE	tmpB;
  BYTE	extOpcode;
  int	opcode = ReadMem(mPC);
  mPC++;
  switch (opcode)
    {
    case 0x06: REG_B = ReadMem(mPC++); return 8;
    case 0x0E: REG_C = ReadMem(mPC++); return 8;
    case 0x16: REG_D = ReadMem(mPC++); return 8;
    case 0x1E: REG_E = ReadMem(mPC++); return 8;
    case 0x26: REG_H = ReadMem(mPC++); return 8;
    case 0x2E: REG_L = ReadMem(mPC++); return 8;

    case 0x7F: REG_A = REG_A; return 4;
    case 0x78: REG_A = REG_B; return 4;
    case 0x79: REG_A = REG_C; return 4;
    case 0x7A: REG_A = REG_D; return 4;
    case 0x7B: REG_A = REG_E; return 4;
    case 0x7C: REG_A = REG_H; return 4;
    case 0x7D: REG_A = REG_L; return 4;
    case 0x7E: REG_A = ReadMem(mHL.a); return 8;
    case 0x40: REG_B = REG_B; return 4;
    case 0x41: REG_B = REG_C; return 4;
    case 0x42: REG_B = REG_D; return 4;
    case 0x43: REG_B = REG_E; return 4;
    case 0x44: REG_B = REG_H; return 4;
    case 0x45: REG_B = REG_L; return 4;
    case 0x46: REG_B = ReadMem(mHL.a); return 8;
    case 0x48: REG_C = REG_B; return 4;
    case 0x49: REG_C = REG_C; return 4;
    case 0x4A: REG_C = REG_D; return 4;
    case 0x4B: REG_C = REG_E; return 4;
    case 0x4C: REG_C = REG_H; return 4;
    case 0x4D: REG_C = REG_L; return 4;
    case 0x4E: REG_C = ReadMem(mHL.a); return 8;
    case 0x50: REG_D = REG_B; return 4;

    case 0x51: REG_D = REG_C; return 4;
    case 0x52: REG_D = REG_D; return 4;
    case 0x53: REG_D = REG_E; return 4;
    case 0x54: REG_D = REG_H; return 4;
    case 0x55: REG_D = REG_L; return 4;
    case 0x56: REG_D = ReadMem(mHL.a); return 8;
    case 0x58: REG_E = REG_B; return 4;
    case 0x59: REG_E = REG_C; return 4;
    case 0x5A: REG_E = REG_D; return 4;
    case 0x5B: REG_E = REG_E; return 4;
    case 0x5C: REG_E = REG_H; return 4;
    case 0x5D: REG_E = REG_L; return 4;
    case 0x5E: REG_E = ReadMem(mHL.a); return 8;
    case 0x60: REG_H = REG_B; return 4;
    case 0x61: REG_H = REG_C; return 4;
    case 0x62: REG_H = REG_D; return 4;
    case 0x63: REG_H = REG_E; return 4;
    case 0x64: REG_H = REG_H; return 4;
    case 0x65: REG_H = REG_L; return 4;
    case 0x66: REG_H = ReadMem(mHL.a); return 8;
    case 0x68: REG_L = REG_B; return 4;
    case 0x69: REG_L = REG_C; return 4;
    case 0x6A: REG_L = REG_D; return 4;
    case 0x6B: REG_L = REG_E; return 4;
    case 0x6C: REG_L = REG_H; return 4;
    case 0x6D: REG_L = REG_L; return 4;
    case 0x6E: REG_L = ReadMem(mHL.a); return 8;
    case 0x70: WriteMem(mHL.a, REG_B); return 8;
    case 0x71: WriteMem(mHL.a, REG_C); return 8;
    case 0x72: WriteMem(mHL.a, REG_D); return 8;
    case 0x73: WriteMem(mHL.a, REG_E); return 8;
    case 0x74: WriteMem(mHL.a, REG_H); return 8;
    case 0x75: WriteMem(mHL.a, REG_L); return 8;
    case 0x36: WriteMem(mHL.a, ReadMem(mPC++)); return 12;


    case 0x0A: REG_A = ReadMem(mBC.a); return 8;
    case 0x1A: REG_A = ReadMem(mDE.a); return 8;

    case 0xFA:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      WriteMem(REG_A, ReadMem(tmp.a));
      return 16;
    case 0x3E: REG_A = ReadMem(mPC++); // Warn return 8;
    case 0x47: REG_B = REG_A; return 4;
    case 0x4F: REG_C = REG_A; return 4;
    case 0x57: REG_D = REG_A; return 4;
    case 0x5F: REG_E = REG_A; return 4;
    case 0x67: REG_H = REG_A; return 4;
    case 0x6F: REG_L = REG_A; return 4;
    case 0x02: mBC.a = REG_A; return 8;
    case 0x12: mDE.a = REG_A; return 8;
    case 0x77: mBC.a = REG_A; return 8;

    case 0xEA:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      WriteMem(tmp.a, REG_A);
      return 16;
    case 0xF2: REG_A = ReadMem(0xFF00 + REG_C); return 8;
    case 0xE2: WriteMem(0xFF00 + REG_C, REG_A); return 8;
    case 0x3A:
      REG_A = ReadMem(mHL.a);
      mHL.a--;
      return 8;
    case 0x32:
      WriteMem(mHL.a, REG_A);
      mHL.a--;
      return 8;
    case 0x2A:
      REG_A = ReadMem(mHL.a);
      mHL.a++;
      return 8;
    case 0x22:
      WriteMem(mHL.a, REG_A);
      mHL.a++;
      return 8;
    case 0xE0:
      WriteMem(0xFF00 + ReadMem(mPC++), REG_A);
      return 8;
    case 0xF0:
      REG_A = ReadMem(0xFF00 + ReadMem(mPC++));
      return 8;
    case 0x01:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      mBC.a = tmp.a;
      return 12;
    case 0x11:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      mDE.a = tmp.a;
      return 12;
    case 0x21:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      mHL.a = tmp.a;
      return 12;
    case 0x31:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      mSP = tmp.a;
      return 12;
    case 0xF9:
      mSP = mHL.a;
      return 8;
    case 0xF8:
      Load16bitHL();
      return 12;
    case 0x08:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      WriteMem(tmp.a, mSP);
      return 20;

    case 0xF5: Push(mAF.a); return 16;
    case 0xC5: Push(mBC.a); return 16;
    case 0xD5: Push(mDE.a); return 16;
    case 0xE5: Push(mHL.a); return 16;
    case 0xF1: mAF.a = Pop(); return 12;
    case 0xC1: mBC.a = Pop(); return 12;
    case 0xD1: mDE.a = Pop(); return 12;
    case 0xE1: mHL.a = Pop(); return 12;

    case 0x87: ADD_8Bit(REG_A, REG_A, false); return 4;
    case 0x80: ADD_8Bit(REG_A, REG_B, false); return 4;
    case 0x81: ADD_8Bit(REG_A, REG_C, false); return 4;
    case 0x82: ADD_8Bit(REG_A, REG_D, false); return 4;
    case 0x83: ADD_8Bit(REG_A, REG_E, false); return 4;
    case 0x84: ADD_8Bit(REG_A, REG_H, false); return 4;
    case 0x85: ADD_8Bit(REG_A, REG_L, false); return 4;
    case 0x86: ADD_8Bit(REG_A, ReadMem(mHL.a), false); return 8;
    case 0xC6: ADD_8Bit(REG_A, ReadMem(mPC++), false); return 8;

    case 0x8F: ADD_8Bit(REG_A, REG_A, true); return 4;
    case 0x88: ADD_8Bit(REG_A, REG_B, true); return 4;
    case 0x89: ADD_8Bit(REG_A, REG_C, true); return 4;
    case 0x8A: ADD_8Bit(REG_A, REG_D, true); return 4;
    case 0x8B: ADD_8Bit(REG_A, REG_E, true); return 4;
    case 0x8C: ADD_8Bit(REG_A, REG_H, true); return 4;
    case 0x8D: ADD_8Bit(REG_A, REG_L, true); return 4;
    case 0x8E: ADD_8Bit(REG_A, ReadMem(mHL.a), true); return 8;
    case 0xCE: ADD_8Bit(REG_A, ReadMem(mPC++), true); return 8;

    case 0x97: SUB_8Bit(REG_A, REG_A, false); return 4;
    case 0x90: SUB_8Bit(REG_A, REG_B, false); return 4;
    case 0x91: SUB_8Bit(REG_A, REG_C, false); return 4;
    case 0x92: SUB_8Bit(REG_A, REG_D, false); return 4;
    case 0x93: SUB_8Bit(REG_A, REG_E, false); return 4;
    case 0x94: SUB_8Bit(REG_A, REG_H, false); return 4;
    case 0x95: SUB_8Bit(REG_A, REG_L, false); return 4;
    case 0x96: SUB_8Bit(REG_A, ReadMem(mHL.a), false); return 8;
    case 0xD6: SUB_8Bit(REG_A, ReadMem(mPC++), false); return 8;

    case 0x9F: SUB_8Bit(REG_A, REG_A, true); return 4;
    case 0x98: SUB_8Bit(REG_A, REG_B, true); return 4;
    case 0x99: SUB_8Bit(REG_A, REG_C, true); return 4;
    case 0x9A: SUB_8Bit(REG_A, REG_D, true); return 4;
    case 0x9B: SUB_8Bit(REG_A, REG_E, true); return 4;
    case 0x9C: SUB_8Bit(REG_A, REG_H, true); return 4;
    case 0x9D: SUB_8Bit(REG_A, REG_L, true); return 4;
    case 0x9E: SUB_8Bit(REG_A, ReadMem(mHL.a), true); return 8;
    case 0xDE: SUB_8Bit(REG_A, ReadMem(mPC++), true); return 8;

    case 0xA7: AND_8Bit(REG_A, REG_A); return 4;
    case 0xA0: AND_8Bit(REG_A, REG_B); return 4;
    case 0xA1: AND_8Bit(REG_A, REG_C); return 4;
    case 0xA2: AND_8Bit(REG_A, REG_D); return 4;
    case 0xA3: AND_8Bit(REG_A, REG_E); return 4;
    case 0xA4: AND_8Bit(REG_A, REG_H); return 4;
    case 0xA5: AND_8Bit(REG_A, REG_L); return 4;
    case 0xA6: AND_8Bit(REG_A, ReadMem(mHL.a)); return 8;
    case 0xE6: AND_8Bit(REG_A, ReadMem(mPC++)); return 8;

    case 0xB7: OR_8Bit(REG_A, REG_A); return 4;
    case 0xB0: OR_8Bit(REG_A, REG_B); return 4;
    case 0xB1: OR_8Bit(REG_A, REG_C); return 4;
    case 0xB2: OR_8Bit(REG_A, REG_D); return 4;
    case 0xB3: OR_8Bit(REG_A, REG_E); return 4;
    case 0xB4: OR_8Bit(REG_A, REG_H); return 4;
    case 0xB5: OR_8Bit(REG_A, REG_L); return 4;
    case 0xB6: OR_8Bit(REG_A, ReadMem(mHL.a)); return 8;
    case 0xF6: OR_8Bit(REG_A, ReadMem(mPC++)); return 8;

    case 0xAF: XOR_8Bit(REG_A, REG_A); return 4;
    case 0xA8: XOR_8Bit(REG_A, REG_B); return 4;
    case 0xA9: XOR_8Bit(REG_A, REG_C); return 4;
    case 0xAA: XOR_8Bit(REG_A, REG_D); return 4;
    case 0xAB: XOR_8Bit(REG_A, REG_E); return 4;
    case 0xAC: XOR_8Bit(REG_A, REG_H); return 4;
    case 0xAD: XOR_8Bit(REG_A, REG_L); return 4;
    case 0xAE: XOR_8Bit(REG_A, ReadMem(mHL.a)); return 8;
    case 0xEE: XOR_8Bit(REG_A, ReadMem(mPC++)); return 8;

    case 0xBF: CP_8Bit(REG_A, REG_A); return 4;
    case 0xB8: CP_8Bit(REG_A, REG_B); return 4;
    case 0xB9: CP_8Bit(REG_A, REG_C); return 4;
    case 0xBA: CP_8Bit(REG_A, REG_D); return 4;
    case 0xBB: CP_8Bit(REG_A, REG_E); return 4;
    case 0xBC: CP_8Bit(REG_A, REG_H); return 4;
    case 0xBD: CP_8Bit(REG_A, REG_L); return 4;
    case 0xBE: CP_8Bit(REG_A, ReadMem(mHL.a)); return 8;
    case 0xFE: CP_8Bit(REG_A, ReadMem(mPC++)); return 8;

    case 0x3C: INC_8Bit(REG_A); return 4;
    case 0x04: INC_8Bit(REG_B); return 4;
    case 0x0C: INC_8Bit(REG_C); return 4;
    case 0x14: INC_8Bit(REG_D); return 4;
    case 0x1C: INC_8Bit(REG_E); return 4;
    case 0x24: INC_8Bit(REG_H); return 4;
    case 0x2C: INC_8Bit(REG_L); return 4;
    case 0x34:
      tmpB = ReadMem(mHL.a);
      INC_8Bit(tmpB);
      WriteMem(mHL.a, tmpB);
      return 12;

    case 0x3D: DEC_8Bit(REG_A); return 4;
    case 0x05: DEC_8Bit(REG_B); return 4;
    case 0x0D: DEC_8Bit(REG_C); return 4;
    case 0x15: DEC_8Bit(REG_D); return 4;
    case 0x1D: DEC_8Bit(REG_E); return 4;
    case 0x25: DEC_8Bit(REG_H); return 4;
    case 0x2D: DEC_8Bit(REG_L); return 4;
    case 0x35:
      tmpB = ReadMem(mHL.a);
      DEC_8Bit(tmpB);
      WriteMem(mHL.a, tmpB);
      return 12;

    case 0x09: ADD_16bit(mHL.a, mBC.a); return 8;
    case 0x19: ADD_16bit(mHL.a, mDE.a); return 8;
    case 0x29: ADD_16bit(mHL.a, mHL.a); return 8;
    case 0x39: ADD_16bit(mHL.a, mSP); return 8;
    case 0xE8: ADD_16bitSigned(mSP, ReadMem(mPC++)); return 16;

    case 0x03: mBC.a++; return 8;
    case 0x13: mDE.a++; return 8;
    case 0x23: mHL.a++; return 8;
    case 0x33: mSP++; return 8;
    case 0x0B: mBC.a--; return 8;
    case 0x1B: mDE.a--; return 8;
    case 0x2B: mHL.a--; return 8;
    case 0x3B: mSP--; return 8;
    case 0x27: DDA_8Bit(REG_A); return 4;

    case 0x2F:
      SET_BIT(REG_F, F_N);
      SET_BIT(REG_F, F_H);
      REG_A |= 0xFF;
      return 4;
    case 0x3F:
      RESET_BIT(REG_F, F_N);
      RESET_BIT(REG_F, F_H);
      if (IS_BIT_SET(REG_F, F_C))
	RESET_BIT(REG_F, F_C);
      else
	SET_BIT(REG_F, F_C);
      return 4;
    case 0x37:
      RESET_BIT(REG_F, F_N);
      RESET_BIT(REG_F, F_H);
      RESET_BIT(REG_F, F_C);
      return 4;

    case 0x00: return 4;
    case 0x76: Halt(); return 4;
    case 0xF3: ToggleIntAfter(false); return 4;
    case 0xFB: ToggleIntAfter(true); return 4;

    case 0x07: RotateLeft_8bit(REG_A, false); return 4;
    case 0x17: RotateLeft_8bit(REG_A, true); return 4;

    case 0x0F: RotateRight_8bit(REG_A, false); return 4;
    case 0x1F: RotateRight_8bit(REG_A, true); return 4;

      // JUMP
    case 0xC3:
      tmp.lo = ReadMem(mPC++); tmp.hi = ReadMem(mPC++);
      mPC = tmp.a;
      return 12;
    case 0xC2:
      tmp.lo = ReadMem(mPC++); tmp.hi = ReadMem(mPC++);
      if (!IS_BIT_SET(REG_F, F_Z))
	mPC = tmp.a;
      return 12;
    case 0xCA:
      tmp.lo = ReadMem(mPC++); tmp.hi = ReadMem(mPC++);
      if (IS_BIT_SET(REG_F, F_Z))
	mPC = tmp.a;
      return 12;
    case 0xD2:
      tmp.lo = ReadMem(mPC++); tmp.hi = ReadMem(mPC++);
      if (!IS_BIT_SET(REG_F, F_C))
	mPC = tmp.a;
      return 12;
    case 0xDA:
      tmp.lo = ReadMem(mPC++); tmp.hi = ReadMem(mPC++);
      if (IS_BIT_SET(REG_F, F_C))
	mPC = tmp.a;
      return 12;
    case 0xE9: mPC = mHL.a; return 4;
    case 0x18: tmpB = ReadMem(mPC++); mPC += tmpB - 1;
      return 8;
    case 0x20:
      mPC++;
      if (!IS_BIT_SET(REG_F, F_Z))
	mPC = ReadMem(mPC) - 1;
      return 8;
    case 0x28:
      mPC++;
      if (IS_BIT_SET(REG_F, F_Z))
	mPC = ReadMem(mPC) - 1;
      return 8;
    case 0x30:
      mPC++;
      if (!IS_BIT_SET(REG_F, F_C))
	mPC = ReadMem(mPC) - 1;
      return 8;
    case 0x38:
      mPC++;
      if (IS_BIT_SET(REG_F, F_C))
	mPC += ReadMem(mPC) - 1;
      return 8;

      // CALL
    case 0xCD:
      tmp.lo = ReadMem(mPC++); tmp.hi = ReadMem(mPC++);
      Push(mPC);
      mPC = tmp.a;
      return 12;

    case 0xC4:
      tmp.lo = ReadMem(mPC++); tmp.hi = ReadMem(mPC++);
      if (IS_BIT_SET(REG_F, F_Z))
	return 12;
      Push(mPC);
      mPC = tmp.a;
      return 12;
    case 0xCC:
      tmp.lo = ReadMem(mPC++); tmp.hi = ReadMem(mPC++);
      if (!IS_BIT_SET(REG_F, F_Z))
	return 12;
      Push(mPC);
      mPC = tmp.a;
      return 12;
    case 0xD4:
      if (IS_BIT_SET(REG_F, F_C))
	return 12;
      tmp.lo = ReadMem(mPC++); tmp.hi = ReadMem(mPC++);
      Push(mPC);
      mPC = tmp.a;
      return 12;
    case 0xDC:
      tmp.lo = ReadMem(mPC++); tmp.hi = ReadMem(mPC++);
      if (!IS_BIT_SET(REG_F, F_C))
	return 12;
      Push(mPC);
      mPC = tmp.a;
      return 12;

      // RST
    case 0xC7: Push(mPC - 1); mPC = 0x00; return 32;
    case 0xCF: Push(mPC - 1); mPC = 0x08; return 32;
    case 0xD7: Push(mPC - 1); mPC = 0x10; return 32;
    case 0xDF: Push(mPC - 1); mPC = 0x18; return 32;
    case 0xE7: Push(mPC - 1); mPC = 0x20; return 32;
    case 0xEF: Push(mPC - 1); mPC = 0x28; return 32;
    case 0xF7: Push(mPC - 1); mPC = 0x30; return 32;
    case 0xFF: Push(mPC - 1); mPC = 0x38; return 32;

      // RET
    case 0xC9: mPC = Pop(); return 8;
    case 0xC0: if (!IS_BIT_SET(REG_F, F_Z)) mPC = Pop(); return 8;
    case 0xC8: if (IS_BIT_SET(REG_F, F_Z)) mPC = Pop(); return 8;
    case 0xD0: if (!IS_BIT_SET(REG_F, F_C)) mPC = Pop(); return 8;
    case 0xD8: if (IS_BIT_SET(REG_F, F_C)) mPC = Pop(); return 8;

      // RETI
    case 0xD9: mPC = Pop(); ToggleInt(true); return 8;

      // Extended opcodes
    case 0x10:
      {
	extOpcode = ReadMem(mPC++);
	if (extOpcode == 0x0)
	  {
	    Stop();
	    return 4;
	  }
	std::cout << "Unknown opcode :" << opcode << "." << extOpcode<< std::endl;
	return 1;
      }

    case 0xCB:
      {
	extOpcode = ReadMem(mPC++);
	switch (extOpcode)
	  {
	  case 0x37: SWAP_8bit(REG_A); return 8;
	  case 0x30: SWAP_8bit(REG_B); return 8;
	  case 0x31: SWAP_8bit(REG_C); return 8;
	  case 0x32: SWAP_8bit(REG_D); return 8;
	  case 0x33: SWAP_8bit(REG_E); return 8;
	  case 0x34: SWAP_8bit(REG_H); return 8;
	  case 0x35: SWAP_8bit(REG_L); return 8;

	  case 0x36:
	    tmpB = ReadMem(mHL.a);
	    SWAP_8bit(tmpB);
	    WriteMem(mHL.a, tmpB);
	    return 16;

	  case 0x07: RotateLeft_8bit(REG_A, false); return 8;
	  case 0x00: RotateLeft_8bit(REG_B, false); return 8;
	  case 0x01: RotateLeft_8bit(REG_C, false); return 8;
	  case 0x02: RotateLeft_8bit(REG_D, false); return 8;
	  case 0x03: RotateLeft_8bit(REG_E, false); return 8;
	  case 0x04: RotateLeft_8bit(REG_H, false); return 8;
	  case 0x05: RotateLeft_8bit(REG_L, false); return 8;
	  case 0x06:
	    tmpB = ReadMem(mHL.a);
	    RotateLeft_8bit(tmpB, false);
	    WriteMem(mHL.a, tmpB);
	    return 16;

	  case 0x17: RotateLeft_8bit(REG_A, true); return 8;
	  case 0x10: RotateLeft_8bit(REG_B, true); return 8;
	  case 0x11: RotateLeft_8bit(REG_C, true); return 8;
	  case 0x12: RotateLeft_8bit(REG_D, true); return 8;
	  case 0x13: RotateLeft_8bit(REG_E, true); return 8;
	  case 0x14: RotateLeft_8bit(REG_H, true); return 8;
	  case 0x15: RotateLeft_8bit(REG_L, true); return 8;
	  case 0x16:
	    tmpB = ReadMem(mHL.a);
	    RotateLeft_8bit(tmpB, true);
	    WriteMem(mHL.a, tmpB);
	    return 16;

	  case 0x0F: RotateRight_8bit(REG_A, false); return 8;
	  case 0x08: RotateRight_8bit(REG_B, false); return 8;
	  case 0x09: RotateRight_8bit(REG_C, false); return 8;
	  case 0x0A: RotateRight_8bit(REG_D, false); return 8;
	  case 0x0B: RotateRight_8bit(REG_E, false); return 8;
	  case 0x0C: RotateRight_8bit(REG_H, false); return 8;
	  case 0x0D: RotateRight_8bit(REG_L, false); return 8;
	  case 0x0E:
	    tmpB = ReadMem(mHL.a);
	    RotateRight_8bit(tmpB, false);
	    WriteMem(mHL.a, tmpB);
	    return 16;

	  case 0x1F: RotateRight_8bit(REG_A, true); return 8;
	  case 0x18: RotateRight_8bit(REG_B, true); return 8;
	  case 0x19: RotateRight_8bit(REG_C, true); return 8;
	  case 0x1A: RotateRight_8bit(REG_D, true); return 8;
	  case 0x1B: RotateRight_8bit(REG_E, true); return 8;
	  case 0x1C: RotateRight_8bit(REG_H, true); return 8;
	  case 0x1D: RotateRight_8bit(REG_L, true); return 8;
	  case 0x1E:
	    tmpB = ReadMem(mHL.a);
	    RotateRight_8bit(tmpB, true);
	    WriteMem(mHL.a, tmpB);
	    return 16;

	  case 0x27: ShiftLeft_8bit(REG_A); return 8;
	  case 0x20: ShiftLeft_8bit(REG_B); return 8;
	  case 0x21: ShiftLeft_8bit(REG_C); return 8;
	  case 0x22: ShiftLeft_8bit(REG_D); return 8;
	  case 0x23: ShiftLeft_8bit(REG_E); return 8;
	  case 0x24: ShiftLeft_8bit(REG_H); return 8;
	  case 0x25: ShiftLeft_8bit(REG_L); return 8;
	  case 0x26:
	    tmpB = ReadMem(mHL.a);
	    ShiftLeft_8bit(tmpB);
	    WriteMem(mHL.a, tmpB);
	    return 16;

	  case 0x2F: ShiftRight_8bit(REG_A, false); return 8;
	  case 0x28: ShiftRight_8bit(REG_B, false); return 8;
	  case 0x29: ShiftRight_8bit(REG_C, false); return 8;
	  case 0x2A: ShiftRight_8bit(REG_D, false); return 8;
	  case 0x2B: ShiftRight_8bit(REG_E, false); return 8;
	  case 0x2C: ShiftRight_8bit(REG_H, false); return 8;
	  case 0x2D: ShiftRight_8bit(REG_L, false); return 8;
	  case 0x2E:
	    tmpB = ReadMem(mHL.a);
	    ShiftRight_8bit(tmpB, false);
	    WriteMem(mHL.a, tmpB);
	    return 16;

	  case 0x3F: ShiftRight_8bit(REG_A, true); return 8;
	  case 0x38: ShiftRight_8bit(REG_B, true); return 8;
	  case 0x39: ShiftRight_8bit(REG_C, true); return 8;
	  case 0x3A: ShiftRight_8bit(REG_D, true); return 8;
	  case 0x3B: ShiftRight_8bit(REG_E, true); return 8;
	  case 0x3C: ShiftRight_8bit(REG_H, true); return 8;
	  case 0x3D: ShiftRight_8bit(REG_L, true); return 8;
	  case 0x3E:
	    tmpB = ReadMem(mHL.a);
	    ShiftRight_8bit(tmpB, true);
	    WriteMem(mHL.a, tmpB);
	    return 16;

	  case 0x47: TestBit(REG_A, 0); return 8;
	  case 0x40: TestBit(REG_B, 0); return 8;
	  case 0x41: TestBit(REG_C, 0); return 8;
	  case 0x42: TestBit(REG_D, 0); return 8;
	  case 0x43: TestBit(REG_E, 0); return 8;
	  case 0x44: TestBit(REG_H, 0); return 8;
	  case 0x45: TestBit(REG_L, 0); return 8;
	  case 0x46: TestBit(ReadMem(mHL.a), 0); return 16;
	  case 0x4F: TestBit(REG_A, 1); return 8;
	  case 0x48: TestBit(REG_B, 1); return 8;
	  case 0x49: TestBit(REG_C, 1); return 8;
	  case 0x4A: TestBit(REG_D, 1); return 8;
	  case 0x4B: TestBit(REG_E, 1); return 8;
	  case 0x4C: TestBit(REG_H, 1); return 8;
	  case 0x4D: TestBit(REG_L, 1); return 8;
	  case 0x4E: TestBit(ReadMem(mHL.a), 1); return 16;
	  case 0x57: TestBit(REG_A, 2); return 8;
	  case 0x50: TestBit(REG_B, 2); return 8;
	  case 0x51: TestBit(REG_C, 2); return 8;
	  case 0x52: TestBit(REG_D, 2); return 8;
	  case 0x53: TestBit(REG_E, 2); return 8;
	  case 0x54: TestBit(REG_H, 2); return 8;
	  case 0x55: TestBit(REG_L, 2); return 8;
	  case 0x56: TestBit(ReadMem(mHL.a), 2); return 16;
	  case 0x5F: TestBit(REG_A, 3); return 8;
	  case 0x58: TestBit(REG_B, 3); return 8;
	  case 0x59: TestBit(REG_C, 3); return 8;
	  case 0x5A: TestBit(REG_D, 3); return 8;
	  case 0x5B: TestBit(REG_E, 3); return 8;
	  case 0x5C: TestBit(REG_H, 3); return 8;
	  case 0x5D: TestBit(REG_L, 3); return 8;
	  case 0x5E: TestBit(ReadMem(mHL.a), 3); return 16;
	  case 0x67: TestBit(REG_A, 4); return 8;
	  case 0x60: TestBit(REG_B, 4); return 8;
	  case 0x61: TestBit(REG_C, 4); return 8;
	  case 0x62: TestBit(REG_D, 4); return 8;
	  case 0x63: TestBit(REG_E, 4); return 8;
	  case 0x64: TestBit(REG_H, 4); return 8;
	  case 0x65: TestBit(REG_L, 4); return 8;
	  case 0x66: TestBit(ReadMem(mHL.a), 4); return 16;
	  case 0x6F: TestBit(REG_A, 5); return 8;
	  case 0x68: TestBit(REG_B, 5); return 8;
	  case 0x69: TestBit(REG_C, 5); return 8;
	  case 0x6A: TestBit(REG_D, 5); return 8;
	  case 0x6B: TestBit(REG_E, 5); return 8;
	  case 0x6C: TestBit(REG_H, 5); return 8;
	  case 0x6D: TestBit(REG_L, 5); return 8;
	  case 0x6E: TestBit(ReadMem(mHL.a), 5); return 16;
	  case 0x77: TestBit(REG_A, 6); return 8;
	  case 0x70: TestBit(REG_B, 6); return 8;
	  case 0x71: TestBit(REG_C, 6); return 8;
	  case 0x72: TestBit(REG_D, 6); return 8;
	  case 0x73: TestBit(REG_E, 6); return 8;
	  case 0x74: TestBit(REG_H, 6); return 8;
	  case 0x75: TestBit(REG_L, 6); return 8;
	  case 0x76: TestBit(ReadMem(mHL.a), 6); return 16;
	  case 0x7F: TestBit(REG_A, 7); return 8;
	  case 0x78: TestBit(REG_B, 7); return 8;
	  case 0x79: TestBit(REG_C, 7); return 8;
	  case 0x7A: TestBit(REG_D, 7); return 8;
	  case 0x7B: TestBit(REG_E, 7); return 8;
	  case 0x7C: TestBit(REG_H, 7); return 8;
	  case 0x7D: TestBit(REG_L, 7); return 8;
	  case 0x7E: TestBit(ReadMem(mHL.a), 7); return 16;


	  case 0xC7: SET_BIT(REG_A, 0); return 8;
	  case 0xC0: SET_BIT(REG_B, 0); return 8;
	  case 0xC1: SET_BIT(REG_C, 0); return 8;
	  case 0xC2: SET_BIT(REG_D, 0); return 8;
	  case 0xC3: SET_BIT(REG_E, 0); return 8;
	  case 0xC4: SET_BIT(REG_H, 0); return 8;
	  case 0xC5: SET_BIT(REG_L, 0); return 8;
	  case 0xC6:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 0);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xCF: SET_BIT(REG_A, 1); return 8;
	  case 0xC8: SET_BIT(REG_B, 1); return 8;
	  case 0xC9: SET_BIT(REG_C, 1); return 8;
	  case 0xCA: SET_BIT(REG_D, 1); return 8;
	  case 0xCB: SET_BIT(REG_E, 1); return 8;
	  case 0xCC: SET_BIT(REG_H, 1); return 8;
	  case 0xCD: SET_BIT(REG_L, 1); return 8;
	  case 0xCE:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 1);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xD7: SET_BIT(REG_A, 2); return 8;
	  case 0xD0: SET_BIT(REG_B, 2); return 8;
	  case 0xD1: SET_BIT(REG_C, 2); return 8;
	  case 0xD2: SET_BIT(REG_D, 2); return 8;
	  case 0xD3: SET_BIT(REG_E, 2); return 8;
	  case 0xD4: SET_BIT(REG_H, 2); return 8;
	  case 0xD5: SET_BIT(REG_L, 2); return 8;
	  case 0xD6:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 2);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xDF: SET_BIT(REG_A, 3); return 8;
	  case 0xD8: SET_BIT(REG_B, 3); return 8;
	  case 0xD9: SET_BIT(REG_C, 3); return 8;
	  case 0xDA: SET_BIT(REG_D, 3); return 8;
	  case 0xDB: SET_BIT(REG_E, 3); return 8;
	  case 0xDC: SET_BIT(REG_H, 3); return 8;
	  case 0xDD: SET_BIT(REG_L, 3); return 8;
	  case 0xDE:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 3);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xE7: SET_BIT(REG_A, 4); return 8;
	  case 0xE0: SET_BIT(REG_B, 4); return 8;
	  case 0xE1: SET_BIT(REG_C, 4); return 8;
	  case 0xE2: SET_BIT(REG_D, 4); return 8;
	  case 0xE3: SET_BIT(REG_E, 4); return 8;
	  case 0xE4: SET_BIT(REG_H, 4); return 8;
	  case 0xE5: SET_BIT(REG_L, 4); return 8;
	  case 0xE6:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 4);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xEF: SET_BIT(REG_A, 5); return 8;
	  case 0xE8: SET_BIT(REG_B, 5); return 8;
	  case 0xE9: SET_BIT(REG_C, 5); return 8;
	  case 0xEA: SET_BIT(REG_D, 5); return 8;
	  case 0xEB: SET_BIT(REG_E, 5); return 8;
	  case 0xEC: SET_BIT(REG_H, 5); return 8;
	  case 0xED: SET_BIT(REG_L, 5); return 8;
	  case 0xEE:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 5);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xF7: SET_BIT(REG_A, 6); return 8;
	  case 0xF0: SET_BIT(REG_B, 6); return 8;
	  case 0xF1: SET_BIT(REG_C, 6); return 8;
	  case 0xF2: SET_BIT(REG_D, 6); return 8;
	  case 0xF3: SET_BIT(REG_E, 6); return 8;
	  case 0xF4: SET_BIT(REG_H, 6); return 8;
	  case 0xF5: SET_BIT(REG_L, 6); return 8;
	  case 0xF6:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 6);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xFF: SET_BIT(REG_A, 7); return 8;
	  case 0xF8: SET_BIT(REG_B, 7); return 8;
	  case 0xF9: SET_BIT(REG_C, 7); return 8;
	  case 0xFA: SET_BIT(REG_D, 7); return 8;
	  case 0xFB: SET_BIT(REG_E, 7); return 8;
	  case 0xFC: SET_BIT(REG_H, 7); return 8;
	  case 0xFD: SET_BIT(REG_L, 7); return 8;
	  case 0xFE:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 7);
	    WriteMem(mHL.a, tmpB);
	    return 16;

	  case 0x87: SET_BIT(REG_A, 0); return 8;
	  case 0x80: SET_BIT(REG_B, 0); return 8;
	  case 0x81: SET_BIT(REG_C, 0); return 8;
	  case 0x82: SET_BIT(REG_D, 0); return 8;
	  case 0x83: SET_BIT(REG_E, 0); return 8;
	  case 0x84: SET_BIT(REG_H, 0); return 8;
	  case 0x85: SET_BIT(REG_L, 0); return 8;
	  case 0x86:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 0);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0x8F: SET_BIT(REG_A, 1); return 8;
	  case 0x88: SET_BIT(REG_B, 1); return 8;
	  case 0x89: SET_BIT(REG_C, 1); return 8;
	  case 0x8A: SET_BIT(REG_D, 1); return 8;
	  case 0x8B: SET_BIT(REG_E, 1); return 8;
	  case 0x8C: SET_BIT(REG_H, 1); return 8;
	  case 0x8D: SET_BIT(REG_L, 1); return 8;
	  case 0x8E:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 1);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0x97: SET_BIT(REG_A, 2); return 8;
	  case 0x90: SET_BIT(REG_B, 2); return 8;
	  case 0x91: SET_BIT(REG_C, 2); return 8;
	  case 0x92: SET_BIT(REG_D, 2); return 8;
	  case 0x93: SET_BIT(REG_E, 2); return 8;
	  case 0x94: SET_BIT(REG_H, 2); return 8;
	  case 0x95: SET_BIT(REG_L, 2); return 8;
	  case 0x96:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 2);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0x9F: SET_BIT(REG_A, 3); return 8;
	  case 0x98: SET_BIT(REG_B, 3); return 8;
	  case 0x99: SET_BIT(REG_C, 3); return 8;
	  case 0x9A: SET_BIT(REG_D, 3); return 8;
	  case 0x9B: SET_BIT(REG_E, 3); return 8;
	  case 0x9C: SET_BIT(REG_H, 3); return 8;
	  case 0x9D: SET_BIT(REG_L, 3); return 8;
	  case 0x9E:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 3);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xA7: SET_BIT(REG_A, 4); return 8;
	  case 0xA0: SET_BIT(REG_B, 4); return 8;
	  case 0xA1: SET_BIT(REG_C, 4); return 8;
	  case 0xA2: SET_BIT(REG_D, 4); return 8;
	  case 0xA3: SET_BIT(REG_E, 4); return 8;
	  case 0xA4: SET_BIT(REG_H, 4); return 8;
	  case 0xA5: SET_BIT(REG_L, 4); return 8;
	  case 0xA6:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 4);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xAF: SET_BIT(REG_A, 5); return 8;
	  case 0xA8: SET_BIT(REG_B, 5); return 8;
	  case 0xA9: SET_BIT(REG_C, 5); return 8;
	  case 0xAA: SET_BIT(REG_D, 5); return 8;
	  case 0xAB: SET_BIT(REG_E, 5); return 8;
	  case 0xAC: SET_BIT(REG_H, 5); return 8;
	  case 0xAD: SET_BIT(REG_L, 5); return 8;
	  case 0xAE:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 5);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xB7: SET_BIT(REG_A, 6); return 8;
	  case 0xB0: SET_BIT(REG_B, 6); return 8;
	  case 0xB1: SET_BIT(REG_C, 6); return 8;
	  case 0xB2: SET_BIT(REG_D, 6); return 8;
	  case 0xB3: SET_BIT(REG_E, 6); return 8;
	  case 0xB4: SET_BIT(REG_H, 6); return 8;
	  case 0xB5: SET_BIT(REG_L, 6); return 8;
	  case 0xB6:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 6);
	    WriteMem(mHL.a, tmpB);
	    return 16;
	  case 0xBF: SET_BIT(REG_A, 7); return 8;
	  case 0xB8: SET_BIT(REG_B, 7); return 8;
	  case 0xB9: SET_BIT(REG_C, 7); return 8;
	  case 0xBA: SET_BIT(REG_D, 7); return 8;
	  case 0xBB: SET_BIT(REG_E, 7); return 8;
	  case 0xBC: SET_BIT(REG_H, 7); return 8;
	  case 0xBD: SET_BIT(REG_L, 7); return 8;
	  case 0xBE:
	    tmpB = ReadMem(mHL.a);
	    SET_BIT(tmpB, 7);
	    WriteMem(mHL.a, tmpB);
	    return 16;

	  default:
	    std::cout << "Unknown opcode :" << opcode << "." << extOpcode << std::endl;
	    return 1;
	  }
      }

    default:
      std::cout << "Unknown opcode :" << opcode << std::endl;
      return 1;
    }
}
