#ifndef RENDER_OPENGL_HPP_
# define RENDER_OPENGL_HPP_

# include <QGLWidget>
# include <QTimer>

class RenderOpenGL : public QGLWidget
{
  Q_OBJECT

public:
  RenderOpenGL(QWidget *parent = 0, int frameTime = 0);
  virtual void initializeGL();
  void	InitTexture(int width, int height, unsigned char *array);
  void	UpdateScreen(unsigned char *array);
  virtual void resizeGL(int width, int height);
  virtual void paintGL();
  virtual void keyPressEvent(QKeyEvent *keyEvent) = 0;
  virtual void OnInit() = 0;
  virtual void OnUpdate() = 0;

private:
  QTimer  mTimer;
  unsigned int mTextureName;
  unsigned int		mScreenHeight;
  unsigned int		mScreenWidth;
};

#endif // !RENDER_OPENGL_HPP_
