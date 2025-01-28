#ifndef PENGUINSPRITE_H
#define PENGUINSPRITE_H
#include <QDomDocument>
#include <QDomElement>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QThread>
#include <QObject>
#include "../../../canvasobject.h"
#include "penguinspritebase.h"
#include "../../../widgets/scene.h"
#include "Clothing/penguinspriteclothing.h"
#include "../../Constants/constants.h"
#include "../../../Interface/ChatBubble/chatbubble.h"

class PenguinSprite : public PenguinSpriteBase
{
    Q_OBJECT
public:

    explicit PenguinSprite(Scene* parent = nullptr);

    void sendChatBubble(QString msg);

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
    QThread* thread = nullptr;

    double velocity = 0;

    Scene* parent = nullptr;

    ChatBubble* bubble = nullptr;

    bool active = false;


    CanvasObject* head = nullptr;
    CanvasObject* face = nullptr;
    CanvasObject* neck = nullptr;
    CanvasObject* body = nullptr;
    CanvasObject* hand = nullptr;
    CanvasObject* feet = nullptr;


public slots:
    void animationDone() override;
    void setPosition(QPointF pos);
    void sceneMouseMoved(QPointF pos);
    void sceneMousePressed(QPointF pos);
    void sceneKeyPressed(int key);
    void resetPenguin();


protected:
    //bool eventFilter(QObject *watched, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PENGUINSPRITE_H
