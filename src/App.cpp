#include <iostream>
#include "App.hpp"

App::App(int ac, char **av) :
  QApplication (ac, av),
  mMainWindow(NULL)
{

}

void	App::Init()
{
  mMainWindow = new MainWindow(this);
  mMainWindow->Init();
  mMainWindow->show();
}

App::~App()
{
  if (mMainWindow)
    delete mMainWindow;
}
