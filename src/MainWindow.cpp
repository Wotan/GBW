#include <iostream>
#include "GraphicsEngine.hpp"
#include "MainWindow.hpp"

MainWindow::MainWindow(App *app):
  mApp(app)
{

}

MainWindow::~MainWindow()
{
  delete mGraphicsEngine;
  std::cout << "MainWindow deleted" << std::endl;
}

void	MainWindow::Init()
{
  /////////////////////////////////////////////
  setMinimumSize(320, 240);

  /////////////////////////////////////////////
  QMenu *menuFile = menuBar()->addMenu(tr("&File"));
  QMenu *menuPlay = menuBar()->addMenu(tr("&Play"));
  QMenu *menuDebugger = menuBar()->addMenu(tr("&Debugger"));

  QAction *actionOpen = menuFile->addAction(tr("&Open"));
  QAction *actionExit = menuFile->addAction(tr("&Exit"));

  /////////////////////////////////////////////
  actionExit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

  /////////////////////////////////////////////
  connect(actionExit, SIGNAL(triggered()), mApp, SLOT(quit()));


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
  //mGraphicsEngine->NewEmulator();
}
