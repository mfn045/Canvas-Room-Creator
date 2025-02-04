#ifndef CATEGORYBUTTON_H
#define CATEGORYBUTTON_H

#include "../../../../CanvasObject/Multi/multicanvasobject.h"
#include "../../OvalButton/ovalbutton.h"

class CategoryButton : public MultiCanvasObject
{
public:
    explicit CategoryButton(MultiCanvasObject* parent = nullptr);
    OvalButton* getButton();

private:
    OvalButton* button = nullptr;
};

#endif // CATEGORYBUTTON_H
