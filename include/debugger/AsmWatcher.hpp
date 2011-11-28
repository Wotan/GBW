#ifndef ASM_WATCHER_HPP_
# define ASM_WATCHER_HPP_

# include <QCheckBox>
# include "MemWatcher.hpp"

class HexSpinBox;

class AsmWatcher : public QFrame
{
  Q_OBJECT

public:
  AsmWatcher(QWidget *parent);
  ~AsmWatcher();
  virtual void paintEvent(QPaintEvent *);
  void	SetEmu(Emulator *emu) {mEmu = emu;}


private:
  HexSpinBox	*mBoxAddr;
  Emulator	*mEmu;
  QCheckBox	*mBoxFollow;
};

#endif // !ASM_WATCHER_HPP_
