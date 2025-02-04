#ifndef MENUBAR_H
#define MENUBAR_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "../../widgets/scene.h"
#include "../Buttons/CircleButton/circlebutton.h"
#include "../../CanvasObject/Multi/multicanvasobject.h"
#include "../TextBox/textbox.h"
#include "../SvgGridContainer/gridcontainer.h"

class MenuBar : public MultiCanvasObject
{
    Q_OBJECT
public:
    explicit MenuBar(Scene *parent = nullptr);

    CircleButton* getSendChatButton();

    TextBox* getChatInput();

private:
    CircleButton* puffleTricks_Button = nullptr;
    CircleButton* safeChat_Button = nullptr;
    CircleButton* emoticons_Button = nullptr;
    CircleButton* penguinState_Button = nullptr;
    CircleButton* snowBall_Button = nullptr;
    CircleButton* sendChat_Button = nullptr;
    CircleButton* playerCard_Button = nullptr;
    CircleButton* friends_Button = nullptr;
    CircleButton* igloo_Button = nullptr;
    CircleButton* settings_Button = nullptr;
    MultiCanvasObject* chat = nullptr;
    TextBox* chatInput = nullptr;

    Scene* parent;

signals:
};

#endif // MENUBAR_H
