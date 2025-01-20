#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class OpenGLWidget : public QOpenGLWidget
{
public:
    explicit OpenGLWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QOpenGLFunctions& getFunctions();

protected:
    void initializeGL() override;
    void paintEvent(QPaintEvent *e) override;
    void paintGL() override;

private:
    QOpenGLFunctions f;
    QTimer* timer = nullptr;
};

#endif // OPENGLWIDGET_H
