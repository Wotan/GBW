#include <QSettings>
#include <iostream>
#include <QPalette>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>

#include "GraphicsEngine.hpp"
#include "MainWindow.hpp"
#include "TileWatcher.hpp"
#include "Settings.hpp"


MainWindow::MainWindow(App *app):
  mApp(app)
{
}

MainWindow::~MainWindow()
{
  SaveSettings();
  delete mGraphicsEngine;
  delete mDebug;
}

void	MainWindow::SaveSettings()
{
  mApp->GetSettings()->setValue("mainwindow/size", size());
  mApp->GetSettings()->setValue("video/bilinear", 
				mGraphicsEngine->IsBilinearActive());

  mApp->GetSettings()->setValue("input/Up", mKeyTab[0]);
  mApp->GetSettings()->setValue("input/Down", mKeyTab[1]);
  mApp->GetSettings()->setValue("input/Right", mKeyTab[2]);
  mApp->GetSettings()->setValue("input/Left", mKeyTab[3]);
  mApp->GetSettings()->setValue("input/A", mKeyTab[4]);
  mApp->GetSettings()->setValue("input/B", mKeyTab[5]);
  mApp->GetSettings()->setValue("input/Start", mKeyTab[6]);
  mApp->GetSettings()->setValue("input/Select", mKeyTab[7]);
}

void	MainWindow::Init()
{
  /////////////////////////////////////////////
  ////     Set Main Window settings        ////
  /////////////////////////////////////////////
  QPalette newPalette;
  newPalette.setColor(QPalette::Window, QColor(0, 0, 0));
  setPalette(newPalette);

  /////////////////////////////////////////////
  ////        Init defaults keys           ////
  /////////////////////////////////////////////
  mKeyTab[0] = (Qt::Key)mApp->GetSettings()->value("input/Up",
						   Qt::Key_Up).toInt();
  mKeyTab[1] = (Qt::Key)mApp->GetSettings()->value("input/Down",
						   Qt::Key_Down).toInt();
  mKeyTab[2] = (Qt::Key)mApp->GetSettings()->value("input/Right",
						   Qt::Key_Right).toInt();
  mKeyTab[3] = (Qt::Key)mApp->GetSettings()->value("input/Left",
						   Qt::Key_Left).toInt();
  mKeyTab[4] = (Qt::Key)mApp->GetSettings()->value("input/A",
						   Qt::Key_Q).toInt();
  mKeyTab[5] = (Qt::Key)mApp->GetSettings()->value("input/B",
						   Qt::Key_W).toInt();
  mKeyTab[6] = (Qt::Key)mApp->GetSettings()->value("input/Start",
						   Qt::Key_Return).toInt();
  mKeyTab[7] = (Qt::Key)mApp->GetSettings()->value("input/Select",
						   Qt::Key_Shift).toInt();

  /////////////////////////////////////////////
  ////          Create Menus               ////
  /////////////////////////////////////////////
  
  // Menu File
  QMenu *menuFile = menuBar()->addMenu(tr("&File"));
  QAction *actionOpen = menuFile->addAction(tr("&Open..."));
  menuFile->addSeparator();
  mActionLoadState = menuFile->addAction(tr("&Load state..."));
  mActionSaveState = menuFile->addAction(tr("&Save state..."));

  QAction *actionLoadQuickState = menuFile->addAction(tr("&Load quick state"));
  QAction *actionSaveQuickState = menuFile->addAction(tr("&Save quick state"));
  QAction *actionExit = menuFile->addAction(tr("&Exit"));
  menuFile->addSeparator();

  // Menu Run
  QMenu *menuRun = menuBar()->addMenu(tr("&Run"));
  mActionPlay = menuRun->addAction(tr("&Play"));
  mActionPause = menuRun->addAction(tr("&Pause"));
  mActionReset = menuRun->addAction(tr("&Reset"));

  // Menu Settings
  QMenu *menuSettings = menuBar()->addMenu(tr("&Settings"));
  QAction *actionInput = menuSettings->addAction(tr("&Input"));
  QAction *actionVideo = menuSettings->addAction(tr("&Video"));

  // Menu Tools
  QMenu *menuTools = menuBar()->addMenu(tr("&Tools"));
  QAction *actionTileWatcher = menuTools->addAction(tr("&Tile Watcher"));

  // Menu Debugger
  QMenu *menuDebugger = menuBar()->addMenu(tr("&Debugger"));
  QAction *actionShowDebug = menuDebugger->addAction(tr("&Show debug panel"));

  // Set icons
  QStyle *style = QApplication::style();
  actionOpen->setIcon(style->standardIcon(QStyle::SP_DialogOpenButton));
  actionExit->setIcon(style->standardIcon(QStyle::SP_DialogCloseButton));

  mActionPlay->setIcon(style->standardIcon(QStyle::SP_MediaPlay));
  mActionPause->setIcon(style->standardIcon(QStyle::SP_MediaPause));
  mActionReset->setIcon(style->standardIcon(QStyle::SP_BrowserReload));
  /////////////////////////////////////////////
  ////         Create Shorcuts             ////
  /////////////////////////////////////////////
  actionExit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
  actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  actionShowDebug->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
  mActionPlay->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  mActionPause->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
  mActionReset->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
  actionTileWatcher->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
  actionInput->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
  mActionLoadState->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
  mActionSaveState->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
  actionLoadQuickState->setShortcut(QKeySequence(Qt::Key_F9));
  actionSaveQuickState->setShortcut(QKeySequence(Qt::Key_F8));

  /////////////////////////////////////////////
  ////     Graphics Engine Init (first)    ////
  /////////////////////////////////////////////
  int menuBarHeight = menuBar()->sizeHint().height();
  mGraphicsEngine = new GraphicsEngine(this, QPoint(0, menuBarHeight),
				       QSize(160, 144), mApp);
  mGraphicsEngine->SetBilinear(mApp->GetSettings()->
			       value("video/bilinear", true).toBool());
  mGraphicsEngine->SetMainWindow(this);
  mGraphicsEngine->show();
  togglePlay(false);
  mActionPlay->setEnabled(false);
  mActionReset->setEnabled(false);
  mActionSaveState->setEnabled(false);
  mActionLoadState->setEnabled(false);

  /// Windows settings after Graphic engine init
  setMinimumSize(GB_SCREEN_X, GB_SCREEN_Y + menuBarHeight);
  resize(mApp->GetSettings()->value("mainwindow/size",
 QSize(GB_SCREEN_X, GB_SCREEN_Y + menuBarHeight)).toSize());

  /////////////////////////////////////////////
  ////        Create all panels            ////
  /////////////////////////////////////////////
  mInputWindow = new InputWindow(mApp, this);
  mInputWindow->InitWidget();

  mVideoSettings = new VideoSettings(mApp, this);
  mVideoSettings->Init();

  mDebug = new Debugger(this, mApp);
  mDebug->Init();

  mTileWatcher = new TileWatcher(this);
  mTileWatcher->resize(120, 120);
  
  /////////////////////////////////////////////  
  ////           Init signals(last)        ////
  /////////////////////////////////////////////
  connect(actionExit, SIGNAL(triggered()), mApp, SLOT(quit()));
  connect(actionOpen, SIGNAL(triggered()), this, SLOT(OpenRom()));

  connect(mActionLoadState, SIGNAL(triggered()), this, SLOT(LoadState()));
  connect(mActionSaveState, SIGNAL(triggered()), this, SLOT(SaveState()));

  connect(actionLoadQuickState, SIGNAL(triggered()),
	  this, SLOT(LoadQuickState()));
  connect(actionSaveQuickState, SIGNAL(triggered()),
	  this, SLOT(SaveQuickState()));

  connect(actionShowDebug, SIGNAL(triggered()), mDebug, SLOT(show()));
  connect(actionInput, SIGNAL(triggered()), mInputWindow, SLOT(show()));
  connect(actionVideo, SIGNAL(triggered()), mVideoSettings, SLOT(show()));
  connect(actionTileWatcher, SIGNAL(triggered()), mTileWatcher, SLOT(show()));

  connect(mGraphicsEngine, SIGNAL(ChangeEmuInstance(Emulator *)),
	  mDebug, SLOT(EmuInstanceChange(Emulator *)));
  connect(mGraphicsEngine, SIGNAL(ChangeEmuInstance(Emulator *)),
   	  mTileWatcher, SLOT(SetEmu(Emulator *)));
  connect(mGraphicsEngine, SIGNAL(ChangeEmuInstance(Emulator *)),
   	  this, SLOT(EmuChange(Emulator *)));
  connect(mActionPlay, SIGNAL(triggered()), mGraphicsEngine, SLOT(PlayEmu()));
  connect(mActionPause, SIGNAL(triggered()), mGraphicsEngine, SLOT(PauseEmu()));
  connect(mActionReset, SIGNAL(triggered()), mGraphicsEngine, SLOT(ResetEmu()));

  /////////////////////////////////////////////  
  ////           Check arguments           ////
  /////////////////////////////////////////////
  if (mApp->arguments().size() > 1)
    {
      QString romFileName = mApp->arguments().at(1);
      if (mGraphicsEngine->NewEmulator(romFileName.toStdString().c_str()))
	mGraphicsEngine->PauseEmu();
      if (mApp->arguments().size() > 2)
	{
	  QString romSaveState = mApp->arguments().at(2);
	  Emulator *emu = mGraphicsEngine->GetEmulator();
	  if (!emu->LoadState(romSaveState.toStdString().c_str()))
	    std::cerr << "Could not load save state" << std::endl;
	}
    }
}

void	MainWindow::EmuChange(Emulator *emu)
{
  if (emu)
    setWindowTitle(QString("GBW - ") + QString(emu->GetRomName()));
  else
    setWindowTitle("GBW");
}

void	MainWindow::OpenRom()
{
  QString romFileName;

  romFileName = QFileDialog::getOpenFileName(0, "Select a Game Boy ROM");
  if (romFileName != 0)
    if (mGraphicsEngine->NewEmulator(romFileName.toStdString().c_str()))
      mGraphicsEngine->PauseEmu();
}

void	MainWindow::resizeEvent(QResizeEvent *event)
{
  int menuBarHeight = menuBar()->sizeHint().height();
  QSize size = event->size();
  int curWidth, curHeight;
  int nextWidth, nextHeight;
  int posX, posY;

  curWidth = size.width();
  curHeight = size.height() - menuBarHeight;

  if (curWidth * GB_SCREEN_Y <= curHeight * GB_SCREEN_X)
    {
      nextWidth = curWidth;
      nextHeight = (curWidth * GB_SCREEN_Y) / GB_SCREEN_X;
    }
  else
    {
      nextHeight = curHeight;
      nextWidth = (curHeight * GB_SCREEN_X) / GB_SCREEN_Y;
    }
  mGraphicsEngine->resize(nextWidth, nextHeight);
  posX = (size.width() - nextWidth) / 2;
  posY = (size.height() + menuBarHeight - nextHeight) / 2;
  mGraphicsEngine->move(posX > 0 ? posX : 0,
			posY > menuBarHeight ? posY : menuBarHeight);
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
  Emulator *emu = mGraphicsEngine->GetEmulator();
  int	   curKey = keyEvent->key();

  if (!emu)
    return ;

  if (mKeyTab[0] == curKey)
    emu->KeyChange(Up, true);
  else if (mKeyTab[1] == curKey)
    emu->KeyChange(Down, true);
  else if (mKeyTab[2] == curKey)
    emu->KeyChange(Right, true);
  else if (mKeyTab[3] == curKey)
    emu->KeyChange(Left, true);
  else if (mKeyTab[4] == curKey)
    emu->KeyChange(BUTTON_A, true);
  else if (mKeyTab[5] == curKey)
    emu->KeyChange(BUTTON_B, true);
  else if (mKeyTab[6] == curKey)
    emu->KeyChange(Start, true);
  else if (mKeyTab[7] == curKey)
    emu->KeyChange(Select, true);
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyEvent)
{
  Emulator *emu = mGraphicsEngine->GetEmulator();
  int curKey = keyEvent->key();

  if (!emu)
    return ;

  if (mKeyTab[0] == curKey)
    emu->KeyChange(Up, false);
  else if (mKeyTab[1] == curKey)
    emu->KeyChange(Down, false);
  else if (mKeyTab[2] == curKey)
    emu->KeyChange(Right, false);
  else if (mKeyTab[3] == curKey)
    emu->KeyChange(Left, false);
  else if (mKeyTab[4] == curKey)
    emu->KeyChange(BUTTON_A, false);
  else if (mKeyTab[5] == curKey)
    emu->KeyChange(BUTTON_B, false);
  else if (mKeyTab[6] == curKey)
    emu->KeyChange(Start, false);
  else if (mKeyTab[7] == curKey)
    emu->KeyChange(Select, false);
}


void MainWindow::togglePlay(bool play)
{
  if (play)
    {
      mActionPlay->setEnabled(false);
      mActionPause->setEnabled(true);
      mActionReset->setEnabled(true);
      mActionSaveState->setEnabled(true);
      mActionLoadState->setEnabled(true);
    }
  else
    {
      mActionPlay->setEnabled(true);
      mActionPause->setEnabled(false);
      mActionReset->setEnabled(true);
    }
}

void	MainWindow::LoadState()
{
  QString fileName;
  Emulator *emu;

  emu = mGraphicsEngine->GetEmulator();
  fileName = QFileDialog::getOpenFileName(0, "Select a file to load state");
  if (fileName != 0 && emu)
    {
      if (!emu->LoadState(fileName.toStdString().c_str()))
	QMessageBox::critical(this, "Error", 
			      "Save state is from a different game");
    }
}

void	MainWindow::SaveState()
{
  QString fileName;
  Emulator *emu;

  emu = mGraphicsEngine->GetEmulator();
  fileName = QFileDialog::getSaveFileName(0, "Select a file to save state");
  if (fileName != 0 && emu)
    emu->SaveState(fileName.toStdString().c_str());
}

void	MainWindow::LoadQuickState()
{
  QString file = QDir::tempPath() + "/GBW_quick_state.save";
  Emulator *emu = mGraphicsEngine->GetEmulator();

  if (emu)
    emu->LoadState(file.toStdString().c_str());
}

void	MainWindow::SaveQuickState()
{
  QString file = QDir::tempPath() + "/GBW_quick_state.save";
  Emulator *emu = mGraphicsEngine->GetEmulator();

  if (emu)
    emu->SaveState(file.toStdString().c_str());
}

