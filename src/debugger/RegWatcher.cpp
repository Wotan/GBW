#include <iostream>
#include <QPainter>
#include <QFrame>
#include "RegWatcher.hpp"

RegWatcher::RegWatcher(QWidget *parent) :
  QFrame(parent)
{
  setMinimumSize(200, 200);
  setMaximumSize(200, 200);

  setFrameStyle(QFrame::Panel | QFrame::Sunken);
  setLineWidth(1);
}

void	RegWatcher::paintEvent(QPaintEvent *event)
{
  QFrame::paintEvent(event);

  QPainter painter(this);
  painter.drawText(5, 20, "FF");
  std::cout << "Redraw" << std::endl;
}
