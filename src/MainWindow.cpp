#include <iostream>
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
  setMinimumSize(320, 240);

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
  actionExit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
  actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  actionShowDebug->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));

  /////////////////////////////////////////////
  mDebug = new Debugger(this, mApp);
  mDebug->Init();

  ////////////////////////////////////////////
  int menuBarHeight = menuBar()->sizeHint().height();
  mGraphicsEngine = new GraphicsEngine(this, QPoint(0, menuBarHeight),
				       QSize(160, 144), mApp);
  mGraphicsEngine->show();

  if (mApp->arguments().size() > 1)
    {
      QString romFile = mApp->arguments().at(1);
      mGraphicsEngine->NewEmulator(romFile.toStdString().c_str());
    }

  //////////// Signals //////////////////////
  connect(actionExit, SIGNAL(triggered()), mApp, SLOT(quit()));
  connect(actionOpen, SIGNAL(triggered()), this, SLOT(OpenRom()));
  connect(actionShowDebug, SIGNAL(triggered()), mDebug, SLOT(show()));

  connect(mGraphicsEngine, SIGNAL(ChangeEmuInstance(Emulator *)),
	  mDebug, SLOT(EmuInstanceChange(Emulator *)));
  connect(actionPlay, SIGNAL(triggered()), mGraphicsEngine, SLOT(PlayEmu()));
  connect(actionPause, SIGNAL(triggered()), mGraphicsEngine, SLOT(PauseEmu()));
}

void	MainWindow::OpenRom()
{
  QString fileName;

  fileName = QFileDialog::getOpenFileName(0, "Select a Game Boy ROM",
					  getcwd(NULL, 64));
  if (fileName != 0)
    mGraphicsEngine->NewEmulator(fileName.toStdString().c_str());
}

