#include "canvas.h"

Canvas::Canvas() {
    setAcceptDrops(true);
    setRenderHint(QPainter::LosslessImageRendering);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setMouseTracking(true);
}


void Canvas::mouseMoveEvent(QMouseEvent *event){
    emit canvasMouseMoved(event->pos());
    return QGraphicsView::mouseMoveEvent(event);
}

void Canvas::mousePressEvent(QMouseEvent *event){
    emit canvasMousePressed(event->pos());
    return QGraphicsView::mousePressEvent(event);
}


void Canvas::dropEvent(QDropEvent *event){
    emit canvasDropped(event->position());
    return QGraphicsView::dropEvent(event);
}


void Canvas::resizeEvent(QResizeEvent *event){
    fitInView(scene()->sceneRect(),Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}
