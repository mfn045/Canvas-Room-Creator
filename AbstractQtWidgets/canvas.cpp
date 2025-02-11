#include "canvas.h"

Canvas::Canvas() {
    setAcceptDrops(true);
    setStyleSheet("border: 1px solid red;");
    setRenderHint(QPainter::LosslessImageRendering);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setMouseTracking(true);
    if(useOpenGL){
        openglWidget = new OpenGLWidget();

        QSurfaceFormat format;
        format.setDepthBufferSize(0);
        format.setStencilBufferSize(8);
        format.setSamples(1);
        openglWidget->setFormat(format);
        openglWidget->setUpdateBehavior(QOpenGLWidget::PartialUpdate);

        setViewport(openglWidget);

        setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    }
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
    return QGraphicsView::resizeEvent(event);
}


void Canvas::paintEvent(QPaintEvent *event){
    if(useOpenGL){
        openglWidget->makeCurrent();
        openglWidget->getFunctions().glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        openglWidget->getFunctions().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    QGraphicsView::paintEvent(event);
}
