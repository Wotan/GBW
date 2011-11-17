#include <iostream>
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
  return true;
}

void	Debugger::EmuInstanceChange(Emulator *emu)
{
  mEmu = emu;
  std::cout << "Change emulator instance (" << emu << ")" << std::endl;
}
