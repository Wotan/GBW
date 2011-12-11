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
class VideoSettings;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(App *app);
  ~MainWindow();
  void	Init();
  void	SaveSettings();
  virtual void	resizeEvent(QResizeEvent * event);
  void keyPressEvent(QKeyEvent *keyEvent);
  void keyReleaseEvent(QKeyEvent *keyEvent);
  void togglePlay(bool play);
  Qt::Key *GetKeyTab() {return mKeyTab;}			    
  GraphicsEngine *GetGraphicsEngine() {return mGraphicsEngine;}

public slots:
  void	OpenRom();
  void	LoadState();
  void	SaveState();
  void	EmuChange(Emulator *);

private:
  Qt::Key	mKeyTab[8];
  GraphicsEngine *mGraphicsEngine;
  App		*mApp;
  InputWindow	*mInputWindow;
  VideoSettings	*mVideoSettings;
  Debugger	*mDebug;
  TileWatcher	*mTileWatcher;
  QAction	*mActionPlay;
  QAction	*mActionPause;
  QAction	*mActionReset;
  QAction	*mActionLoadState;
  QAction	*mActionSaveState;
};

#endif // MAINWINDOW_HPP_
