#ifndef MEM_WATCHER_HPP_
# define MEM_WATCHER_HPP_

# include <QPushButton>
# include <QSpinBox>
# include <QFrame>
# include <QScrollBar>
# include <QComboBox>
# include "Emulator.hpp"


class Emulator;

class HexSpinBox : public QSpinBox
{
  Q_OBJECT

public:
  HexSpinBox(QWidget *parent = 0);
  ~HexSpinBox();

protected:
  QValidator::State validate(QString &text, int &pos) const;
  int		valueFromText(const QString &text) const;
  QString	textFromValue(int value) const;

private:
  QRegExpValidator *mValidator;
};

class MemWatcher : public QFrame
{
  Q_OBJECT

public:
  MemWatcher(QWidget *parent);
  ~MemWatcher();
  virtual void paintEvent(QPaintEvent *);
  void	SetEmu(Emulator *emu) {mEmu = emu;}

public slots:
  void	AliasChange(int id);

private:
  HexSpinBox	*mBoxAddr;
  Emulator	*mEmu;
  QScrollBar	*mScrollBar;
  QComboBox	*mAddrAlias;
};

#endif // !MEM_WATCHER_HPP_
