#ifndef DEBUGGER_HPP_
# define DEBUGGER_HPP_

# include <QPushButton>
# include <QShortcut>
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

  static const char *GetOpMnemonic(Emulator *emu, int addr);
  static const char *GetOpDesc(Emulator *emu, int addr);

public slots:
  void		EmuInstanceChange(Emulator *emu);
  void		NextOpcode();

private:
  App		*mApp;
  Emulator	*mEmu;
  RegWatcher	*mRegWatcher;
  MemWatcher	*mMemWatcher;
  QPushButton	*mNextOp;
  QShortcut	*mExitShortcut;
  QShortcut	*mNextOpShortcut;
};

#endif // DEBUGGER_HPP_
