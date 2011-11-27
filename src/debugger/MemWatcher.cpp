#include <QPushButton>
#include <QFrame>
#include <QPainter>
#include "MemWatcher.hpp"


MemWatcher::MemWatcher(QWidget *parent) :
  QFrame(parent),
  mEmu(0)
{
  setFrameStyle(QFrame::Panel | QFrame::Sunken);
  setLineWidth(1);

  // QPalette palette;
  // palette.setColor(backgroundRole(), QColor(255, 255, 255));
  // setPalette(palette);
  // setAutoFillBackground(true);

  mBoxAddr = new HexSpinBox(this);
  mBoxAddr->setGeometry(215, 5, 80, 20);
  mBoxAddr->setSingleStep(0x8);
  connect(mBoxAddr, SIGNAL(valueChanged(int)), this, SLOT(repaint()));

  mScrollBar = new QScrollBar(Qt::Vertical, this);
  mScrollBar->setGeometry(280, 30, 15, 290);
  mScrollBar->setRange(0, 0xFFFF - 8 * 16);
  mScrollBar->setSingleStep(0x8);
  mScrollBar->setPageStep(0x8);


  mAddrAlias = new QComboBox(this);
  mAddrAlias->setGeometry(40, 5, 170, 20);
  mAddrAlias->addItem("None");
  mAddrAlias->addItem("ROM Bank 00");
  mAddrAlias->addItem("ROM Bank 01..NN");
  mAddrAlias->addItem("Video RAM (VRAM)");
  mAddrAlias->addItem("External RAM");
  mAddrAlias->addItem("Work RAM Bank 0");
  mAddrAlias->addItem("Work RAM Bank 1");
  mAddrAlias->addItem("ECHO C000-DDFF");
  mAddrAlias->addItem("Sprite Attribute Table");
  mAddrAlias->addItem("I/O Ports");
  mAddrAlias->addItem("High RAM");

  connect(mBoxAddr, SIGNAL(valueChanged(int)), mScrollBar, SLOT(setValue(int)));
  connect(mScrollBar, SIGNAL(valueChanged(int)), mBoxAddr, SLOT(setValue(int)));
  connect(mAddrAlias, SIGNAL(currentIndexChanged(int)), this, SLOT(AliasChange(int)));
}

MemWatcher::~MemWatcher()
{
  delete mBoxAddr;
  delete mScrollBar;
  delete mAddrAlias;
}

void	MemWatcher::AliasChange(int id)
{
  switch (id)
    {
    case 0:
      break;
    case 1: mScrollBar->setValue(0x0000); break;
    case 2: mScrollBar->setValue(0x4000); break;
    case 3: mScrollBar->setValue(0x8000); break;
    case 4: mScrollBar->setValue(0xA000); break;
    case 5: mScrollBar->setValue(0xC000); break;
    case 6: mScrollBar->setValue(0xD000); break;
    case 7: mScrollBar->setValue(0xE000); break;
    case 8: mScrollBar->setValue(0xFE00); break;
    case 9: mScrollBar->setValue(0xFF00); break;
    case 10: mScrollBar->setValue(0xFF80); break;
    }
}

void	MemWatcher::paintEvent(QPaintEvent *event)
{
  QFrame::paintEvent(event);

  QPainter painter(this);
  painter.setFont(QFont("Monospace"));
  if (mEmu == 0)
    return ;
  QString line;

  int	curMem = mBoxAddr->value();
  int	posLine = 40;
  for (int i = 0; i < 0xF; i++)
    {
      line.sprintf("%04X: ", curMem);
      for (int j = 0; j < 8; j++)
	line.append(QString().sprintf("%02X ", mEmu->ReadMem(curMem + j)));
      painter.drawText(5, posLine, line);
      posLine += 20;
      curMem += 8;
    }

  curMem = mEmu->mPC - mEmu->mPC % 8;

  ///////////////////////////////////////////
  line.sprintf("PC %04X: ", curMem);
  for (int j = 0; j < 8; j++)
    line.append(QString().sprintf("%02X ", mEmu->ReadMem(curMem + j)));
  painter.fillRect(85 + 27 * (mEmu->mPC % 8),
		   posLine - 3, 20, 16, QColor(255, 204, 51));
  painter.drawText(5, posLine + 10, line);

  posLine += 20;
  curMem += 8;

  //////////////////////////////////////////
  line.sprintf("PC %04X: ", curMem);
  for (int j = 0; j < 8; j++)
    line.append(QString().sprintf("%02X ", mEmu->ReadMem(curMem + j)));
  painter.drawText(5, posLine + 10, line);
  posLine += 20;

  //////////////////////////////////////////
  painter.drawText(5, posLine + 10, Debugger::GetOpMnemonic(mEmu, mEmu->mPC));
  painter.drawText(QRect(5, posLine + 15, 300, 290),
		   Qt::AlignLeft | Qt::TextWordWrap,
		   Debugger::GetOpDesc(mEmu, mEmu->mPC));
}

HexSpinBox::HexSpinBox(QWidget *parent) :
  QSpinBox(parent)
{
  setRange(0, 0xFFFF - 8 * 16);
  mValidator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
}

HexSpinBox::~HexSpinBox()
{
  delete mValidator;
}

QValidator::State HexSpinBox::validate(QString &text, int &pos) const
{
  return mValidator->validate(text, pos);
}

int	HexSpinBox::valueFromText(const QString &text) const
{
  bool	tmp;
  return text.toInt(&tmp, 16);
}

QString	HexSpinBox::textFromValue(int value) const
{
  return QString::number(value, 16).toUpper();
}
