#include <iostream>
#include "App.hpp"

int		main(int ac, char **av)
{
  App		app(ac, av);

  app.Init();
  return app.exec();
}

