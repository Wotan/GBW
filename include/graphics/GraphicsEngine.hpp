#ifndef GRAPHICS_ENGINE_HPP_
# define GRAPHICS_ENGINE_HPP_

# include "App.hpp"
# include "Emulator.hpp"
# include "RenderOpenGL.hpp"

# define GB_SCREEN_X 160
# define GB_SCREEN_Y 144

class App;
class Emulator;

class GraphicsEngine : public RenderOpenGL
{
Q_OBJECT

public:
  GraphicsEngine(QWidget *parent, const QPoint& position,
		 const QSize& size, App *app);
  ~GraphicsEngine();
  virtual void	OnInit();
  virtual void	OnUpdate();
  void	ClearScreen();
  void	FillScreen();
  char	*GetScreenArrayPtr() {return mScreenArray;};

  bool	NewEmulator(const char *fileName);
  void	CloseEmulator();
  Emulator *GetEmulator() {return mEmu;};

public slots:
  void	PlayEmu();
  void	PauseEmu();

signals:
  void	ChangeEmuInstance(Emulator *emu);

private:

  char		mScreenArray[GB_SCREEN_X * GB_SCREEN_Y * 4];
  App		*mApp;
  Emulator	*mEmu;

};

#endif // GRAPHICS_ENGINE_HPP_
