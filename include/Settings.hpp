#ifndef SETTINGS_HPP_
# define SETTINGS_HPP_

class KeyEdit : public QLineEdit
{
public:
  KeyEdit(int id, App *app, QWidget *parent);
  virtual void keyPressEvent(QKeyEvent *keyEvent);
private:
  App *mApp;
  int	mId; // 0-7 default / 8-15 alias
};

class InputWindow : public QDialog
{
public:
  InputWindow(App *app, QWidget *parent);
  void	InitWidget();
  static std::string GetKeyString(Qt::Key key);

private:
  QLabel	*mTabLabel[8];
  QGridLayout	*mMainLayout;
  App *mApp;
};

class	VideoSettings : public QDialog
{
public:
  VideoSettings(App *app, QWidget *parent);
  void	Init();

private:
  QGridLayout	*mMainLayout;
  QCheckBox	*mBilinear;
  App *mApp;
};

#endif // !SETTINGS_HPP_
