#ifndef EMULATOR_HPP_
# define EMULATOR_HPP_

# include <inttypes.h>
# include "App.hpp"



# define BYTE uint8_t
# define WORD uint16_t

# define SBYTE int8_t
# define SWORD int16_t

typedef union
{
  WORD	data;
  struct
  {
    BYTE Hi; // 8 Hight bits
    BYTE Lo; // 8 Low bits
  }
} uRegister;	// Register seems to be big endian
		// instead of other 16 bit value (?)

class Emulator
{
public:
  Emulator(App *app);
  void	Init(char *fileName);
  void	DoCycle();
  void	DoFrame();
  void	Play();
  void	Pause();

private:
  // Registers
  BYTE	mPC;
  BYTE	mSP; // Stack pointer

  // Memory
  BYTE	mCartridgeMem[0xFFFFFF];
  BYTE	mIntermalMem[];
};

#endif // !EMULATOR_HPP_
