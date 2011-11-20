#include <iostream>
#include <fstream>
#include "App.hpp"
#include "Emulator.hpp"

int	Emulator::DoOpcode()
{
  UWORD tmp;
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


    default:
      std::cout << "Unknown opcode :" << opcode << std::endl;
      return 1;
    }
}
