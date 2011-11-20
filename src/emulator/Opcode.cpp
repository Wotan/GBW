#include <iostream>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"

int	Emulator::DoOpcode()
{
  UWORD tmp;
  BYTE	tmpB;
  int	opcode = ReadMem(mPC);
  mPC++;
  switch (opcode)
    {
      /// LD nn,n
    case 0x06: // B, n
      REG_B = ReadMem(mPC++);
      return 8;
    case 0x0E: // C, n
      REG_C = ReadMem(mPC++);
      return 8;
    case 0x16: // D, n
      REG_D = ReadMem(mPC++);
      return 8;
    case 0x1E: // E, n
      REG_E = ReadMem(mPC++);
      return 8;
    case 0x26: // H, n
      REG_H = ReadMem(mPC++);
      return 8;
    case 0x2E: // L, n
      REG_L = ReadMem(mPC++);
      return 8;

      /// LD r1,r2
    case 0x7F:
      REG_A = REG_A;
      return 4;
    case 0x78:
      REG_A = REG_B;
      return 4;
    case 0x79:
      REG_A = REG_C;
      return 4;
    case 0x7A:
      REG_A = REG_D;
      return 4;
    case 0x7B:
      REG_A = REG_E;
      return 4;
    case 0x7C:
      REG_A = REG_H;
      return 4;
    case 0x7D:
      REG_A = REG_L;
      return 4;
    case 0x7E:
      REG_A = ReadMem(mHL.a);
      return 8;
    case 0x40:
      REG_B = REG_B;
      return 4;
    case 0x41:
      REG_B = REG_C;
      return 4;
    case 0x42:
      REG_B = REG_D;
      return 4;
    case 0x43:
      REG_B = REG_E;
      return 4;
    case 0x44:
      REG_B = REG_H;
      return 4;
    case 0x45:
      REG_B = REG_L;
      return 4;
    case 0x46:
      REG_B = ReadMem(mHL.a);
      return 8;
    case 0x48:
      REG_C = REG_B;
      return 4;
    case 0x49:
      REG_C = REG_C;
      return 4;
    case 0x4A:
      REG_C = REG_D;
      return 4;
    case 0x4B:
      REG_C = REG_E;
      return 4;
    case 0x4C:
      REG_C = REG_H;
      return 4;
    case 0x4D:
      REG_C = REG_L;
      return 4;
    case 0x4E:
      REG_C = ReadMem(mHL.a);
      return 8;
    case 0x50:
      REG_D = REG_B;
      return 4;

    case 0x51:
      REG_D = REG_C;
      return 4;
    case 0x52:
      REG_D = REG_D;
      return 4;
    case 0x53:
      REG_D = REG_E;
      return 4;
    case 0x54:
      REG_D = REG_H;
      return 4;
    case 0x55:
      REG_D = REG_L;
      return 4;
    case 0x56:
      REG_D = ReadMem(mHL.a);
      return 8;
    case 0x58:
      REG_E = REG_B;
      return 4;
    case 0x59:
      REG_E = REG_C;
      return 4;
    case 0x5A:
      REG_E = REG_D;
      return 4;
    case 0x5B:
      REG_E = REG_E;
      return 4;
    case 0x5C:
      REG_E = REG_H;
      return 4;
    case 0x5D:
      REG_E = REG_L;
      return 4;
    case 0x5E:
      REG_E = ReadMem(mHL.a);
      return 8;
    case 0x60:
      REG_H = REG_B;
      return 4;
    case 0x61:
      REG_H = REG_C;
      return 4;
    case 0x62:
      REG_H = REG_D;
      return 4;
    case 0x63:
      REG_H = REG_E;
      return 4;
    case 0x64:
      REG_H = REG_H;
      return 4;
    case 0x65:
      REG_H = REG_L;
      return 4;
    case 0x66:
      REG_H = ReadMem(mHL.a);
      return 8;
    case 0x68:
      REG_L = REG_B;
      return 4;
    case 0x69:
      REG_L = REG_C;
      return 4;
    case 0x6A:
      REG_L = REG_D;
      return 4;
    case 0x6B:
      REG_L = REG_E;
      return 4;
    case 0x6C:
      REG_L = REG_H;
      return 4;
    case 0x6D:
      REG_L = REG_L;
      return 4;
    case 0x6E:
      REG_L = ReadMem(mHL.a);
      return 8;
    case 0x70:
      WriteMem(mHL.a, REG_B);
      return 8;
    case 0x71:
      WriteMem(mHL.a, REG_C);
      return 8;
    case 0x72:
      WriteMem(mHL.a, REG_D);
      return 8;
    case 0x73:
      WriteMem(mHL.a, REG_E);
      return 8;
    case 0x74:
      WriteMem(mHL.a, REG_H);
      return 8;
    case 0x75:
      WriteMem(mHL.a, REG_L);
      return 8;
    case 0x36:
      WriteMem(mHL.a, ReadMem(mPC++));
    return 12;

    case 0x0A:
      REG_A = ReadMem(mBC.a);
      return 8;
    case 0x1A:
      REG_A = ReadMem(mDE.a);
      return 8;
    case 0xFA:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      WriteMem(REG_A, ReadMem(tmp.a));
      return 16;
    case 0x3E: // Warn
      REG_A = ReadMem(mPC++);
      return 8;
    case 0x47:
      REG_B = REG_A;
      return 4;
    case 0x4F:
      REG_C = REG_A;
      return 4;
    case 0x57:
      REG_D = REG_A;
      return 4;
    case 0x5F:
      REG_E = REG_A;
      return 4;
    case 0x67:
      REG_H = REG_A;
      return 4;
    case 0x6F:
      REG_L = REG_A;
      return 4;
    case 0x02:
      mBC.a = REG_A;
      return 8;
    case 0x12:
      mDE.a = REG_A;
      return 8;
    case 0x77:
      mBC.a = REG_A;
      return 8;

    case 0xEA:
      tmp.lo = ReadMem(mPC++);
      tmp.hi = ReadMem(mPC++);
      WriteMem(tmp.a, REG_A);
      return 16;
    case 0xF2:
      REG_A = ReadMem(0xFF00 + REG_C);
      return 8;
    case 0xE2:
      WriteMem(0xFF00 + REG_C, REG_A);
      return 8;
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

    case 0xF5:
      Push(mAF.a);
      return 16;
    case 0xC5:
      Push(mBC.a);
      return 16;
    case 0xD5:
      Push(mDE.a);
      return 16;
    case 0xE5:
      Push(mHL.a);
      return 16;
    case 0xF1:
      mAF.a = Pop();
      return 12;
    case 0xC1:
      mBC.a = Pop();
      return 12;
    case 0xD1:
      mDE.a = Pop();
      return 12;
    case 0xE1:
      mHL.a = Pop();
      return 12;

    case 0x87:
      ADD_8Bit(REG_A, REG_A, false);
      return 4;
    case 0x80:
      ADD_8Bit(REG_A, REG_B, false);
      return 4;
    case 0x81:
      ADD_8Bit(REG_A, REG_C, false);
      return 4;
    case 0x82:
      ADD_8Bit(REG_A, REG_D, false);
      return 4;
    case 0x83:
      ADD_8Bit(REG_A, REG_E, false);
      return 4;
    case 0x84:
      ADD_8Bit(REG_A, REG_H, false);
      return 4;
    case 0x85:
      ADD_8Bit(REG_A, REG_L, false);
      return 4;
    case 0x86:
      ADD_8Bit(REG_A, ReadMem(mHL.a), false);
      return 8;
    case 0xC6:
      ADD_8Bit(REG_A, ReadMem(mPC++), false);
      return 8;

    case 0x8F:
      ADD_8Bit(REG_A, REG_A, true);
      return 4;
    case 0x88:
      ADD_8Bit(REG_A, REG_B, true);
      return 4;
    case 0x89:
      ADD_8Bit(REG_A, REG_C, true);
      return 4;
    case 0x8A:
      ADD_8Bit(REG_A, REG_D, true);
      return 4;
    case 0x8B:
      ADD_8Bit(REG_A, REG_E, true);
      return 4;
    case 0x8C:
      ADD_8Bit(REG_A, REG_H, true);
      return 4;
    case 0x8D:
      ADD_8Bit(REG_A, REG_L, true);
      return 4;
    case 0x8E:
      ADD_8Bit(REG_A, ReadMem(mHL.a), true);
      return 8;
    case 0xCE:
      ADD_8Bit(REG_A, ReadMem(mPC++), true);
      return 8;

    case 0x97:
      SUB_8Bit(REG_A, REG_A, false);
      return 4;
    case 0x90:
      SUB_8Bit(REG_A, REG_B, false);
      return 4;
    case 0x91:
      SUB_8Bit(REG_A, REG_C, false);
      return 4;
    case 0x92:
      SUB_8Bit(REG_A, REG_D, false);
      return 4;
    case 0x93:
      SUB_8Bit(REG_A, REG_E, false);
      return 4;
    case 0x94:
      SUB_8Bit(REG_A, REG_H, false);
      return 4;
    case 0x95:
      SUB_8Bit(REG_A, REG_L, false);
      return 4;
    case 0x96:
      SUB_8Bit(REG_A, ReadMem(mHL.a), false);
      return 8;
    case 0xD6:
      SUB_8Bit(REG_A, ReadMem(mPC++), false);
      return 8;

    case 0x9F:
      SUB_8Bit(REG_A, REG_A, true);
      return 4;
    case 0x98:
      SUB_8Bit(REG_A, REG_B, true);
      return 4;
    case 0x99:
      SUB_8Bit(REG_A, REG_C, true);
      return 4;
    case 0x9A:
      SUB_8Bit(REG_A, REG_D, true);
      return 4;
    case 0x9B:
      SUB_8Bit(REG_A, REG_E, true);
      return 4;
    case 0x9C:
      SUB_8Bit(REG_A, REG_H, true);
      return 4;
    case 0x9D:
      SUB_8Bit(REG_A, REG_L, true);
      return 4;
    case 0x9E:
      SUB_8Bit(REG_A, ReadMem(mHL.a), true);
      return 8;
    case 0xDE:
      SUB_8Bit(REG_A, ReadMem(mPC++), true);
      return 8;

    case 0xA7:
      AND_8Bit(REG_A, REG_A);
      return 4;
    case 0xA0:
      AND_8Bit(REG_A, REG_B);
      return 4;
    case 0xA1:
      AND_8Bit(REG_A, REG_C);
      return 4;
    case 0xA2:
      AND_8Bit(REG_A, REG_D);
      return 4;
    case 0xA3:
      AND_8Bit(REG_A, REG_E);
      return 4;
    case 0xA4:
      AND_8Bit(REG_A, REG_H);
      return 4;
    case 0xA5:
      AND_8Bit(REG_A, REG_L);
      return 4;
    case 0xA6:
      AND_8Bit(REG_A, ReadMem(mHL.a));
      return 8;
    case 0xE6:
      AND_8Bit(REG_A, ReadMem(mPC++));
      return 8;

    case 0xB7:
      OR_8Bit(REG_A, REG_A);
      return 4;
    case 0xB0:
      OR_8Bit(REG_A, REG_B);
      return 4;
    case 0xB1:
      OR_8Bit(REG_A, REG_C);
      return 4;
    case 0xB2:
      OR_8Bit(REG_A, REG_D);
      return 4;
    case 0xB3:
      OR_8Bit(REG_A, REG_E);
      return 4;
    case 0xB4:
      OR_8Bit(REG_A, REG_H);
      return 4;
    case 0xB5:
      OR_8Bit(REG_A, REG_L);
      return 4;
    case 0xB6:
      OR_8Bit(REG_A, ReadMem(mHL.a));
      return 8;
    case 0xF6:
      OR_8Bit(REG_A, ReadMem(mPC++));
      return 8;

    case 0xAF:
      XOR_8Bit(REG_A, REG_A);
      return 4;
    case 0xA8:
      XOR_8Bit(REG_A, REG_B);
      return 4;
    case 0xA9:
      XOR_8Bit(REG_A, REG_C);
      return 4;
    case 0xAA:
      XOR_8Bit(REG_A, REG_D);
      return 4;
    case 0xAB:
      XOR_8Bit(REG_A, REG_E);
      return 4;
    case 0xAC:
      XOR_8Bit(REG_A, REG_H);
      return 4;
    case 0xAD:
      XOR_8Bit(REG_A, REG_L);
      return 4;
    case 0xAE:
      XOR_8Bit(REG_A, ReadMem(mHL.a));
      return 8;
    case 0xEE:
      XOR_8Bit(REG_A, ReadMem(mPC++));
      return 8;

    case 0xBF:
      CP_8Bit(REG_A, REG_A);
      return 4;
    case 0xB8:
      CP_8Bit(REG_A, REG_B);
      return 4;
    case 0xB9:
      CP_8Bit(REG_A, REG_C);
      return 4;
    case 0xBA:
      CP_8Bit(REG_A, REG_D);
      return 4;
    case 0xBB:
      CP_8Bit(REG_A, REG_E);
      return 4;
    case 0xBC:
      CP_8Bit(REG_A, REG_H);
      return 4;
    case 0xBD:
      CP_8Bit(REG_A, REG_L);
      return 4;
    case 0xBE:
      CP_8Bit(REG_A, ReadMem(mHL.a));
      return 8;
    case 0xFE:
      CP_8Bit(REG_A, ReadMem(mPC++));
      return 8;

    case 0x3C:
      INC_8Bit(REG_A);
      return 4;
    case 0x04:
      INC_8Bit(REG_B);
      return 4;
    case 0x0C:
      INC_8Bit(REG_C);
      return 4;
    case 0x14:
      INC_8Bit(REG_D);
      return 4;
    case 0x1C:
      INC_8Bit(REG_E);
      return 4;
    case 0x24:
      INC_8Bit(REG_H);
      return 4;
    case 0x2C:
      INC_8Bit(REG_L);
      return 4;
    case 0x34:
      tmpB = ReadMem(mHL.a);
      INC_8Bit(tmpB);
      WriteMem(mHL.a, tmpB);
      return 12;

    case 0x3D:
      DEC_8Bit(REG_A);
      return 4;
    case 0x05:
      DEC_8Bit(REG_B);
      return 4;
    case 0x0D:
      DEC_8Bit(REG_C);
      return 4;
    case 0x15:
      DEC_8Bit(REG_D);
      return 4;
    case 0x1D:
      DEC_8Bit(REG_E);
      return 4;
    case 0x25:
      DEC_8Bit(REG_H);
      return 4;
    case 0x2D:
      DEC_8Bit(REG_L);
      return 4;
    case 0x35:
      tmpB = ReadMem(mHL.a);
      DEC_8Bit(tmpB);
      WriteMem(mHL.a, tmpB);
      return 12;

    case 0x09:
      ADD_16bit(mHL.a, mBC.a);
      return 8;
    case 0x19:
      ADD_16bit(mHL.a, mDE.a);
      return 8;
    case 0x29:
      ADD_16bit(mHL.a, mHL.a);
      return 8;
    case 0x39:
      ADD_16bit(mHL.a, mSP);
      return 8;
    case 0xE8:
      ADD_16bitSigned(mSP, ReadMem(mPC++));
      return 16;

    case 0x03:
      mBC.a++;
      return 8;
    case 0x13:
      mDE.a++;
      return 8;
    case 0x23:
      mHL.a++;
      return 8;
    case 0x33:
      mSP++;
      return 8;
    case 0x0B:
      mBC.a--;
      return 8;
    case 0x1B:
      mDE.a--;
      return 8;
    case 0x2B:
      mHL.a--;
      return 8;
    case 0x3B:
      mSP--;
      return 8;




    default:
      std::cout << "Unknown opcode :" << opcode << std::endl;
      return 1;
    }
}
