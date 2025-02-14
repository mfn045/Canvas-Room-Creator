#ifndef SERVERSELECTIONPAGE_H
#define SERVERSELECTIONPAGE_H

#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Common/TitleLabel/titlelabel.h"
#include "Interface/Screens/LoginScreen/Buttons/ServerButton/serverbutton.h"

namespace LoginScreen {
class ServerSelectionPage : public MultiCanvasObject
{
public:
    explicit ServerSelectionPage(MultiCanvasObject* parent = nullptr);
};
}

#endif // SERVERSELECTIONPAGE_H
