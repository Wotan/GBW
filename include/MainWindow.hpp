#ifndef MAINWINDOW_HPP_
# define MAINWINDOW_HPP_

#include <QMenuBar>
#include <QMainWindow>
#include "App.hpp"
#include "GraphicsEngine.hpp"

class App;
class GraphicsEngine;

class MainWindow : public QMainWindow
{
public:
  MainWindow(App *app);
  ~MainWindow();
  void	Init();

private:

  GraphicsEngine *mGraphicsEngine;
  App		*mApp;
};

#endif // MAINWINDOW_HPP_
