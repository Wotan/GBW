#ifndef GRAPHICS_ENGINE_HPP_
# define GRAPHICS_ENGINE_HPP_

# include "App.hpp"
# include "QSFMLCanvas.hpp"
# include "Emulator.hpp"

# define GB_SCREEN_X 160
# define GB_SCREEN_Y 144

class App;
class Emulator;

class GraphicsEngine : public QSFMLCanvas
{
Q_OBJECT

public:
  GraphicsEngine(QWidget *parent, const QPoint& position,
		 const QSize& size, App *app);
  ~GraphicsEngine();
  void	OnInit();
  void	OnUpdate();
  void	ClearScreen();
  void	FillScreen();
  char	*GetScreenArrayPtr() {return mScreenArray;};

  bool	NewEmulator(const char *fileName);
  void	CloseEmulator();

public slots:
  void	PlayEmu();
  void	PauseEmu();

signals:
  void	ChangeEmuInstance(Emulator *emu);

private:
  sf::Texture	mScreen;
  sf::Sprite	mSpriteScreen;

  // bpp = 4 r g b a
  char		mScreenArray[GB_SCREEN_X * GB_SCREEN_Y * 4];
  App		*mApp;
  Emulator	*mEmu;
};

#endif // GRAPHICS_ENGINE_HPP_
