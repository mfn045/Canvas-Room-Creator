#ifndef ABSTRACTCANVASOBJECT_H
#define ABSTRACTCANVASOBJECT_H

#include <QPointF>
#include <QCursor>
#include <QPainter>
#include <QImage>
#include <QSvgRenderer>
#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "../Objects/Constants/constants.h"

class AbstractCanvasObject : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    explicit AbstractCanvasObject(AbstractCanvasObject* parent = nullptr);

    virtual void nextFrame(bool loop = true, bool force = false) = 0;
    virtual void setFrame(int currentFrame) = 0;
    virtual void prevFrame(bool loop = true, bool force = false) = 0;
    int getCurrentFrame();

    int getID();
    int setID(int id);

    QString getName();
    QString setName(QString name);

    QPointF getOrigin();
    QPointF setOrigin(QPointF origin);

    bool containsActionFlag(CANVAS::ACTION flag);
    void setActionFlags(int flags);
    int getActionFlags();

    bool isMouseTrackable();
    bool setIsMouseTrackable(bool trackable);
    bool isClickable();
    bool setIsClickable(bool isClickable);
    bool isHoverable();
    bool setIsHoverable(bool isClickable);

    bool hasAnimationLoop();
    bool setHasAnimationLoop(bool animationLoop);
    bool isAnimationOn();
    bool setIsAnimationOn(bool animationOn);

    virtual bool isTransparentPixel(QPointF pos);

    bool isFramePaused();

protected:
    bool animationLoop = false;
    bool animationOn = true;
    int currentFrame = 0;

    bool isImageLatest = false;
    std::unique_ptr<QImage> image;
    QList<int> framePauses;


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    unsigned short actionFlags = 0;
    int id = 0;
    QPointF origin;
    QString name = "";

signals:
    virtual void animationDone();
    void hoverEnter(QPointF pos);
    void hoverLeave(QPointF pos);
    void hoverMove(QPointF pos);
    void mousePress(QPointF pos);
    void mouseMove(QPointF pos);
    void mouseRelease(QPointF pos);
};

#endif // ABSTRACTCANVASOBJECT_H
