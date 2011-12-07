#include <iostream>
#include <QPalette>
#include <QFileDialog>
#include <QMessageBox>
#include "GraphicsEngine.hpp"
#include "MainWindow.hpp"
#include "TileWatcher.hpp"

MainWindow::MainWindow(App *app):
  mApp(app)
{
  std::cout << "MainWindow created" << std::endl;
}

MainWindow::~MainWindow()
{
  delete mGraphicsEngine;
  delete mDebug;
  std::cout << "MainWindow deleted" << std::endl;
}

void	MainWindow::Init()
{
  /////////////////////////////////////////////
  QMenu *menuFile = menuBar()->addMenu(tr("&File"));
  QMenu *menuRun = menuBar()->addMenu(tr("&Run"));
  QMenu *menuTools = menuBar()->addMenu(tr("&Tools"));
  QMenu *menuDebugger = menuBar()->addMenu(tr("&Debugger"));

  QAction *actionOpen = menuFile->addAction(tr("&Open..."));

  QAction *actionShowDebug = menuDebugger->addAction(tr("&Show debug panel"));
  mActionPlay = menuRun->addAction(tr("&Play"));
  mActionPause = menuRun->addAction(tr("&Pause"));
  mActionReset = menuRun->addAction(tr("&Reset"));
  QAction *actionTileWatcher = menuTools->addAction(tr("&Tile Watcher"));

  menuFile->addSeparator();
  mActionLoadState = menuFile->addAction(tr("&Load state..."));
  mActionSaveState = menuFile->addAction(tr("&Save state..."));
  menuFile->addSeparator();
  QAction *actionExit = menuFile->addAction(tr("&Exit"));

  /////////////////////////////////////////////
  QPalette newPalette;
  newPalette.setColor(QPalette::Window, QColor(0, 0, 0));
  setPalette(newPalette);

  /////////////////////////////////////////////
  actionExit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
  actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  actionShowDebug->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
  mActionPlay->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  mActionPause->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
  mActionReset->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
  actionTileWatcher->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));

  mActionLoadState->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
  mActionSaveState->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));

  /////////////////////////////////////////////
  mDebug = new Debugger(this, mApp);
  mDebug->Init();

  mTileWatcher = new TileWatcher(this);
  mTileWatcher->resize(120, 120);

  ////////////////////////////////////////////
  int menuBarHeight = menuBar()->sizeHint().height();
  mGraphicsEngine = new GraphicsEngine(this, QPoint(0, menuBarHeight),
				       QSize(160, 144), mApp);
  mGraphicsEngine->SetMainWindow(this);
  mGraphicsEngine->show();
  togglePlay(false);
  mActionPlay->setEnabled(false);
  mActionReset->setEnabled(false);
  mActionSaveState->setEnabled(false);
  mActionLoadState->setEnabled(false);

  /////////////////////////////////////////////
  setMinimumSize(GB_SCREEN_X, GB_SCREEN_Y + menuBarHeight);
  resize(GB_SCREEN_X, GB_SCREEN_Y + menuBarHeight);

  //////////// Signals //////////////////////
  connect(actionExit, SIGNAL(triggered()), mApp, SLOT(quit()));
  connect(actionOpen, SIGNAL(triggered()), this, SLOT(OpenRom()));

  connect(mActionLoadState, SIGNAL(triggered()), this, SLOT(LoadState()));
  connect(mActionSaveState, SIGNAL(triggered()), this, SLOT(SaveState()));

  connect(actionShowDebug, SIGNAL(triggered()), mDebug, SLOT(show()));
  connect(actionTileWatcher, SIGNAL(triggered()), mTileWatcher, SLOT(show()));

  connect(mGraphicsEngine, SIGNAL(ChangeEmuInstance(Emulator *)),
	  mDebug, SLOT(EmuInstanceChange(Emulator *)));
  connect(mGraphicsEngine, SIGNAL(ChangeEmuInstance(Emulator *)),
   	  mTileWatcher, SLOT(SetEmu(Emulator *)));
  connect(mActionPlay, SIGNAL(triggered()), mGraphicsEngine, SLOT(PlayEmu()));
  connect(mActionPause, SIGNAL(triggered()), mGraphicsEngine, SLOT(PauseEmu()));
  connect(mActionReset, SIGNAL(triggered()), mGraphicsEngine, SLOT(ResetEmu()));

  if (mApp->arguments().size() > 1)
    {
      QString romFileName = mApp->arguments().at(1);
      if (mGraphicsEngine->NewEmulator(romFileName.toStdString().c_str()))
	togglePlay(true);
    }

}

void	MainWindow::OpenRom()
{
  QString romFileName;

  romFileName = QFileDialog::getOpenFileName(0, "Select a Game Boy ROM");
  if (romFileName != 0)
    if (mGraphicsEngine->NewEmulator(romFileName.toStdString().c_str()))
      togglePlay(true);
}

void	MainWindow::resizeEvent(QResizeEvent *event)
{
  int menuBarHeight = menuBar()->sizeHint().height();
  QSize size = event->size();
  int width, height;


  if (size.width() * GB_SCREEN_Y <= GB_SCREEN_X * size.height())
    {
      width = size.width();
      height = (width * GB_SCREEN_Y) / GB_SCREEN_X;

      int pos = ((size.height()  + menuBarHeight - height) / 2);
      mGraphicsEngine->move(0, pos > menuBarHeight ? pos : menuBarHeight);
    }
  else
    {
      height = size.height() - menuBarHeight;
      width = (height * GB_SCREEN_X) / GB_SCREEN_Y;
      mGraphicsEngine->move((size.width() - width) / 2, menuBarHeight);
    }
  mGraphicsEngine->resize(width, height);
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
  Emulator *emu = mGraphicsEngine->GetEmulator();

  if (!emu)
    return ;
  switch (keyEvent->key())
    {
    case Qt::Key_Up: emu->KeyChange(Up, true); break;
    case Qt::Key_Down: emu->KeyChange(Down, true); break;
    case Qt::Key_Right: emu->KeyChange(Right, true); break;
    case Qt::Key_Left: emu->KeyChange(Left, true); break;
    case Qt::Key_Q: emu->KeyChange(BUTTON_A, true); break;
    case Qt::Key_W: emu->KeyChange(BUTTON_B, true); break;
    case Qt::Key_Return: emu->KeyChange(Start, true); break;
    case Qt::Key_Shift: emu->KeyChange(Select, true); break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyEvent)
{
  Emulator *emu = mGraphicsEngine->GetEmulator();

  if (!emu)
    return ;
  switch (keyEvent->key())
    {
    case Qt::Key_Up: emu->KeyChange(Up, false); break;
    case Qt::Key_Down: emu->KeyChange(Down, false); break;
    case Qt::Key_Right: emu->KeyChange(Right, false); break;
    case Qt::Key_Left: emu->KeyChange(Left, false); break;
    case Qt::Key_Q: emu->KeyChange(BUTTON_A, false); break;
    case Qt::Key_W: emu->KeyChange(BUTTON_B, false); break;
    case Qt::Key_Return: emu->KeyChange(Start, false); break;
    case Qt::Key_Shift: emu->KeyChange(Select, false); break;
    }
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
