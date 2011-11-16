#include <iostream>
#include <QPoint>
#include <QSize>
#include "GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine(QWidget *parent, const QPoint& position,
			       const QSize& size, App *app) :
  QSFMLCanvas(parent, position,  size, 16),
  mApp(app)
{

}

GraphicsEngine::~GraphicsEngine()
{
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
  Draw(mSpriteScreen);
}

void	GraphicsEngine::DrawScanLine(int numScanLine)
{
  mScreen.Update((sf::Uint8 *)mCurrentScanLine, GB_SCREEN_X,
		 1, 0, numScanLine);
}

void	GraphicsEngine::ClearScreen()
{
  for (int i = 0; i < GB_SCREEN_X * 4; i ++)
    mCurrentScanLine[i] = 0x00;
  for (int i = 0; i < GB_SCREEN_Y; i++)
    DrawScanLine(i);
}
