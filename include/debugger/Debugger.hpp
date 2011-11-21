#ifndef DEBUGGER_HPP_
# define DEBUGGER_HPP_

# include <QPushButton>
# include <QWidget>
# include <QDialog>
# include "App.hpp"
# include "Emulator.hpp"
# include "RegWatcher.hpp"
# include "MemWatcher.hpp"

class App;
class Emulator;
class RegWatcher;
class MemWatcher;

class Debugger : public QDialog
{
  Q_OBJECT

public:
  Debugger(QWidget *parent, App *mApp);
  ~Debugger();
  bool	Init();

public slots:
  void		EmuInstanceChange(Emulator *emu);
  void		NextOpcode();

private:
  App		*mApp;
  Emulator	*mEmu;
  RegWatcher	*mRegWatcher;
  MemWatcher	*mMemWatcher;
  QPushButton	*mNextOp;
};

#endif // DEBUGGER_HPP_
