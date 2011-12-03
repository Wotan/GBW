#ifndef TILE_WATCHER_HPP_
# define TILE_WATCHER_HPP_

# include <QDialog>
# include <QPainter>
# include "Emulator.hpp"

class Emulator;
class HexSpinBox;

class TileWatcher : public QDialog
{
  Q_OBJECT

public:
  TileWatcher(QWidget *parent);
  virtual void paintEvent(QPaintEvent *);
  const char	*SetColor(int spriteColor, BYTE bpalette);

public slots:
  void	SetEmu(Emulator *emu) {mEmu = emu;}
private:
  Emulator	*mEmu;
  HexSpinBox	*mBoxAddr;
};

#endif // !TILE_WATCHER_HPP_
