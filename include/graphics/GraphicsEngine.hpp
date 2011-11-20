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
  void	DrawScanLine(int numScanLine);
  char	*GetScanLinePtr() {return mCurrentScanLine;};
  bool	NewEmulator(const char *fileName);
  void	CloseEmulator();

public slots:
  void	PlayEmu() {if (mEmu) mEmu->Play();}
  void	PauseEmu() {if(mEmu) mEmu->Pause();}

signals:
  void	ChangeEmuInstance(Emulator *emu);

private:
  sf::Texture	mScreen;
  sf::Sprite	mSpriteScreen;
  char		mCurrentScanLine[GB_SCREEN_X * 4]; // bpp = 4
  App		*mApp;
  Emulator	*mEmu;
};

#endif // GRAPHICS_ENGINE_HPP_
