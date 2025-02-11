#ifndef CATEGORYBUTTON_H
#define CATEGORYBUTTON_H

#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Widgets/Buttons/OvalButton/ovalbutton.h"

class CategoryButton : public MultiCanvasObject
{
public:
    explicit CategoryButton(MultiCanvasObject* parent = nullptr);
    OvalButton* getButton();

private:
    OvalButton* button = nullptr;
};

#endif // CATEGORYBUTTON_H
