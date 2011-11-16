#ifndef APP_HPP_
# define APP_HPP_

#include <QApplication>
#include "MainWindow.hpp"

class MainWindow;

class App : public QApplication
{
public:
  App(int ac, char **av);
  ~App();
  void	Init();
private:
  MainWindow *mMainWindow;
};

#endif // !APP_HPP_
