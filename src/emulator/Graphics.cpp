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
  char	*curScanLine = mGraphics->GetScanLinePtr();
  BYTE	PX, PY;
  int	RPX, RPY;
  bool	bit0, bit1;
  BYTE tileId;
  BYTE B1, B2;

  for (int i = 0; i < 40 * 4; i += 4)
    {
      PY = mOAM[i];
      RPY = PY - 16;
      if (!(curLine >= RPY && curLine < RPY + (is8X16 ? 16 : 8)))
	continue ;
      PX = mOAM[i + 1];
      RPX = PX - 8;
      if (PX == 0 || PX >= 168)
	continue ;
      tileId = mOAM[i + 2];

      for (int j = 0; j < 8; j++)
	{
	  B1 = ReadMem(0x8000 + tileId * 16 + ((curLine - RPY) * 2 + 0));
	  B2 = ReadMem(0x8000 + tileId * 16 + ((curLine - RPY) * 2 + 1));

	  SetColor((int *)(curScanLine + RPX + j * 4), IS_BIT_SET(B1, 7 - j)
		   | (IS_BIT_SET(B2, 7 - j) << 1), true);
	}

    }
  mGraphics->DrawScanLine(curLine);
}

// FF40 bit 6 Pattern window = 0;9800-9BFFF / 1;9C00 - 9FFF
// FF40 bit 3 Pattern BG = 9800-9BFFF / 9C00 - 9FFF
// FF40 bit 4 Tile data  = 8800-97FF / 8000-8FFF
void	Emulator::DrawBG(int curLine)
{
  signed int tileId;
  bool	bit0, bit1;
  int	posY = mIOPorts[0x42] + curLine;
  int	posX = mIOPorts[0x43];
  BYTE	tmp;
  char	*curScanLine = mGraphics->GetScanLinePtr();
  int	addrTileData = IS_BIT_SET(mIOPorts[0x40], 4) ? 0x8000 : 0x9000;
  int	addrBGPattern = IS_BIT_SET(mIOPorts[0x40], 3) ? 0x9C00 : 0x9800;

  for (int i = 0; i < 160; i++)
    {
      tileId = ReadMem(addrBGPattern + (((posY % 256) / 8) * 32)
		       + ((posX % 256) / 8));

      tmp = ReadMem(addrTileData + tileId * 16 + ((posY % 8) * 2) + 0);
      bit0 = IS_BIT_SET(tmp, 7 - (posX % 8));

      tmp = ReadMem(addrTileData + tileId * 16 + ((posY % 8) * 2) + 1);
      bit1 = IS_BIT_SET(tmp, 7 - (posX % 8));

      SetColor((int *)(curScanLine + i * 4), bit0 | (bit1 << 1), false);
      posX++;
    }
  mGraphics->DrawScanLine(curLine);
}

void	Emulator::SetColor(int *scanLine, int spriteColor, bool blankTransp)
{
  int	finalColor;
  Palette *palette = (Palette *)&mIOPorts[0x47];

  switch (spriteColor)
    {
    case 0: finalColor = palette->colorNum0; break;
    case 1: finalColor = palette->colorNum1; break;
    case 2: finalColor = palette->colorNum2; break;
    case 3: finalColor = palette->colorNum3; break;
    }
  switch (finalColor)
    {
    case 0: if (!blankTransp) *scanLine = 0xFFFFFFFF; break;
    case 1: *scanLine = 0x90909090; break;
    case 2: *scanLine = 0x50505050; break;
    case 3: *scanLine = 0x00000000; break;
    }
}
