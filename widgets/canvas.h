#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QObject>
#include <QMouseEvent>
#include "openglwidget.h"
#include <QOpenGLFunctions>

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
    Canvas();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void canvasMousePressed(QPointF pos);
    void canvasMouseMoved(QPointF pos);
    void canvasDropped(QPointF pos);

private:
    OpenGLWidget* openglWidget = nullptr;
    bool useOpenGL = true;
};

#endif // CANVAS_H
