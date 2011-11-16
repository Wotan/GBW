#ifndef GRAPHICS_ENGINE_HPP_
# define GRAPHICS_ENGINE_HPP_

# include "App.hpp"
# include "QSFMLCanvas.hpp"

# define GB_SCREEN_X 160
# define GB_SCREEN_Y 144

class App;

class GraphicsEngine : public QSFMLCanvas
{
public:
  GraphicsEngine(QWidget *parent, const QPoint& position,
		 const QSize& size, App *app);
  ~GraphicsEngine();
  void	OnInit();
  void	OnUpdate();
  void	ClearScreen();
  void	DrawScanLine(int numScanLine);
  char	*GetScanLinePtr() {return mCurrentScanLine;};

private:
  sf::Texture	mScreen;
  sf::Sprite	mSpriteScreen;
  char		mCurrentScanLine[GB_SCREEN_X * 4]; // bpp = 4
  App		*mApp;
};

#endif // GRAPHICS_ENGINE_HPP_
