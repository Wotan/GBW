#ifndef REG_WATCHER_HPP_
# define REG_WATCHER_HPP_

# include <QFrame>
# include <QPainter>

class Emulator;

class RegWatcher : public QFrame
{
public:
  RegWatcher(QWidget *parent);
  virtual void paintEvent(QPaintEvent *);
  void	SetEmu(Emulator *emu) {mEmu = emu;}

private:
  Emulator *mEmu;
};

#endif // !REG_WATCHER_HPP_
