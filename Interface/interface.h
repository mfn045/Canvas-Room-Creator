#ifndef INTERFACE_H
#define INTERFACE_H
#include "../widgets/scene.h"
#include <QFontDatabase>
#include "../Objects/Penguin/Sprite/penguinsprite.h"
#include "MenuBar/menubar.h"
#include "News/news.h"
#include "Mail/mail.h"
#include "Map/map.h"
#include "Friend_Requests/friend_requests.h"
#include "SvgGridContainer/gridcontainer.h"
#include "ChatHistory/chathistory.h"
#include "PlayerCard/playercard.h"
#include "../Objects/Items/items.h"


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
