#ifndef MAINWINDOW_HPP_
# define MAINWINDOW_HPP_

#include <QMenuBar>
#include <QMainWindow>
#include <QResizeEvent>
#include "App.hpp"
#include "GraphicsEngine.hpp"
#include "Debugger.hpp"

class App;
class GraphicsEngine;
class Debugger;
class TileWatcher;
class InputWindow;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(App *app);
  ~MainWindow();
  void	Init();
  virtual void	resizeEvent(QResizeEvent * event);
  void keyPressEvent(QKeyEvent *keyEvent);
  void keyReleaseEvent(QKeyEvent *keyEvent);
  void togglePlay(bool play);
  Qt::Key *GetKeyTab() {return mKeyTab;}			    

public slots:
  void	OpenRom();
  void	LoadState();
  void	SaveState();

private:
  Qt::Key	mKeyTab[8];
  GraphicsEngine *mGraphicsEngine;
  App		*mApp;
  InputWindow	*mInputWindow;
  Debugger	*mDebug;
  TileWatcher	*mTileWatcher;
  QAction	*mActionPlay;
  QAction	*mActionPause;
  QAction	*mActionReset;
  QAction	*mActionLoadState;
  QAction	*mActionSaveState;
};

#endif // MAINWINDOW_HPP_
