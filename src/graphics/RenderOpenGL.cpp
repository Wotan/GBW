#include "RenderOpenGL.hpp"

RenderOpenGL::RenderOpenGL(QWidget *parent, int frameTime) :
  QGLWidget(parent)
{
  mTimer.setInterval(frameTime);
}

void RenderOpenGL::initializeGL()
{
  glClearColor(.5,.5,.5,0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glEnable(GL_TEXTURE_2D);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  connect(&mTimer, SIGNAL(timeout()), this, SLOT(repaint()));
  mTimer.start();
  OnInit();
}

void RenderOpenGL::InitTexture(int width, int height, unsigned char *array,
			       bool linear)
{
  glGenTextures(1,&mTextureName);
  glBindTexture(GL_TEXTURE_2D, mTextureName);
  glTexImage2D (GL_TEXTURE_2D, 0, 4, width, height, 0,
   		GL_RGBA, GL_UNSIGNED_BYTE, array);
  UpdateLinear(linear);
  mScreenHeight = height;
  mScreenWidth = width;
}

void RenderOpenGL::UpdateLinear(bool on)
{
  glBindTexture(GL_TEXTURE_2D, mTextureName);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		  on ? GL_LINEAR : GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		  on ? GL_LINEAR : GL_NEAREST);
}

void RenderOpenGL::UpdateScreen(unsigned char *array)
{
  glBindTexture(GL_TEXTURE_2D, mTextureName);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mScreenWidth, mScreenHeight,
		  GL_RGBA, GL_UNSIGNED_BYTE, array);

}

void RenderOpenGL::resizeGL(int width, int height)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, width, height);
}

void RenderOpenGL::paintGL()
{
  OnUpdate();

  glBindTexture(GL_TEXTURE_2D, mTextureName);

  glBegin(GL_QUADS);

  glTexCoord2f(0, 1);
  glVertex2f(-1, -1);

  glTexCoord2f(0, 0);
  glVertex2f(-1, 1);

  glTexCoord2f(1, 0);
  glVertex2f(1, 1);

  glTexCoord2f(1, 1);
  glVertex2f(1, -1);

  glEnd();
}

