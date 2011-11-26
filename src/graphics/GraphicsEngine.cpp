#include <iostream>
#include <QPoint>
#include <QSize>
#include "GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine(QWidget *parent, const QPoint& position,
			       const QSize& size, App *app) :
  QSFMLCanvas(parent, position,  size, 32),
  mApp(app),
  mEmu(NULL)
{
  std::cout << "GraphicsEngine created" << std::endl;
}

GraphicsEngine::~GraphicsEngine()
{
  if (mEmu)
    delete mEmu;
  std::cout << "GraphicsEngine deleted" << std::endl;
}

void	GraphicsEngine::OnInit()
{
  mScreen.Create(GB_SCREEN_X, GB_SCREEN_Y);
  mSpriteScreen.SetTexture(mScreen);
  ClearScreen();
  // mSpriteScreen.SetScale(size().width() / mSpriteScreen.GetSize().x,
  // 			 size().height() / mSpriteScreen.GetSize().y);

}

// Call every 16ms
void	GraphicsEngine::OnUpdate()
{
  Clear();
  if (mEmu)
    {
      mEmu->DoFrame();
      Draw(mSpriteScreen);
      FillScreen();

      mEmu->DoFrame();
      FillScreen();
      Draw(mSpriteScreen);
    }


  static sf::Clock clock;
  std::cout << "Update " <<  clock.GetElapsedTime()
	    << std::endl;
  clock.Reset();
}

void	GraphicsEngine::FillScreen()
{
  mScreen.Update((sf::Uint8 *)mScreenArray);
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
