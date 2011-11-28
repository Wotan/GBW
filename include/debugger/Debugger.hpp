#ifndef DEBUGGER_HPP_
# define DEBUGGER_HPP_

# include <QPushButton>
# include <QShortcut>
# include <QWidget>
# include <QDialog>
# include "App.hpp"
# include "Emulator.hpp"
# include "InfosWatcher.hpp"
# include "MemWatcher.hpp"
# include "AsmWatcher.hpp"

class App;
class Emulator;
class InfosWatcher;
class MemWatcher;
class AsmWatcher;

class Debugger : public QDialog
{
  Q_OBJECT

public:
  Debugger(QWidget *parent, App *mApp);
  ~Debugger();
  bool	Init();

  static const char *GetOpMnemonic(Emulator *emu, int addr);
  static const char *GetOpDesc(Emulator *emu, int addr);
  static int GetOpSize(Emulator *emu, int addr);
  void RepaintAll();

public slots:
  void		EmuInstanceChange(Emulator *emu);
  void		NextOpcode();
  void		NextXOpcode();

private:
  App		*mApp;
  Emulator	*mEmu;
  InfosWatcher	*mInfosWatcher;
  MemWatcher	*mMemWatcher;
  AsmWatcher	*mAsmWatcher;

  QPushButton	*mNextOp;
  QShortcut	*mExitShortcut;
  QShortcut	*mNextOpShortcut;
  QSpinBox	*mNbOpcode;
  QPushButton	*mNextNbOp;
};

#endif // DEBUGGER_HPP_
