#ifndef EMULATOR_HPP_
# define EMULATOR_HPP_

# include <inttypes.h>
# include "App.hpp"

# define BYTE uint8_t
# define WORD uint16_t

# define SBYTE int8_t
# define SWORD int16_t

# define SIZE_BANK 0x2000 // 16KB
# define MAX_BANK 128 // Maybe 256
# define MAX_SIZE_CARTRIDGE SIZE_BANK * MAX_BANK

# define IS_BIT_SET(x, n) ((x & (1 << n)))
# define SET_BIT(x, n) (x |= (1 << n))

# define RAM 1
# define ROM 0

class App;

enum romType
  {
    ONLY_ROM,
    MCB1,
    MCB2,
    MCB3
  };

typedef union
{
  struct
  {
    BYTE lo; // Lo first, little endian
    BYTE hi;
  };
  WORD	a; // All
} UWORD;

typedef struct
{
  char	Title[0xF];
  BYTE	CGBFlag;
  BYTE	CartridgeType;
  BYTE	ROMSize;
  BYTE	ROMBanks;
  BYTE  ExtRAMSize;
  BYTE	Jap; // 0 = Jap, 1 = Other
} CartridgeInfos;

class Emulator
{
public:
  Emulator(App *app);
  ~Emulator();
  bool	Init(const char *fileName);
  void	InitMem();
  void	InitReg();
  bool	LoadFile(const char *fileName);
  void	ReadCartridgeInfos();
  BYTE	ReadMem(WORD addr);
  void  WriteMem(WORD addr, BYTE value);
  void	DoCycle();
  void	DoFrame();
  void	Play();
  void	Pause();

private:
  // Infos //
  CartridgeInfos mInfos;

  // Registers //
  UWORD	mAF; // A = Low F = Hight
  UWORD	mBC;
  UWORD	mDE;
  UWORD	mHL;
  WORD	mPC;
  WORD	mSP; // Stack pointer

  // Memory //
  BYTE		mCurROMBank;
  BYTE		mMode;
  int		mCurRAMBank;
  bool		mRAMEnable;

  // All ROM (Cartridge)
  BYTE		*mCartridgeMem;

  // (03) 8000 - 9FFF
  BYTE		mVRAM[0x2000];

  // (04) A000 - BFFF (In cartdrige, may use for saving)
  BYTE		mExtRAM[0x2000 * 4]; // 4 bank * 8kB max (2kB or 8kB or 32kB)

  // (5) C000 - CFFF
  // (6) D000 - DFFF
  BYTE		mWRAM[0x1000 * 2];

  // (08) FE00 - FEFF
  BYTE		mOAM[0x100];

  // (10) FF00 - FF7F
  BYTE		mIOPorts[0x80];

  // (11) FF80 - FFFE
  BYTE		mHRAM[0x7F];

  // (12) FFFF
  BYTE		mInterrupEnable;

  App		*mApp;
};


/*
01  0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
02  4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
03  8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
04  A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
05  C000-CFFF   4KB Work RAM Bank 0 (WRAM)
06  D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
07  E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
08  FE00-FE9F   Sprite Attribute Table (OAM)
09  FEA0-FEFF   Not Usable
10  FF00-FF7F   I/O Ports
11  FF80-FFFE   High RAM (HRAM)
12  FFFF        Interrupt Enable Registers
*/
#endif // !EMULATOR_HPP_
