#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsObject>
#include "../../../CanvasObject/Multi/multicanvasobject.h"

class AbstractButton : public MultiCanvasObject
{
    Q_OBJECT
public:
    explicit AbstractButton(MultiCanvasObject *parent = nullptr);
    enum STATE {
        UP,
        OVER,
        DOWN,
        DISABLED
    };

    struct BUTTONPROPERTIES : public PROPERTIES {
        STATE state = UP;
    };

    void setCurrentFrames(STATE state);
    virtual MultiCanvasObject* setIcon(QString filePath);
    void setUp(QString filePath);
    void setDown(QString filePath);
    void setOver(QString filePath);
    void setDisabled(QString filePath);
    void setDisabled(bool disabled);

    MultiCanvasObject* getIcon();

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

    MultiCanvasObject* icon = nullptr;

signals:
    void clicked();
};

#endif // BUTTON_H
