#include <iostream>
#include "Emulator.hpp"

void	Emulator::UpdateLCD(int nbCycles)
{

  if (!IS_BIT_SET(mIOPorts[0x40], 7)) // return if LCD not enabled
    return ;
  mLYCounter -= nbCycles;
  if (mLYCounter <= 0)
    {
      BYTE curLine = mIOPorts[0x44];

      if (curLine < 144)
	DrawLine(curLine);
      else if (curLine == 144)
	REQ_INT(VBLANK);
      if (curLine > 153) // Reset
	mIOPorts[0x44] = 0;
      else
	mIOPorts[0x44]++;
      mLYCounter = 456;
    }
}

void	Emulator::DrawLine(int curLine)
{

  DrawBG(curLine);
  if (IS_BIT_SET(mIOPorts[0x40], 1))
    DrawSprite(curLine);
}

void	Emulator::DrawSprite(int curLine)
{
  bool	is8X16 = IS_BIT_SET(mIOPorts[0x40], 2);
  char	*screen = mGraphics->GetScreenArrayPtr();
  BYTE	PX, PY;
  BYTE	tileId;
  BYTE	B1, B2;
  WORD tmp;

  for (int i = 0; i < 40 * 4; i += 4)
    {
      PY = mOAM[i] - 16;
      if (!(curLine >= PY && curLine < PY + (is8X16 ? 16 : 8)))
	continue ;
      PX = mOAM[i + 1] - 8;
      if (PX == 0 || PX >= 168)
	continue ;
      tileId = mOAM[i + 2];

      B1 = mVRAM[tileId * 16 + ((curLine - PY) * 2 + 0)];
      B2 = mVRAM[tileId * 16 + ((curLine - PY) * 2 + 1)];
      for (int j = 0; j < 8; j++)
	{
	  SetColor((int *)(screen + curLine * GB_SCREEN_X * 4 + PX + j * 4)
		   , IS_BIT_SET(B1, 7 - j)
		   | (IS_BIT_SET(B2, 7 - j) << 1), true);
	}

    }
}

// FF40 bit 6 Pattern window = 0;9800-9BFFF / 1;9C00 - 9FFF
// FF40 bit 3 Pattern BG = 9800-9BFFF / 9C00 - 9FFF
// FF40 bit 4 Tile data  = 8800-97FF / 8000-8FFF
void	Emulator::DrawBG(int curLine)
{
  signed int tileId;
  int	posY = mIOPorts[0x42] + curLine;
  int	posX = mIOPorts[0x43];
  WORD	tmp;
  char	*screen = mGraphics->GetScreenArrayPtr();
  int	addrTileData = IS_BIT_SET(mIOPorts[0x40], 4) ? 0x0 : 0x1000;
  int	addrBGPattern = IS_BIT_SET(mIOPorts[0x40], 3) ? 0x1C00 : 0x1800;

  posY %= 256;
  for (int i = 0; i < 160; i++)
    {
      posX %= 256;

      tileId = mVRAM[addrBGPattern + ((posY * 4) + posX / 8)];
      tmp = addrTileData + tileId * 16 + ((posY % 8) * 2);

      SetColor((int *)(screen + curLine * GB_SCREEN_X * 4 + i * 4),
      	       IS_BIT_SET(mVRAM[tmp], 7 - (posX % 8)) |
      	       (IS_BIT_SET(mVRAM[tmp + 1], 7 - (posX % 8)) << 1),
      	       false);
      posX++;
    }
}

inline void	Emulator::SetColor(int *scanLine, int spriteColor,
				   bool blankTransp)
{
  int	finalColor;
  Palette *palette = (Palette *)&mIOPorts[0x47];

  switch (spriteColor)
    {
    case 0: finalColor = palette->colorNum0; break;
    case 1: finalColor = palette->colorNum1; break;
    case 2: finalColor = palette->colorNum2; break;
    case 3: finalColor = 0; break;
    }
  switch (finalColor)
    {
    case 0: if (!blankTransp) *scanLine = 0xFFFFFFFF; break;
    case 1: *scanLine = 0x90909090; break;
    case 2: *scanLine = 0x50505050; break;
    case 3: *scanLine = 0x00000000; break;
    }
}
