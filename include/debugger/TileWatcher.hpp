#ifndef TILE_WATCHER_HPP_
# define TILE_WATCHER_HPP_

# include <QWidget>
# include <QPainter>

class Emulator;
class HexSpinBox;

class TileWatcher : public QWidget
{
public:
  TileWatcher(QWidget *parent);

  virtual void paintEvent(QPaintEvent *);
  void	SetEmu(Emulator *emu) {mEmu = emu;}
  const char	*SetColor(int spriteColor, BYTE bpalette);
private:
  Emulator	*mEmu;
  HexSpinBox	*mBoxAddr;
};

#endif // !TILE_WATCHER_HPP_
