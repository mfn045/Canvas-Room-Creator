#ifndef INTERFACE_H
#define INTERFACE_H

#include <QFontDatabase>
#include "AbstractQtWidgets/scene.h"
#include "Interface/World/Penguin/Sprite/penguinsprite.h"
#include "Interface/Widgets/ToolBar/toolbar.h"
#include "Interface/World/Buttons/News/news.h"
#include "Interface/World/Buttons/Mail/mail.h"
#include "Interface/World/Buttons/Map/map.h"
#include "Interface/World/Buttons/Friend_Requests/friend_requests.h"
#include "Interface/Common/Containers/GridContainer/gridcontainer.h"
#include "Interface/World/ChatHistory/chathistory.h"
#include "Interface/Widgets/PlayerCard/playercard.h"
#include "Objects/Items/items.h"


class Interface
{
public:
    Scene* getScene();
    Scene* setScene(Scene* scene);

    bool loadItems();
    bool loadFonts();
    bool addToScene(AbstractCanvasObject* obj);
    bool loadHUD();
    bool loadPlayerCard();

    PlayerCard* getPlayerCard();

    Interface& operator =(const Interface&) = delete;
    Interface& operator =(Interface&&) = delete;

private:
    Interface();

    Scene* scene = nullptr;

    PlayerCard* playercard = nullptr;

    friend Interface* createInterface();
};

#endif // INTERFACE_H
