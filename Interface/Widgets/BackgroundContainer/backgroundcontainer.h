#ifndef BACKGROUNDCONTAINER_H
#define BACKGROUNDCONTAINER_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include "Objects/Constants/constants.h"

class BackgroundContainer : public QGraphicsItem
{
public:
    BackgroundContainer(float width = 0, float height = 0);

    void setColor(BACKGROUNDCONTAINER::COLOR color);
    BACKGROUNDCONTAINER::COLOR getColor();

    float setWidth(float width);
    float getWidth();

    float setHeight(float height);
    float getHeight();

    bool hasBackdrop();
    bool setHasBackdrop(bool backDrop);

    void setBackdropColor(QColor color);

    void init();


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    QRectF boundingRect() const override;

private:
    QRectF rect = QRectF(0,0,0,0);

    float width = 0;
    float height = 0;

    QPainterPath path;
    QPainterPath path2;
    QPainterPath path3;
    QPainterPath path4a;
    QPainterPath path4b;
    QPainterPath path5;

    QPainterPath createPath(float offset, float additionalBottomRightXYShrink = 0);

    QColor backDropColor = QColor(0,0,0,0);

    BACKGROUNDCONTAINER::COLOR color = BACKGROUNDCONTAINER::COLOR::BLUE;

    bool initialized = false;
    bool backDrop = false;

};

#endif // BACKGROUNDCONTAINER_H
