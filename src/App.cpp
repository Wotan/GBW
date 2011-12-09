#include <iostream>
#include <QSettings>
#include "App.hpp"

App::App(int ac, char **av) :
  QApplication (ac, av),
  mMainWindow(0),
  mSettings(0)
{

}

void	App::Init()
{
  mSettings = new QSettings("WotanApp", "GBW");

  mMainWindow = new MainWindow(this);
  mMainWindow->Init();
  mMainWindow->show();
}

App::~App()
{
  if (mMainWindow)
    delete mMainWindow;
  if (mSettings)
    delete mSettings;
}
