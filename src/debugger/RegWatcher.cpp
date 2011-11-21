#include <stdio.h>
#include <QString>
#include <iostream>
#include <QPainter>
#include <QFrame>
#include "RegWatcher.hpp"
#include "Emulator.hpp"


RegWatcher::RegWatcher(QWidget *parent) :
  QFrame(parent),
  mEmu(0)
{
  setFrameStyle(QFrame::Panel | QFrame::Sunken);
  setLineWidth(1);
}

void	RegWatcher::paintEvent(QPaintEvent *event)
{
  QFrame::paintEvent(event);

  QPainter painter(this);
  painter.setFont(QFont("Monospace"));
  if (mEmu == 0)
    return ;
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
}
