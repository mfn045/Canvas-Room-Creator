#ifndef INTERFACE_H
#define INTERFACE_H
#include "../widgets/scene.h"
#include <QFontDatabase>
#include "../Objects/Penguin/penguin.h"
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
    static Interface* getInstance();
    Scene* getScene();
    Scene* setScene(Scene* scene);

    bool loadItems();
    bool loadFonts();
    bool loadPenguin();
    bool loadHUD();
    bool loadPlayerCard();

    PlayerCard* getPlayerCard();

private:
    Interface() = default;
    static Interface* instance;
    Scene* scene = nullptr;
    PlayerCard* playercard = nullptr;

    Penguin* activePenguin = nullptr;
    QList<Penguin*> penguins;
};

#endif // INTERFACE_H
