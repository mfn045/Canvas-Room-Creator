#ifndef PENGUIN_H
#define PENGUIN_H
#include <QDomDocument>
#include <QDomElement>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QThread>
#include <QObject>
#include "../../canvasobject.h"
#include "../../widgets/scene.h"
#include "clothes.h"
#include "../../Interface/ChatBubble/chatbubble.h"

class Penguin : public CanvasObject
{
    Q_OBJECT
public:
    enum DIRECTION {
        S,
        SW,
        W,
        NW,
        N,
        NE,
        E,
        SE,
    };

    enum STATE {
        STANDING,
        SITTING,
        WALKING,
        DANCING,
        WAVING
    };

    enum BADGE {
        NONE,
        PLAYER,
        MEMBER_0,
        MEMBER_1,
        MEMBER_2,
        MEMBER_3,
        MEMBER_4
    };

    struct PENGUINPROPERTIES : public PROPERTIES {
        STATE state = STATE::STANDING;
        DIRECTION direction = DIRECTION::S;
    };

    Penguin(Scene* parent = nullptr);

    void sendChatBubble(QString msg);

    void walkTo(QPointF pos);

    void changeColor(QString color);

    DIRECTION getCurrentDirection();
    void setCurrentDirection(DIRECTION direction);
    STATE getCurrentState();
    void setCurrentState(STATE state);

    double getVelocity();
    double setVelocity(double velocity);

    void initializeFrames(QString filePath, DIRECTION direction, STATE state);
    void setCurrentFrames(DIRECTION direction, STATE state);

    STATE getStateFromString(QString string);

private:
    QThread* thread = nullptr;

    double velocity = 0;

    DIRECTION currentDirection = DIRECTION::S;
    STATE currentState = STATE::STANDING;

    Scene* parent = nullptr;

    BADGE memberType = BADGE::PLAYER;

    ChatBubble* bubble = nullptr;

    Clothes clothes;

    bool active = false;

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

#endif // PENGUIN_H
