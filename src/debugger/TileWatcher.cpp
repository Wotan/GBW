#include <cstdio>
#include <QPainter>
#include "MemWatcher.hpp"
#include "TileWatcher.hpp"

TileWatcher::TileWatcher(QWidget *parent) :
  QWidget(parent, Qt::Dialog),
  mEmu(0)
{
  mBoxAddr = new HexSpinBox(this);
  mBoxAddr->setGeometry(5, 5, 80, 20);
  mBoxAddr->setSingleStep(16);
  mBoxAddr->setRange(0x8000, 0xA000 - 0xF);
  connect(mBoxAddr, SIGNAL(valueChanged(int)), this, SLOT(repaint()));
}

void	TileWatcher::paintEvent(QPaintEvent *event)
{
  QWidget::paintEvent(event);

  QPainter painter(this);
  painter.setFont(QFont("Monospace"));
  if (mEmu == 0)
    return ;
  int posX = 30;
  int posY = 30;
  int curMem = mBoxAddr->value() - 0x8000;
  int tmp;

  for (int j = 0; j < 8; j++)
    {
      posX = 30;
      for (int i = 0; i < 8; i++)
	{
	  tmp = IS_BIT_SET(mEmu->mVRAM[curMem], 7 - i) | IS_BIT_SET(mEmu->mVRAM[curMem + 1], 7 - i) << 1;

	  painter.fillRect(QRect(posX, posY, 10, 10),
			   QColor(SetColor(tmp, mEmu->mIOPorts[0x47])));
	  posX += 10;
	}
      curMem += 2;
      posY += 10;
    }
}

const char	*TileWatcher::SetColor(int spriteColor, BYTE bpalette)
{
  int	finalColor;
  Palette *palette = (Palette *)&bpalette;

  switch (spriteColor)
    {
    case 0: finalColor = palette->colorNum0; break;
    case 1: finalColor = palette->colorNum1; break;
    case 2: finalColor = palette->colorNum2; break;
    case 3: finalColor = palette->colorNum3; break;
    }
  switch (finalColor)
    {
    case 0:  return ("#FFFFFF");
    case 1:  return ("#AAAAAA");
    case 2:  return ("#555555");
    case 3:  return ("#000000");
    }
  return "#000000";
}
