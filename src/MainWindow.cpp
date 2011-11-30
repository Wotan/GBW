#include <iostream>
#include <QPalette>
#include <QFileDialog>
#include "GraphicsEngine.hpp"
#include "MainWindow.hpp"

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
  QMenu *menuDebugger = menuBar()->addMenu(tr("&Debugger"));

  QAction *actionOpen = menuFile->addAction(tr("&Open"));
  QAction *actionExit = menuFile->addAction(tr("&Exit"));
  QAction *actionShowDebug = menuDebugger->addAction(tr("&Show debug panel"));
  QAction *actionPlay = menuRun->addAction(tr("&Play"));
  QAction *actionPause = menuRun->addAction(tr("&Pause"));

  /////////////////////////////////////////////
  QPalette newPalette;
  newPalette.setColor(QPalette::Window, QColor(0, 0, 0));
  setPalette(newPalette);

  /////////////////////////////////////////////
  actionExit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
  actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  actionShowDebug->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
  actionPlay->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  actionPause->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));

  /////////////////////////////////////////////
  mDebug = new Debugger(this, mApp);
  mDebug->Init();

  ////////////////////////////////////////////
  int menuBarHeight = menuBar()->sizeHint().height();
  mGraphicsEngine = new GraphicsEngine(this, QPoint(0, menuBarHeight),
				       QSize(160, 144), mApp);
  mGraphicsEngine->show();

  /////////////////////////////////////////////
  setMinimumSize(GB_SCREEN_X, GB_SCREEN_Y + menuBarHeight);
  resize(GB_SCREEN_X, GB_SCREEN_Y + menuBarHeight);

  //////////// Signals //////////////////////
  connect(actionExit, SIGNAL(triggered()), mApp, SLOT(quit()));
  connect(actionOpen, SIGNAL(triggered()), this, SLOT(OpenRom()));
  connect(actionShowDebug, SIGNAL(triggered()), mDebug, SLOT(show()));

  connect(mGraphicsEngine, SIGNAL(ChangeEmuInstance(Emulator *)),
	  mDebug, SLOT(EmuInstanceChange(Emulator *)));
  connect(actionPlay, SIGNAL(triggered()), mGraphicsEngine, SLOT(PlayEmu()));
  connect(actionPause, SIGNAL(triggered()), mGraphicsEngine, SLOT(PauseEmu()));

  if (mApp->arguments().size() > 1)
    {
      QString romFile = mApp->arguments().at(1);
      mGraphicsEngine->NewEmulator(romFile.toStdString().c_str());
    }

}

void	MainWindow::OpenRom()
{
  QString fileName;

  fileName = QFileDialog::getOpenFileName(0, "Select a Game Boy ROM",
					  getcwd(NULL, 64));
  if (fileName != 0)
    mGraphicsEngine->NewEmulator(fileName.toStdString().c_str());
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
