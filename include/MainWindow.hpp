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
  Q_OBJECT

public:
  MainWindow(App *app);
  ~MainWindow();
  void	Init();

public slots:
  void	OpenRom();

private:

  GraphicsEngine *mGraphicsEngine;
  App		*mApp;
};

#endif // MAINWINDOW_HPP_
