#ifndef REG_WATCHER_HPP_
# define REG_WATCHER_HPP_

# include <QFrame>
# include <QPainter>

class Emulator;

class InfosWatcher : public QFrame
{
public:
  InfosWatcher(QWidget *parent);
  virtual void paintEvent(QPaintEvent *);
  void	SetEmu(Emulator *emu) {mEmu = emu;}
  void	DrawRegister(QPainter &painter);
  void	DrawLCDInfos(QPainter &painter);
private:
  Emulator *mEmu;
};

#endif // !REG_WATCHER_HPP_
