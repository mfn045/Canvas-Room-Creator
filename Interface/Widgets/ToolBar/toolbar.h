#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "AbstractQtWidgets/scene.h"
#include "Interface/Widgets/Buttons/CircleButton/circlebutton.h"
#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Common/TextBox/textbox.h"
#include "Interface/Common/Containers/GridContainer/gridcontainer.h"

class ToolBar : public MultiCanvasObject
{
    Q_OBJECT
public:
    explicit ToolBar(Scene *parent = nullptr);

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

#endif // TOOLBAR_H
