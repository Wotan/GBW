#ifndef REG_WATCHER_HPP
# define REG_WATCHER_HPP_

# include <QFrame>
# include <QPainter>

class RegWatcher : public QFrame
{
public:
  RegWatcher(QWidget *parent);
  virtual void paintEvent(QPaintEvent *);

private:

};

#endif // !REG_WATCHER_HPP_
