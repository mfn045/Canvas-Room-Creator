#ifndef SETTINGS_H
#define SETTINGS_H

#include "Interface/Widgets/BackgroundContainer/backgroundcontainer.h"
#include "Interface/Common/TextLabel/textlabel.h"
#include "Interface/Common/TitleLabel/titlelabel.h"
#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Common/Containers/GridContainer/gridcontainer.h"

class Settings : public MultiCanvasObject
{
public:
    explicit Settings(MultiCanvasObject* parent = nullptr);
};

#endif // SETTINGS_H
