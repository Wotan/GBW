#include <stdio.h>
#include <QString>
#include <iostream>
#include <QPainter>
#include <QFrame>
#include "InfosWatcher.hpp"
#include "Emulator.hpp"


InfosWatcher::InfosWatcher(QWidget *parent) :
  QFrame(parent),
  mEmu(0)
{
  setFrameStyle(QFrame::Panel | QFrame::Sunken);
  setLineWidth(1);
}

void	InfosWatcher::paintEvent(QPaintEvent *event)
{
  QFrame::paintEvent(event);

  QPainter painter(this);
  painter.setFont(QFont("Monospace"));
  if (mEmu == 0)
    return ;
  DrawRegister(painter);
  DrawLCDInfos(painter);
}

void	InfosWatcher::DrawLCDInfos(QPainter &painter)
{
  QString line;
  int posX = 150;
  int posLine = 45;

  painter.drawText(posX + 20, 20, "LCD Infos");

  line.sprintf("LCD Display : %s",
	       IS_BIT_SET(mEmu->ReadMem(0xFF40), 7) ?  "On" : "Off");
  painter.drawText(posX, posLine, line);
  posLine += 20;


  line.sprintf("LY : %i", mEmu->ReadMem(0xFF44));
  painter.drawText(posX, posLine, line);

  posLine += 100;
  line.sprintf("Opcodes : %i", mEmu->mOpCounter);
  painter.drawText(posX - 20, posLine, line);
  posLine += 20;

  line.sprintf("Cycles : %i", mEmu->mCyclesCounter);
  painter.drawText(posX - 20, posLine, line);
  posLine += 20;
}

void	InfosWatcher::DrawRegister(QPainter &painter)
{
  QString line;
  painter.drawText(40, 20, "Registers");

  int posLine = 45;
  line.sprintf("AF 0x%04X", mEmu->mAF.a);
  painter.drawText(5, posLine, line);
  posLine += 20;
  line.sprintf("BC 0x%04X", mEmu->mBC.a);
  painter.drawText(5, posLine, line);
  posLine += 20;
  line.sprintf("DE 0x%04X", mEmu->mDE.a);
  painter.drawText(5, posLine, line);
  posLine += 20;
  line.sprintf("HL 0x%04X", mEmu->mHL.a);
  painter.drawText(5, posLine, line);
  posLine += 20;
  line.sprintf("PC 0x%04X", mEmu->mPC);
  painter.drawText(5, posLine, line);
  posLine += 20;
  line.sprintf("SP 0x%04X", mEmu->mSP);
  painter.drawText(5, posLine, line);
  posLine += 20;
  line.sprintf("CurROMBank %i", mEmu->mCurROMBank);
  painter.drawText(5, posLine, line);
  posLine += 20;
  line.sprintf("CurRAMBank %i", mEmu->mCurRAMBank);
  painter.drawText(5, posLine, line);

  posLine = 45;
  line.sprintf("Z %i", IS_BIT_SET(mEmu->REG_F, F_Z) ? 1 : 0);
  painter.drawText(110, posLine, line);
  posLine += 20;

  line.sprintf("N %i", IS_BIT_SET(mEmu->REG_F, F_N) ? 1 : 0);
  painter.drawText(110, posLine, line);
  posLine += 20;

  line.sprintf("H %i", IS_BIT_SET(mEmu->REG_F, F_H) ? 1 : 0);
  painter.drawText(110, posLine, line);
  posLine += 20;

  line.sprintf("C %i", IS_BIT_SET(mEmu->REG_F, F_C) ? 1 : 0);
  painter.drawText(110, posLine, line);
  posLine += 20;
}
