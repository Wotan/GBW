#include <iostream>
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
  mMemWatcher->setGeometry(5, 5, 300, 400);
  mMemWatcher->show();

  mNextOp = new QPushButton("Next Opcode", this);
  mNextOp->setGeometry(335, 250, 100, 25);

  connect(mNextOp, SIGNAL(clicked()), this, SLOT(NextOpcode()));
  return true;
}

void	Debugger::NextOpcode()
{
  std::cout << "Exec opcode ..." << std::endl;
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
}
