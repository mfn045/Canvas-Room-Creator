#ifndef CATEGORYBUTTON_H
#define CATEGORYBUTTON_H

#include "../../../../canvasobject.h"
#include "../../OvalButton/ovalbutton.h"

class CategoryButton : public CanvasObject
{
public:
    explicit CategoryButton(CanvasObject* parent = nullptr);
    OvalButton* getButton();

private:
    OvalButton* button = nullptr;
};

#endif // CATEGORYBUTTON_H
