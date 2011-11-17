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
}

bool Debugger::Init()
{
  setWindowFlags(Qt::Window);

  mRegWatcher = new RegWatcher(this);
  mRegWatcher->setGeometry(5, 5, 200, 200);



  mRegWatcher->show();


  // mMemWatcher = new MemWatcher(this);
  // mMemWatcher->setGeometry(210, 5, 200, 200);
  // mMemWatcher->show();
  return true;
}

void	Debugger::EmuInstanceChange(Emulator *emu)
{
  mEmu = emu;
  std::cout << "Change emulator instance (" << emu << ")" << std::endl;
}
