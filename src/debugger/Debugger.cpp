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
  delete mRegWatcher;
  delete mMemWatcher;
  delete mNextOp;
}

bool Debugger::Init()
{
  setWindowFlags(Qt::Window);

  mRegWatcher = new RegWatcher(this);
  mRegWatcher->setGeometry(310, 5, 150, 200);
  mRegWatcher->show();


  mMemWatcher = new MemWatcher(this);
  mMemWatcher->setGeometry(5, 5, 300, 450);
  mMemWatcher->show();

  mNextOp = new QPushButton("Next Opcode", this);
  mNextOp->setGeometry(335, 250, 100, 25);

  connect(mNextOp, SIGNAL(clicked()), this, SLOT(NextOpcode()));

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
  mEmu->DoOpcode();
  mMemWatcher->repaint();
  mRegWatcher->repaint();
}

void	Debugger::EmuInstanceChange(Emulator *emu)
{
  mEmu = emu;
  mMemWatcher->SetEmu(emu);
  mRegWatcher->SetEmu(emu);
  std::cout << "Change emulator instance (" << emu << ")" << std::endl;
  if (emu)
    {
      mMemWatcher->repaint();
      mRegWatcher->repaint();
    }
}
