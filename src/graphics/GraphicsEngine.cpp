#include <iostream>
#include <QPoint>
#include <QSize>
#include "GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine(QWidget *parent, const QPoint& position,
			       const QSize& size, App *app) :
  RenderOpenGL(parent, 16),
  mApp(app),
  mEmu(NULL),
  mMainWindow(0)
{
  move(position);
  resize(size);
}

GraphicsEngine::~GraphicsEngine()
{
  if (mEmu)
    delete mEmu;
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
  for (int i = 0; i < GB_SCREEN_X * GB_SCREEN_Y * 4; i += 4)
    {
      mScreenArray[i] = 0x0;
      mScreenArray[i + 1] = 0x0;
      mScreenArray[i + 2] = 0x0;
      mScreenArray[i + 3] = 0xFF;
    }
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
  mRomPath = fileName;
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
    {
    mEmu->Play();
    if (mMainWindow)
      mMainWindow->togglePlay(true);
    }
}

void	GraphicsEngine::PauseEmu()
{
  if(mEmu)
    {
      mEmu->Pause();
      if (mMainWindow)
	mMainWindow->togglePlay(false);
    }
}

void GraphicsEngine::ResetEmu()
{
  if (mRomPath.size() != 0)
    {
      NewEmulator(mRomPath.c_str());
      PlayEmu();
    }
}
