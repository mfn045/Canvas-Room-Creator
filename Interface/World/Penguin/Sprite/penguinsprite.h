#ifndef PENGUINSPRITE_H
#define PENGUINSPRITE_H
#include <QDomDocument>
#include <QDomElement>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include "penguinspritebase.h"
#include "AbstractQtWidgets/scene.h"
#include "Clothing/penguinspriteclothing.h"
#include "Interface/World/ChatBubble/chatbubble.h"
#include "ThreadPoolManager/threadpoolmanager.h"


class PenguinSprite : public PenguinSpriteBase
{
    Q_OBJECT
public:

    explicit PenguinSprite();
    ~PenguinSprite();

    void initializeEvents(Scene* scene);
    void uninitializeEvents();

    void sendChatBubble(QString msg);

    QPointF getDestination();
    QPointF setDestination(QPointF destination);

    void walkTo(QPointF pos);

    void changeColor(QString color);

    double getVelocity();
    double setVelocity(double velocity);

    void setHead(int headId);
    void setFace(int faceId);
    void setNeck(int neckId);
    void setBody(int bodyId);
    void setHand(int handId);
    void setFeet(int feetId);
    PenguinSpriteClothing* loadItem(int id);

private:
    QPointF destination;

    double velocity = 0;

    Scene* parent = nullptr;

    ChatBubble* bubble = nullptr;

    bool active = false;


    AtlasCanvasObject* head = nullptr;
    AtlasCanvasObject* face = nullptr;
    AtlasCanvasObject* neck = nullptr;
    AtlasCanvasObject* body = nullptr;
    AtlasCanvasObject* hand = nullptr;
    AtlasCanvasObject* feet = nullptr;


public slots:
    void animationDone() override;
    void setPosition(QPointF pos);
    void sceneMouseMoved(QPointF pos);
    void sceneMousePressed(QPointF pos);
    void sceneKeyPressed(int key);
    void resetPenguin();


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void clickedPenguin();
    void changedDestination();
};

#endif // PENGUINSPRITE_H
