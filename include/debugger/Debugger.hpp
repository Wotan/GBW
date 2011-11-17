#ifndef DEBUGGER_HPP_
# define DEBUGGER_HPP_

# include <QWidget>
# include <QDialog>
# include "App.hpp"
# include "Emulator.hpp"

class Debugger : public QDialog
{
  Q_OBJECT

public:
  Debugger(QWidget *parent, App *mApp);
  ~Debugger();
  bool	Init();

public slots:
  void		EmuInstanceChange(Emulator *emu);

private:
  App		*mApp;
  Emulator	*mEmu;
};

#endif // DEBUGGER_HPP_
