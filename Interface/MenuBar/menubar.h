#ifndef MENUBAR_H
#define MENUBAR_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "../../widgets/scene.h"
#include "../Buttons/BlueCircleButton/bluecirclebutton.h"
#include "../../canvasobject.h"
#include "../TextBox/textbox.h"
#include "../SvgGridContainer/gridcontainer.h"

class MenuBar : public CanvasObject
{
    Q_OBJECT
public:
    explicit MenuBar(Scene *parent = nullptr);

    BlueCircleButton* getSendChatButton();

    TextBox* getChatInput();

private:
    BlueCircleButton* puffleTricks_Button = nullptr;
    BlueCircleButton* safeChat_Button = nullptr;
    BlueCircleButton* emoticons_Button = nullptr;
    BlueCircleButton* penguinState_Button = nullptr;
    BlueCircleButton* snowBall_Button = nullptr;
    BlueCircleButton* sendChat_Button = nullptr;
    BlueCircleButton* playerCard_Button = nullptr;
    BlueCircleButton* friends_Button = nullptr;
    BlueCircleButton* igloo_Button = nullptr;
    BlueCircleButton* settings_Button = nullptr;
    CanvasObject* chat = nullptr;
    TextBox* chatInput = nullptr;

    Scene* parent;

signals:
};

#endif // MENUBAR_H
