#include "AsmWatcher.hpp"

AsmWatcher::AsmWatcher(QWidget *parent) :
  QFrame(parent),
  mEmu(NULL)
{
  setFrameStyle(QFrame::Panel | QFrame::Sunken);
  setLineWidth(1);

  mBoxAddr = new HexSpinBox(this);
  mBoxAddr->setGeometry(5, 5, 80, 20);
  mBoxAddr->setSingleStep(0x1);
  mBoxAddr->setValue(0x100);

  mBoxFollow = new QCheckBox("Follow program counter", this);
  mBoxFollow->move(90, 5);

  connect(mBoxAddr, SIGNAL(valueChanged(int)), this, SLOT(repaint()));
  connect(mBoxFollow, SIGNAL(toggled(bool)),  mBoxAddr, SLOT(setDisabled(bool)));
  connect(mBoxFollow, SIGNAL(toggled(bool)),  this, SLOT(repaint()));
  mBoxFollow->setCheckState(Qt::Checked);
}

AsmWatcher::~AsmWatcher()
{
  delete mBoxAddr;
  delete mBoxFollow;
}

void AsmWatcher::paintEvent(QPaintEvent *event)
{
  QFrame::paintEvent(event);
  QPainter painter(this);
  painter.setFont(QFont("Monospace"));
  if (mEmu == 0)
    return ;
  QString line;
  int curMem;
  if (mBoxAddr->isEnabled())
    curMem = mBoxAddr->value();
  else
    curMem = mEmu->mPC;
  int	posLine = 40;

  for (int i = 0; i < 16; i++)
    {
      if (curMem == mEmu->mPC)
	painter.setPen(QColor(255, 0, 0));
      else
	painter.setPen(QColor(0, 0, 0));
      line.sprintf("%04X: %s", curMem, Debugger::GetOpMnemonic(mEmu, curMem));
      painter.drawText(5, posLine, line);
      posLine += 20;
      curMem += Debugger::GetOpSize(mEmu, curMem);
    }
  painter.drawText(5, posLine + 10, "Description");
  painter.drawText(QRect(5, posLine + 15, 250, 290),
		   Qt::AlignLeft | Qt::TextWordWrap,
		   Debugger::GetOpDesc(mEmu, mEmu->mPC));
}
