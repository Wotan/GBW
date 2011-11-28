#include <stdio.h>
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
    case 0x7E: REG_A = ReadMem(REG_HL); return 8;
    case 0x40: REG_B = REG_B; return 4;
    case 0x41: REG_B = REG_C; return 4;
    case 0x42: REG_B = REG_D; return 4;
    case 0x43: REG_B = REG_E; return 4;
    case 0x44: REG_B = REG_H; return 4;
    case 0x45: REG_B = REG_L; return 4;
    case 0x46: REG_B = ReadMem(REG_HL); return 8;
    case 0x48: REG_C = REG_B; return 4;
    case 0x49: REG_C = REG_C; return 4;
    case 0x4A: REG_C = REG_D; return 4;
    case 0x4B: REG_C = REG_E; return 4;
    case 0x4C: REG_C = REG_H; return 4;
    case 0x4D: REG_C = REG_L; return 4;
    case 0x4E: REG_C = ReadMem(REG_HL); return 8;
    case 0x50: REG_D = REG_B; return 4;

    case 0x51: REG_D = REG_C; return 4;
    case 0x52: REG_D = REG_D; return 4;
    case 0x53: REG_D = REG_E; return 4;
    case 0x54: REG_D = REG_H; return 4;
    case 0x55: REG_D = REG_L; return 4;
    case 0x56: REG_D = ReadMem(REG_HL); return 8;
    case 0x58: REG_E = REG_B; return 4;
    case 0x59: REG_E = REG_C; return 4;
    case 0x5A: REG_E = REG_D; return 4;
    case 0x5B: REG_E = REG_E; return 4;
    case 0x5C: REG_E = REG_H; return 4;
    case 0x5D: REG_E = REG_L; return 4;
    case 0x5E: REG_E = ReadMem(REG_HL); return 8;
    case 0x60: REG_H = REG_B; return 4;
    case 0x61: REG_H = REG_C; return 4;
    case 0x62: REG_H = REG_D; return 4;
    case 0x63: REG_H = REG_E; return 4;
    case 0x64: REG_H = REG_H; return 4;
    case 0x65: REG_H = REG_L; return 4;
    case 0x66: REG_H = ReadMem(REG_HL); return 8;
    case 0x68: REG_L = REG_B; return 4;
    case 0x69: REG_L = REG_C; return 4;
    case 0x6A: REG_L = REG_D; return 4;
    case 0x6B: REG_L = REG_E; return 4;
    case 0x6C: REG_L = REG_H; return 4;
    case 0x6D: REG_L = REG_L; return 4;
    case 0x6E: REG_L = ReadMem(REG_HL); return 8;
    case 0x70: WriteMem(REG_HL, REG_B); return 8;
    case 0x71: WriteMem(REG_HL, REG_C); return 8;
    case 0x72: WriteMem(REG_HL, REG_D); return 8;
    case 0x73: WriteMem(REG_HL, REG_E); return 8;
    case 0x74: WriteMem(REG_HL, REG_H); return 8;
    case 0x75: WriteMem(REG_HL, REG_L); return 8;
    case 0x36: WriteMem(REG_HL, ReadMem(mPC++)); return 12;

    case 0x0A: REG_A = ReadMem(REG_BC); return 8;
    case 0x1A: REG_A = ReadMem(REG_DE); return 8;

    case 0xFA:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      REG_A = ReadMem(tmp.a);
      return 16;
    case 0x3E: REG_A = ReadMem(mPC++); return 8;
    case 0x47: REG_B = REG_A; return 4;
    case 0x4F: REG_C = REG_A; return 4;
    case 0x57: REG_D = REG_A; return 4;
    case 0x5F: REG_E = REG_A; return 4;
    case 0x67: REG_H = REG_A; return 4;
    case 0x6F: REG_L = REG_A; return 4;
    case 0x02: WriteMem(REG_BC, REG_A); return 8;
    case 0x12: WriteMem(REG_DE, REG_A); return 8;
    case 0x77: WriteMem(REG_HL, REG_A); return 8;

    case 0xEA:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      WriteMem(tmp.a, REG_A);
      return 16;
    case 0xF2: REG_A = ReadMem(0xFF00 + REG_C); return 8;
    case 0xE2: WriteMem(0xFF00 + REG_C, REG_A); return 8;
    case 0x3A:
      REG_A = ReadMem(REG_HL);
      REG_HL--;
      return 8;
   case 0x32:
      WriteMem(REG_HL, REG_A);
      REG_HL--;
      return 8;
    case 0x2A:
      REG_A = ReadMem(REG_HL);
      REG_HL++;
      return 8;
    case 0x22:
      WriteMem(REG_HL, REG_A);
      REG_HL++;
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
      REG_HL = tmp.a;
      return 12;
    case 0x31:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      mSP = tmp.a;
      return 12;
    case 0xF9:
      mSP = REG_HL;
      return 8;
    case 0xF8:
      Load16bitHL();
      return 12;
    case 0x08:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      WriteMem(tmp.a, mSP);
      return 20;

    case 0xF5: Push(REG_AF); return 16;
    case 0xC5: Push(REG_BC); return 16;
    case 0xD5: Push(REG_DE); return 16;
    case 0xE5: Push(REG_HL); return 16;
    case 0xF1: REG_AF = Pop(); return 12;
    case 0xC1: REG_BC = Pop(); return 12;
    case 0xD1: REG_DE = Pop(); return 12;
    case 0xE1: REG_HL = Pop(); return 12;

    case 0x87: ADD_8Bit(REG_A, REG_A, false); return 4;
    case 0x80: ADD_8Bit(REG_A, REG_B, false); return 4;
    case 0x81: ADD_8Bit(REG_A, REG_C, false); return 4;
    case 0x82: ADD_8Bit(REG_A, REG_D, false); return 4;
    case 0x83: ADD_8Bit(REG_A, REG_E, false); return 4;
    case 0x84: ADD_8Bit(REG_A, REG_H, false); return 4;
    case 0x85: ADD_8Bit(REG_A, REG_L, false); return 4;
    case 0x86: ADD_8Bit(REG_A, ReadMem(REG_HL), false); return 8;
    case 0xC6: ADD_8Bit(REG_A, ReadMem(mPC++), false); return 8;

    case 0x8F: ADD_8Bit(REG_A, REG_A, true); return 4;
    case 0x88: ADD_8Bit(REG_A, REG_B, true); return 4;
    case 0x89: ADD_8Bit(REG_A, REG_C, true); return 4;
    case 0x8A: ADD_8Bit(REG_A, REG_D, true); return 4;
    case 0x8B: ADD_8Bit(REG_A, REG_E, true); return 4;
    case 0x8C: ADD_8Bit(REG_A, REG_H, true); return 4;
    case 0x8D: ADD_8Bit(REG_A, REG_L, true); return 4;
    case 0x8E: ADD_8Bit(REG_A, ReadMem(REG_HL), true); return 8;
    case 0xCE: ADD_8Bit(REG_A, ReadMem(mPC++), true); return 8;

    case 0x97: SUB_8Bit(REG_A, REG_A, false); return 4;
    case 0x90: SUB_8Bit(REG_A, REG_B, false); return 4;
    case 0x91: SUB_8Bit(REG_A, REG_C, false); return 4;
    case 0x92: SUB_8Bit(REG_A, REG_D, false); return 4;
    case 0x93: SUB_8Bit(REG_A, REG_E, false); return 4;
    case 0x94: SUB_8Bit(REG_A, REG_H, false); return 4;
    case 0x95: SUB_8Bit(REG_A, REG_L, false); return 4;
    case 0x96: SUB_8Bit(REG_A, ReadMem(REG_HL), false); return 8;
    case 0xD6: SUB_8Bit(REG_A, ReadMem(mPC++), false); return 8;

    case 0x9F: SUB_8Bit(REG_A, REG_A, true); return 4;
    case 0x98: SUB_8Bit(REG_A, REG_B, true); return 4;
    case 0x99: SUB_8Bit(REG_A, REG_C, true); return 4;
    case 0x9A: SUB_8Bit(REG_A, REG_D, true); return 4;
    case 0x9B: SUB_8Bit(REG_A, REG_E, true); return 4;
    case 0x9C: SUB_8Bit(REG_A, REG_H, true); return 4;
    case 0x9D: SUB_8Bit(REG_A, REG_L, true); return 4;
    case 0x9E: SUB_8Bit(REG_A, ReadMem(REG_HL), true); return 8;
    case 0xDE: SUB_8Bit(REG_A, ReadMem(mPC++), true); return 8;

    case 0xA7: AND_8Bit(REG_A, REG_A); return 4;
    case 0xA0: AND_8Bit(REG_A, REG_B); return 4;
    case 0xA1: AND_8Bit(REG_A, REG_C); return 4;
    case 0xA2: AND_8Bit(REG_A, REG_D); return 4;
    case 0xA3: AND_8Bit(REG_A, REG_E); return 4;
    case 0xA4: AND_8Bit(REG_A, REG_H); return 4;
    case 0xA5: AND_8Bit(REG_A, REG_L); return 4;
    case 0xA6: AND_8Bit(REG_A, ReadMem(REG_HL)); return 8;
    case 0xE6: AND_8Bit(REG_A, ReadMem(mPC++)); return 8;

    case 0xB7: OR_8Bit(REG_A, REG_A); return 4;
    case 0xB0: OR_8Bit(REG_A, REG_B); return 4;
    case 0xB1: OR_8Bit(REG_A, REG_C); return 4;
    case 0xB2: OR_8Bit(REG_A, REG_D); return 4;
    case 0xB3: OR_8Bit(REG_A, REG_E); return 4;
    case 0xB4: OR_8Bit(REG_A, REG_H); return 4;
    case 0xB5: OR_8Bit(REG_A, REG_L); return 4;
    case 0xB6: OR_8Bit(REG_A, ReadMem(REG_HL)); return 8;
    case 0xF6: OR_8Bit(REG_A, ReadMem(mPC++)); return 8;

    case 0xAF: XOR_8Bit(REG_A, REG_A); return 4;
    case 0xA8: XOR_8Bit(REG_A, REG_B); return 4;
    case 0xA9: XOR_8Bit(REG_A, REG_C); return 4;
    case 0xAA: XOR_8Bit(REG_A, REG_D); return 4;
    case 0xAB: XOR_8Bit(REG_A, REG_E); return 4;
    case 0xAC: XOR_8Bit(REG_A, REG_H); return 4;
    case 0xAD: XOR_8Bit(REG_A, REG_L); return 4;
    case 0xAE: XOR_8Bit(REG_A, ReadMem(REG_HL)); return 8;
    case 0xEE: XOR_8Bit(REG_A, ReadMem(mPC++)); return 8;

    case 0xBF: CP_8Bit(REG_A, REG_A); return 4;
    case 0xB8: CP_8Bit(REG_A, REG_B); return 4;
    case 0xB9: CP_8Bit(REG_A, REG_C); return 4;
    case 0xBA: CP_8Bit(REG_A, REG_D); return 4;
    case 0xBB: CP_8Bit(REG_A, REG_E); return 4;
    case 0xBC: CP_8Bit(REG_A, REG_H); return 4;
    case 0xBD: CP_8Bit(REG_A, REG_L); return 4;
    case 0xBE: CP_8Bit(REG_A, ReadMem(REG_HL)); return 8;
    case 0xFE: CP_8Bit(REG_A, ReadMem(mPC++)); return 8;

    case 0x3C: INC_8Bit(REG_A); return 4;
    case 0x04: INC_8Bit(REG_B); return 4;
    case 0x0C: INC_8Bit(REG_C); return 4;
    case 0x14: INC_8Bit(REG_D); return 4;
    case 0x1C: INC_8Bit(REG_E); return 4;
    case 0x24: INC_8Bit(REG_H); return 4;
    case 0x2C: INC_8Bit(REG_L); return 4;
    case 0x34:
      tmpB = ReadMem(REG_HL);
      INC_8Bit(tmpB);
      WriteMem(REG_HL, tmpB);
      return 12;

    case 0x3D: DEC_8Bit(REG_A); return 4;
    case 0x05: DEC_8Bit(REG_B); return 4;
    case 0x0D: DEC_8Bit(REG_C); return 4;
    case 0x15: DEC_8Bit(REG_D); return 4;
    case 0x1D: DEC_8Bit(REG_E); return 4;
    case 0x25: DEC_8Bit(REG_H); return 4;
    case 0x2D: DEC_8Bit(REG_L); return 4;
    case 0x35:
      tmpB = ReadMem(REG_HL);
      DEC_8Bit(tmpB);
      WriteMem(REG_HL, tmpB);
      return 12;

    case 0x09: ADD_16bit(REG_HL, mBC.a); return 8;
    case 0x19: ADD_16bit(REG_HL, mDE.a); return 8;
    case 0x29: ADD_16bit(REG_HL, REG_HL); return 8;
    case 0x39: ADD_16bit(REG_HL, mSP); return 8;
    case 0xE8: ADD_16bitSigned(mSP, ReadMem(mPC++)); return 16;

    case 0x03: REG_BC++; return 8;
    case 0x13: REG_DE++; return 8;
    case 0x23: REG_HL++; return 8;
    case 0x33: mSP++; return 8;
    case 0x0B: REG_BC--; return 8;
    case 0x1B: REG_DE--; return 8;
    case 0x2B: REG_HL--; return 8;
    case 0x3B: mSP--; return 8;
    case 0x27: DDA_8Bit(REG_A); return 4;

    case 0x2F:
      N_F = 1;
      H_F = 1;
      REG_A ^= 0xFF;
      return 4;
    case 0x3F:
      N_F = 0;
      H_F = 0;
      if (IS_BIT_SET(REG_F, F_C))
	C_F = 0;
      else
	C_F = 1;
      return 4;
    case 0x37:
      N_F = 0;
      H_F = 0;
      C_F = 0;
      return 4;

    case 0x00: return 4;
    case 0x76: Halt(); return 4;
    case 0xF3: ToggleInt(false); return 4;
    case 0xFB: ToggleInt(true); return 4;

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
    case 0xE9: mPC = REG_HL; return 4;

    case 0x18:
      mPC += (SBYTE)ReadMem(mPC) + 1;
      return 8;

    case 0x20:
      mPC += !IS_BIT_SET(REG_F, F_Z) ? (SBYTE)ReadMem(mPC) + 1 : 1;
      return 8;
    case 0x28:
      mPC += IS_BIT_SET(REG_F, F_Z) ? (SBYTE)ReadMem(mPC) + 1 : 1;
      return 8;
    case 0x30:
      mPC += !IS_BIT_SET(REG_F, F_C) ? (SBYTE)ReadMem(mPC) + 1 : 1;
      return 8;
    case 0x38:
      mPC += IS_BIT_SET(REG_F, F_C) ? (SBYTE)ReadMem(mPC) + 1 : 1;
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
    case 0xC7: Push(mPC); mPC = 0x00; return 32;
    case 0xCF: Push(mPC); mPC = 0x08; return 32;
    case 0xD7: Push(mPC); mPC = 0x10; return 32;
    case 0xDF: Push(mPC); mPC = 0x18; return 32;
    case 0xE7: Push(mPC); mPC = 0x20; return 32;
    case 0xEF: Push(mPC); mPC = 0x28; return 32;
    case 0xF7: Push(mPC); mPC = 0x30; return 32;
    case 0xFF: Push(mPC); mPC = 0x38; return 32;

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
	    tmpB = ReadMem(REG_HL);
	    SWAP_8bit(tmpB);
	    WriteMem(REG_HL, tmpB);
	    return 16;

	  case 0x07: RotateLeft_8bit(REG_A, false); return 8;
	  case 0x00: RotateLeft_8bit(REG_B, false); return 8;
	  case 0x01: RotateLeft_8bit(REG_C, false); return 8;
	  case 0x02: RotateLeft_8bit(REG_D, false); return 8;
	  case 0x03: RotateLeft_8bit(REG_E, false); return 8;
	  case 0x04: RotateLeft_8bit(REG_H, false); return 8;
	  case 0x05: RotateLeft_8bit(REG_L, false); return 8;
	  case 0x06:
	    tmpB = ReadMem(REG_HL);
	    RotateLeft_8bit(tmpB, false);
	    WriteMem(REG_HL, tmpB);
	    return 16;

	  case 0x17: RotateLeft_8bit(REG_A, true); return 8;
	  case 0x10: RotateLeft_8bit(REG_B, true); return 8;
	  case 0x11: RotateLeft_8bit(REG_C, true); return 8;
	  case 0x12: RotateLeft_8bit(REG_D, true); return 8;
	  case 0x13: RotateLeft_8bit(REG_E, true); return 8;
	  case 0x14: RotateLeft_8bit(REG_H, true); return 8;
	  case 0x15: RotateLeft_8bit(REG_L, true); return 8;
	  case 0x16:
	    tmpB = ReadMem(REG_HL);
	    RotateLeft_8bit(tmpB, true);
	    WriteMem(REG_HL, tmpB);
	    return 16;

	  case 0x0F: RotateRight_8bit(REG_A, false); return 8;
	  case 0x08: RotateRight_8bit(REG_B, false); return 8;
	  case 0x09: RotateRight_8bit(REG_C, false); return 8;
	  case 0x0A: RotateRight_8bit(REG_D, false); return 8;
	  case 0x0B: RotateRight_8bit(REG_E, false); return 8;
	  case 0x0C: RotateRight_8bit(REG_H, false); return 8;
	  case 0x0D: RotateRight_8bit(REG_L, false); return 8;
	  case 0x0E:
	    tmpB = ReadMem(REG_HL);
	    RotateRight_8bit(tmpB, false);
	    WriteMem(REG_HL, tmpB);
	    return 16;

	  case 0x1F: RotateRight_8bit(REG_A, true); return 8;
	  case 0x18: RotateRight_8bit(REG_B, true); return 8;
	  case 0x19: RotateRight_8bit(REG_C, true); return 8;
	  case 0x1A: RotateRight_8bit(REG_D, true); return 8;
	  case 0x1B: RotateRight_8bit(REG_E, true); return 8;
	  case 0x1C: RotateRight_8bit(REG_H, true); return 8;
	  case 0x1D: RotateRight_8bit(REG_L, true); return 8;
	  case 0x1E:
	    tmpB = ReadMem(REG_HL);
	    RotateRight_8bit(tmpB, true);
	    WriteMem(REG_HL, tmpB);
	    return 16;

	  case 0x27: ShiftLeft_8bit(REG_A); return 8;
	  case 0x20: ShiftLeft_8bit(REG_B); return 8;
	  case 0x21: ShiftLeft_8bit(REG_C); return 8;
	  case 0x22: ShiftLeft_8bit(REG_D); return 8;
	  case 0x23: ShiftLeft_8bit(REG_E); return 8;
	  case 0x24: ShiftLeft_8bit(REG_H); return 8;
	  case 0x25: ShiftLeft_8bit(REG_L); return 8;
	  case 0x26:
	    tmpB = ReadMem(REG_HL);
	    ShiftLeft_8bit(tmpB);
	    WriteMem(REG_HL, tmpB);
	    return 16;

	  case 0x2F: ShiftRight_8bit(REG_A, false); return 8;
	  case 0x28: ShiftRight_8bit(REG_B, false); return 8;
	  case 0x29: ShiftRight_8bit(REG_C, false); return 8;
	  case 0x2A: ShiftRight_8bit(REG_D, false); return 8;
	  case 0x2B: ShiftRight_8bit(REG_E, false); return 8;
	  case 0x2C: ShiftRight_8bit(REG_H, false); return 8;
	  case 0x2D: ShiftRight_8bit(REG_L, false); return 8;
	  case 0x2E:
	    tmpB = ReadMem(REG_HL);
	    ShiftRight_8bit(tmpB, false);
	    WriteMem(REG_HL, tmpB);
	    return 16;

	  case 0x3F: ShiftRight_8bit(REG_A, true); return 8;
	  case 0x38: ShiftRight_8bit(REG_B, true); return 8;
	  case 0x39: ShiftRight_8bit(REG_C, true); return 8;
	  case 0x3A: ShiftRight_8bit(REG_D, true); return 8;
	  case 0x3B: ShiftRight_8bit(REG_E, true); return 8;
	  case 0x3C: ShiftRight_8bit(REG_H, true); return 8;
	  case 0x3D: ShiftRight_8bit(REG_L, true); return 8;
	  case 0x3E:
	    tmpB = ReadMem(REG_HL);
	    ShiftRight_8bit(tmpB, true);
	    WriteMem(REG_HL, tmpB);
	    return 16;

	  case 0x47: TestBit(REG_A, 0); return 8;
	  case 0x40: TestBit(REG_B, 0); return 8;
	  case 0x41: TestBit(REG_C, 0); return 8;
	  case 0x42: TestBit(REG_D, 0); return 8;
	  case 0x43: TestBit(REG_E, 0); return 8;
	  case 0x44: TestBit(REG_H, 0); return 8;
	  case 0x45: TestBit(REG_L, 0); return 8;
	  case 0x46: TestBit(ReadMem(REG_HL), 0); return 16;
	  case 0x4F: TestBit(REG_A, 1); return 8;
	  case 0x48: TestBit(REG_B, 1); return 8;
	  case 0x49: TestBit(REG_C, 1); return 8;
	  case 0x4A: TestBit(REG_D, 1); return 8;
	  case 0x4B: TestBit(REG_E, 1); return 8;
	  case 0x4C: TestBit(REG_H, 1); return 8;
	  case 0x4D: TestBit(REG_L, 1); return 8;
	  case 0x4E: TestBit(ReadMem(REG_HL), 1); return 16;
	  case 0x57: TestBit(REG_A, 2); return 8;
	  case 0x50: TestBit(REG_B, 2); return 8;
	  case 0x51: TestBit(REG_C, 2); return 8;
	  case 0x52: TestBit(REG_D, 2); return 8;
	  case 0x53: TestBit(REG_E, 2); return 8;
	  case 0x54: TestBit(REG_H, 2); return 8;
	  case 0x55: TestBit(REG_L, 2); return 8;
	  case 0x56: TestBit(ReadMem(REG_HL), 2); return 16;
	  case 0x5F: TestBit(REG_A, 3); return 8;
	  case 0x58: TestBit(REG_B, 3); return 8;
	  case 0x59: TestBit(REG_C, 3); return 8;
	  case 0x5A: TestBit(REG_D, 3); return 8;
	  case 0x5B: TestBit(REG_E, 3); return 8;
	  case 0x5C: TestBit(REG_H, 3); return 8;
	  case 0x5D: TestBit(REG_L, 3); return 8;
	  case 0x5E: TestBit(ReadMem(REG_HL), 3); return 16;
	  case 0x67: TestBit(REG_A, 4); return 8;
	  case 0x60: TestBit(REG_B, 4); return 8;
	  case 0x61: TestBit(REG_C, 4); return 8;
	  case 0x62: TestBit(REG_D, 4); return 8;
	  case 0x63: TestBit(REG_E, 4); return 8;
	  case 0x64: TestBit(REG_H, 4); return 8;
	  case 0x65: TestBit(REG_L, 4); return 8;
	  case 0x66: TestBit(ReadMem(REG_HL), 4); return 16;
	  case 0x6F: TestBit(REG_A, 5); return 8;
	  case 0x68: TestBit(REG_B, 5); return 8;
	  case 0x69: TestBit(REG_C, 5); return 8;
	  case 0x6A: TestBit(REG_D, 5); return 8;
	  case 0x6B: TestBit(REG_E, 5); return 8;
	  case 0x6C: TestBit(REG_H, 5); return 8;
	  case 0x6D: TestBit(REG_L, 5); return 8;
	  case 0x6E: TestBit(ReadMem(REG_HL), 5); return 16;
	  case 0x77: TestBit(REG_A, 6); return 8;
	  case 0x70: TestBit(REG_B, 6); return 8;
	  case 0x71: TestBit(REG_C, 6); return 8;
	  case 0x72: TestBit(REG_D, 6); return 8;
	  case 0x73: TestBit(REG_E, 6); return 8;
	  case 0x74: TestBit(REG_H, 6); return 8;
	  case 0x75: TestBit(REG_L, 6); return 8;
	  case 0x76: TestBit(ReadMem(REG_HL), 6); return 16;
	  case 0x7F: TestBit(REG_A, 7); return 8;
	  case 0x78: TestBit(REG_B, 7); return 8;
	  case 0x79: TestBit(REG_C, 7); return 8;
	  case 0x7A: TestBit(REG_D, 7); return 8;
	  case 0x7B: TestBit(REG_E, 7); return 8;
	  case 0x7C: TestBit(REG_H, 7); return 8;
	  case 0x7D: TestBit(REG_L, 7); return 8;
	  case 0x7E: TestBit(ReadMem(REG_HL), 7); return 16;


	  case 0xC7: SET_BIT(REG_A, 0); return 8;
	  case 0xC0: SET_BIT(REG_B, 0); return 8;
	  case 0xC1: SET_BIT(REG_C, 0); return 8;
	  case 0xC2: SET_BIT(REG_D, 0); return 8;
	  case 0xC3: SET_BIT(REG_E, 0); return 8;
	  case 0xC4: SET_BIT(REG_H, 0); return 8;
	  case 0xC5: SET_BIT(REG_L, 0); return 8;
	  case 0xC6:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 0);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xCF: SET_BIT(REG_A, 1); return 8;
	  case 0xC8: SET_BIT(REG_B, 1); return 8;
	  case 0xC9: SET_BIT(REG_C, 1); return 8;
	  case 0xCA: SET_BIT(REG_D, 1); return 8;
	  case 0xCB: SET_BIT(REG_E, 1); return 8;
	  case 0xCC: SET_BIT(REG_H, 1); return 8;
	  case 0xCD: SET_BIT(REG_L, 1); return 8;
	  case 0xCE:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 1);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xD7: SET_BIT(REG_A, 2); return 8;
	  case 0xD0: SET_BIT(REG_B, 2); return 8;
	  case 0xD1: SET_BIT(REG_C, 2); return 8;
	  case 0xD2: SET_BIT(REG_D, 2); return 8;
	  case 0xD3: SET_BIT(REG_E, 2); return 8;
	  case 0xD4: SET_BIT(REG_H, 2); return 8;
	  case 0xD5: SET_BIT(REG_L, 2); return 8;
	  case 0xD6:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 2);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xDF: SET_BIT(REG_A, 3); return 8;
	  case 0xD8: SET_BIT(REG_B, 3); return 8;
	  case 0xD9: SET_BIT(REG_C, 3); return 8;
	  case 0xDA: SET_BIT(REG_D, 3); return 8;
	  case 0xDB: SET_BIT(REG_E, 3); return 8;
	  case 0xDC: SET_BIT(REG_H, 3); return 8;
	  case 0xDD: SET_BIT(REG_L, 3); return 8;
	  case 0xDE:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 3);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xE7: SET_BIT(REG_A, 4); return 8;
	  case 0xE0: SET_BIT(REG_B, 4); return 8;
	  case 0xE1: SET_BIT(REG_C, 4); return 8;
	  case 0xE2: SET_BIT(REG_D, 4); return 8;
	  case 0xE3: SET_BIT(REG_E, 4); return 8;
	  case 0xE4: SET_BIT(REG_H, 4); return 8;
	  case 0xE5: SET_BIT(REG_L, 4); return 8;
	  case 0xE6:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 4);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xEF: SET_BIT(REG_A, 5); return 8;
	  case 0xE8: SET_BIT(REG_B, 5); return 8;
	  case 0xE9: SET_BIT(REG_C, 5); return 8;
	  case 0xEA: SET_BIT(REG_D, 5); return 8;
	  case 0xEB: SET_BIT(REG_E, 5); return 8;
	  case 0xEC: SET_BIT(REG_H, 5); return 8;
	  case 0xED: SET_BIT(REG_L, 5); return 8;
	  case 0xEE:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 5);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xF7: SET_BIT(REG_A, 6); return 8;
	  case 0xF0: SET_BIT(REG_B, 6); return 8;
	  case 0xF1: SET_BIT(REG_C, 6); return 8;
	  case 0xF2: SET_BIT(REG_D, 6); return 8;
	  case 0xF3: SET_BIT(REG_E, 6); return 8;
	  case 0xF4: SET_BIT(REG_H, 6); return 8;
	  case 0xF5: SET_BIT(REG_L, 6); return 8;
	  case 0xF6:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 6);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xFF: SET_BIT(REG_A, 7); return 8;
	  case 0xF8: SET_BIT(REG_B, 7); return 8;
	  case 0xF9: SET_BIT(REG_C, 7); return 8;
	  case 0xFA: SET_BIT(REG_D, 7); return 8;
	  case 0xFB: SET_BIT(REG_E, 7); return 8;
	  case 0xFC: SET_BIT(REG_H, 7); return 8;
	  case 0xFD: SET_BIT(REG_L, 7); return 8;
	  case 0xFE:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 7);
	    WriteMem(REG_HL, tmpB);
	    return 16;

	  case 0x87: SET_BIT(REG_A, 0); return 8;
	  case 0x80: SET_BIT(REG_B, 0); return 8;
	  case 0x81: SET_BIT(REG_C, 0); return 8;
	  case 0x82: SET_BIT(REG_D, 0); return 8;
	  case 0x83: SET_BIT(REG_E, 0); return 8;
	  case 0x84: SET_BIT(REG_H, 0); return 8;
	  case 0x85: SET_BIT(REG_L, 0); return 8;
	  case 0x86:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 0);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0x8F: SET_BIT(REG_A, 1); return 8;
	  case 0x88: SET_BIT(REG_B, 1); return 8;
	  case 0x89: SET_BIT(REG_C, 1); return 8;
	  case 0x8A: SET_BIT(REG_D, 1); return 8;
	  case 0x8B: SET_BIT(REG_E, 1); return 8;
	  case 0x8C: SET_BIT(REG_H, 1); return 8;
	  case 0x8D: SET_BIT(REG_L, 1); return 8;
	  case 0x8E:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 1);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0x97: SET_BIT(REG_A, 2); return 8;
	  case 0x90: SET_BIT(REG_B, 2); return 8;
	  case 0x91: SET_BIT(REG_C, 2); return 8;
	  case 0x92: SET_BIT(REG_D, 2); return 8;
	  case 0x93: SET_BIT(REG_E, 2); return 8;
	  case 0x94: SET_BIT(REG_H, 2); return 8;
	  case 0x95: SET_BIT(REG_L, 2); return 8;
	  case 0x96:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 2);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0x9F: SET_BIT(REG_A, 3); return 8;
	  case 0x98: SET_BIT(REG_B, 3); return 8;
	  case 0x99: SET_BIT(REG_C, 3); return 8;
	  case 0x9A: SET_BIT(REG_D, 3); return 8;
	  case 0x9B: SET_BIT(REG_E, 3); return 8;
	  case 0x9C: SET_BIT(REG_H, 3); return 8;
	  case 0x9D: SET_BIT(REG_L, 3); return 8;
	  case 0x9E:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 3);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xA7: SET_BIT(REG_A, 4); return 8;
	  case 0xA0: SET_BIT(REG_B, 4); return 8;
	  case 0xA1: SET_BIT(REG_C, 4); return 8;
	  case 0xA2: SET_BIT(REG_D, 4); return 8;
	  case 0xA3: SET_BIT(REG_E, 4); return 8;
	  case 0xA4: SET_BIT(REG_H, 4); return 8;
	  case 0xA5: SET_BIT(REG_L, 4); return 8;
	  case 0xA6:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 4);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xAF: SET_BIT(REG_A, 5); return 8;
	  case 0xA8: SET_BIT(REG_B, 5); return 8;
	  case 0xA9: SET_BIT(REG_C, 5); return 8;
	  case 0xAA: SET_BIT(REG_D, 5); return 8;
	  case 0xAB: SET_BIT(REG_E, 5); return 8;
	  case 0xAC: SET_BIT(REG_H, 5); return 8;
	  case 0xAD: SET_BIT(REG_L, 5); return 8;
	  case 0xAE:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 5);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xB7: SET_BIT(REG_A, 6); return 8;
	  case 0xB0: SET_BIT(REG_B, 6); return 8;
	  case 0xB1: SET_BIT(REG_C, 6); return 8;
	  case 0xB2: SET_BIT(REG_D, 6); return 8;
	  case 0xB3: SET_BIT(REG_E, 6); return 8;
	  case 0xB4: SET_BIT(REG_H, 6); return 8;
	  case 0xB5: SET_BIT(REG_L, 6); return 8;
	  case 0xB6:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 6);
	    WriteMem(REG_HL, tmpB);
	    return 16;
	  case 0xBF: SET_BIT(REG_A, 7); return 8;
	  case 0xB8: SET_BIT(REG_B, 7); return 8;
	  case 0xB9: SET_BIT(REG_C, 7); return 8;
	  case 0xBA: SET_BIT(REG_D, 7); return 8;
	  case 0xBB: SET_BIT(REG_E, 7); return 8;
	  case 0xBC: SET_BIT(REG_H, 7); return 8;
	  case 0xBD: SET_BIT(REG_L, 7); return 8;
	  case 0xBE:
	    tmpB = ReadMem(REG_HL);
	    SET_BIT(tmpB, 7);
	    WriteMem(REG_HL, tmpB);
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

inline void	Emulator::ADD_8Bit(BYTE &toAdd, BYTE add, bool addCarry)
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

inline void	Emulator::SUB_8Bit(BYTE &toSub, BYTE sub, bool addCarry)
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

inline void	Emulator::AND_8Bit(BYTE &toAnd, BYTE src)
{
  N_F = 0;
  H_F = 1;
  C_F = 0;
  Z_F = 0;

  toAnd &= src;
  Z_F = (toAnd == 0);
}

inline void	Emulator::OR_8Bit(BYTE &toOr, BYTE src)
{
  N_F = 0;
  H_F = 0;
  C_F = 0;
  Z_F = 0;

  toOr |= src;
  Z_F = (toOr == 0);
}

inline void	Emulator::XOR_8Bit(BYTE &toXor, BYTE src)
{
  N_F = H_F = C_F = 0;
  toXor ^= src;
  Z_F = !toXor;
}

inline void	Emulator::CP_8Bit(BYTE cp1, BYTE cp2)
{
  N_F = 1;
  Z_F = (cp1 == cp2);
  H_F = ((cp1 & 0xFF) < (cp2 & 0xFF));
  C_F = (cp1 < cp2);
}

inline void	Emulator::INC_8Bit(BYTE &toInc)
{
  N_F = 0;
  toInc++;
  H_F = ((toInc & 0x0F) == 0x0);
  Z_F = (toInc == 0);
}

inline void	Emulator::DEC_8Bit(BYTE &toDec)
{
  N_F = 1;
  toDec--;
  H_F = ((toDec & 0x0F) == 0xF);
  Z_F = (toDec == 0);
}

inline void	Emulator::ADD_16bit(WORD &toAdd, WORD add)
{
  N_F = 0;
  C_F = (toAdd + add > 0xFFFF);
  H_F = (((toAdd & 0x000F) + (add & 0x000F)) > 0x000F);
  toAdd += add;
}

inline void	Emulator::ADD_16bitSigned(WORD &toAdd, SBYTE add)
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

inline void	Emulator::SWAP_8bit(BYTE &toSwap)
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

inline void	Emulator::DDA_8Bit(BYTE &nbr)
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

inline void	Emulator::RotateRight_8bit(BYTE &data, bool throughtCarry)
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

inline void	Emulator::RotateLeft_8bit(BYTE &data, bool throughtCarry)
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

inline void	Emulator::ShiftLeft_8bit(BYTE &data)
{
  N_F = 0;
  H_F = 0;
  Z_F = 0;
  C_F = IS_BIT_SET(data, 7);
  data <<= 1;
  Z_F = (data == 0);
}

inline void	Emulator::ShiftRight_8bit(BYTE &data, bool MSB)
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

inline void	Emulator::TestBit(BYTE totest, BYTE n)
{
  Z_F = !IS_BIT_SET(totest, n);
  N_F = 0;
  H_F = 1;
}
