#include <iostream>
#include <QMessageBox>
#include <QPushButton>
#include "Debugger.hpp"
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
  delete mInfosWatcher;
  delete mMemWatcher;
  delete mNextOp;
  delete mNbOpcode;
  delete mNextNbOp;
}

bool Debugger::Init()
{
  setWindowFlags(Qt::Window);

  mInfosWatcher = new InfosWatcher(this);
  mInfosWatcher->setGeometry(310, 5, 300, 200);
  mInfosWatcher->show();


  mMemWatcher = new MemWatcher(this);
  mMemWatcher->setGeometry(5, 5, 300, 450);
  mMemWatcher->show();

  mNextOp = new QPushButton("Next Opcode", this);
  mNextOp->setGeometry(385, 250, 100, 25);

  mNbOpcode = new QSpinBox(this);
  mNbOpcode->setRange(1, 1000000000);
  mNbOpcode->setGeometry(315, 305, 100, 20);

  mNextNbOp = new QPushButton("Jump opcodes", this);
  mNextNbOp->setGeometry(435, 300, 120, 25);

  connect(mNextOp, SIGNAL(clicked()), this, SLOT(NextOpcode()));
  connect(mNextNbOp, SIGNAL(clicked()), this, SLOT(NextXOpcode()));

  mExitShortcut = new QShortcut(QKeySequence("Ctrl+D"), this);
  mNextOpShortcut = new QShortcut(QKeySequence("Ctrl+Space"), this);

  connect(mExitShortcut, SIGNAL(activated()), this, SLOT(close()));
  connect(mNextOpShortcut, SIGNAL(activated()), this, SLOT(NextOpcode()));


  return true;
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
  mMemWatcher->repaint();
  mInfosWatcher->repaint();
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
      i++;
    }
  mMemWatcher->repaint();
  mInfosWatcher->repaint();
}

void	Debugger::EmuInstanceChange(Emulator *emu)
{
  mEmu = emu;
  mMemWatcher->SetEmu(emu);
  mInfosWatcher->SetEmu(emu);
  std::cout << "Change emulator instance (" << emu << ")" << std::endl;
  if (emu)
    {
      mMemWatcher->repaint();
      mInfosWatcher->repaint();
    }
}
