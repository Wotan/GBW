#ifndef APP_HPP_
# define APP_HPP_

#include <QApplication>
#include "MainWindow.hpp"

class MainWindow;
class QSettings;

class App : public QApplication
{
public:
  App(int ac, char **av);
  ~App();
  void	Init();
  QSettings	*GetSettings() {return mSettings;}

private:
  MainWindow *mMainWindow;
  QSettings	*mSettings;
};

#endif // !APP_HPP_
