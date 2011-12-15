#include <iostream>
#include <QTimer>
#include <QMessageBox>
#include <QPushButton>
#include "Debugger.hpp"
#include "AsmWatcher.hpp"
#include "TileWatcher.hpp"
#include "Emulator.hpp"

Debugger::Debugger(QWidget *parent, App *app) :
  QDialog(parent),
  mApp(app),
  mEmu(0)
{
  std::cout << "Debugger created" << std::endl;
}

Debugger::~Debugger()
{
  std::cout << "Debugger deleted" << std::endl;
}

bool Debugger::Init()
{
  setWindowFlags(Qt::Window);
  setWindowTitle(QString("GBW Debugger"));

  mUpdateTimer = new QTimer(this);
  mUpdateTimer->setInterval(500);
  mUpdateTimer->start();

  mMainLayout = new QGridLayout(this);

  mInfosWatcher = new InfosWatcher(this);
  mInfosWatcher->setMinimumSize(300, 200);

  mMemWatcher = new MemWatcher(this);
  mMemWatcher->setMinimumSize(300, 330);

  mAsmWatcher = new AsmWatcher(this);
  mAsmWatcher->setMinimumSize(300, 450);

  mNextOp = new QPushButton("Next Opcode (Ctrl + Space)", this);

  mNbOpcode = new QSpinBox(this);
  mNbOpcode->setRange(1, 1000000000);

  mNextNbOp = new QPushButton("Jump opcodes", this);

  mShowLastOps = new QPushButton("Show lasts ops", this);

  mMainLayout->addWidget(mInfosWatcher, 0, 0, 1, 2);
  mMainLayout->addWidget(mMemWatcher, 1, 0, 3, 2);
  mMainLayout->addWidget(mAsmWatcher, 0, 2, 2, 2);
  mMainLayout->addWidget(mNbOpcode, 2, 2);
  mMainLayout->addWidget(mNextNbOp, 2, 3);
  mMainLayout->addWidget(mNextOp, 3, 2, 1, 2);
  mMainLayout->addWidget(mShowLastOps, 4, 0, 1, 1);
  setLayout(mMainLayout);


  connect(mNextOp, SIGNAL(clicked()), this, SLOT(NextOpcode()));
  connect(mNextNbOp, SIGNAL(clicked()), this, SLOT(NextXOpcode()));
  connect(mShowLastOps, SIGNAL(clicked()), this, SLOT(ShowLastsOps()));

  mExitShortcut = new QShortcut(QKeySequence("Ctrl+D"), this);
  mNextOpShortcut = new QShortcut(QKeySequence("Ctrl+Space"), this);

  connect(mExitShortcut, SIGNAL(activated()), this, SLOT(close()));
  connect(mNextOpShortcut, SIGNAL(activated()), this, SLOT(NextOpcode()));
  connect(mUpdateTimer, SIGNAL(timeout()), this, SLOT(repaint()));


  return true;
}

void		Debugger::ShowLastsOps()
{
  if (!mEmu)
    return ;
  std::list<char *>::reverse_iterator it;
  for (it = mEmu->mListLastOps.rbegin() ; it != mEmu->mListLastOps.rend(); it++)
    std::cout << *it << std::endl;
}

void	Debugger::NextOpcode()
{
  if (!mEmu)
    {
      QMessageBox::critical(this, "Error",
			    "No rom loaded");
      return ;
    }
  int nbCycles = mEmu->DoOpcode();
  mEmu->UpdateTimer(nbCycles);
  mEmu->UpdateLCD(nbCycles);
  mEmu->HandleInterupt();
  mEmu->mOpCounter++;
  mEmu->mCyclesCounter += nbCycles;
  RepaintAll();
}

void	Debugger::NextXOpcode()
{
  if (!mEmu)
    {
      QMessageBox::critical(this, "Error",
			    "No rom loaded");
      return ;
    }
  int nbCyclesToDo = mNbOpcode->value();
  int i = 0;
  while (i < nbCyclesToDo)
    {
      int nbCurCycles = mEmu->DoOpcode();
      mEmu->UpdateTimer(nbCurCycles);
      mEmu->UpdateLCD(nbCurCycles);
      mEmu->HandleInterupt();
      mEmu->mOpCounter++;
      mEmu->mCyclesCounter += nbCurCycles;
      i++;
    }
  RepaintAll();
}

void	Debugger::EmuInstanceChange(Emulator *emu)
{
  mEmu = emu;
  mMemWatcher->SetEmu(emu);
  mInfosWatcher->SetEmu(emu);
  mAsmWatcher->SetEmu(emu);
  std::cout << "Change emulator instance (" << emu << ")" << std::endl;
  if (emu)
    RepaintAll();
}

void Debugger::RepaintAll()
{
  mMemWatcher->repaint();
  mInfosWatcher->repaint();
  mAsmWatcher->repaint();
}
