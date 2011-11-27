#include <iostream>
#include <QPoint>
#include <QSize>
#include "GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine(QWidget *parent, const QPoint& position,
			       const QSize& size, App *app) :
  RenderOpenGL(parent, 16),
  mApp(app),
  mEmu(NULL)
{
  std::cout << "GraphicsEngine created" << std::endl;
  move(position);
  resize(size);
}

GraphicsEngine::~GraphicsEngine()
{
  if (mEmu)
    delete mEmu;
  std::cout << "GraphicsEngine deleted" << std::endl;
}

void	GraphicsEngine::OnInit()
{
  InitTexture(GB_SCREEN_X, GB_SCREEN_Y, (unsigned char *)mScreenArray);
  ClearScreen();
}

// Call every 16ms
void	GraphicsEngine::OnUpdate()
{
  if (mEmu)
    {
      mEmu->DoFrame();
      FillScreen();
    }
}

void	GraphicsEngine::FillScreen()
{
  UpdateScreen((unsigned char *)mScreenArray);
}

void	GraphicsEngine::ClearScreen()
{
  for (int i = 0; i < GB_SCREEN_X * GB_SCREEN_Y * 4; i ++)
    mScreenArray[i] = 0x00;
  FillScreen();
}

bool	GraphicsEngine::NewEmulator(const char *fileName)
{
  if (mEmu)
    delete mEmu;

  mEmu = new Emulator(mApp, this);
  if (!mEmu->Init(fileName))
    {
      CloseEmulator();
      return false;
    }
  emit ChangeEmuInstance(mEmu);
  return true;
}

void	GraphicsEngine::CloseEmulator()
{
  delete mEmu;
  mEmu = 0;
  emit ChangeEmuInstance(mEmu);
}

void	GraphicsEngine::PlayEmu()
{
  if (mEmu)
    mEmu->Play();
}

void	GraphicsEngine::PauseEmu()
{
  if(mEmu)
    mEmu->Pause();
}

void GraphicsEngine::keyPressEvent(QKeyEvent *keyEvent)
{


}
