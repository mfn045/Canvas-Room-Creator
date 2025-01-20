#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget* parent, Qt::WindowFlags f) : QOpenGLWidget(parent, f) {

}


void OpenGLWidget::initializeGL(){
    qDebug() << "OpenGL functions initialized!";
    f.initializeOpenGLFunctions();
}


void OpenGLWidget::paintEvent(QPaintEvent *e){
    f.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    f.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return QOpenGLWidget::paintEvent(e);
}

void OpenGLWidget::paintGL(){
    f.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    f.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    context()->swapBuffers(context()->surface());
}


QOpenGLFunctions& OpenGLWidget::getFunctions(){
    return f;
}
