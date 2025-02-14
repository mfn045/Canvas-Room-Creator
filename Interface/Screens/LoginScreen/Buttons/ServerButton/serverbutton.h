#ifndef SERVERBUTTON_H
#define SERVERBUTTON_H

#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"
#include "Interface/Common/Containers/GridContainer/gridcontainer.h"
#include "Interface/Common/TextLabel/textlabel.h"

namespace LoginScreen {
namespace Buttons {
class ServerButton : public AbstractButton
{
public:
    explicit ServerButton(MultiCanvasObject* parent = nullptr);

};
}
}

#endif // SERVERBUTTON_H
