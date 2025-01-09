#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsObject>
#include "../../../canvasobject.h"

class AbstractButton : public CanvasObject
{
    Q_OBJECT
public:
    explicit AbstractButton(CanvasObject *parent = nullptr);
    enum STATE {
        UP,
        OVER,
        DOWN
    };

    struct BUTTONPROPERTIES : public PROPERTIES {
        STATE state = UP;
    };

    void setCurrentFrames(STATE state);
    virtual void setIcon(QString filePath);
    void setUp(QString filePath);
    void setDown(QString filePath);
    void setOver(QString filePath);

    CanvasObject* getIcon();

    virtual QVariant positionChanged(const QVariant& pos);

private:
    STATE currentState = UP;

protected:
    bool initialized = false;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    CanvasObject* icon = nullptr;

signals:
    void clicked();
};

#endif // BUTTON_H
