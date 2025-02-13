#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "Interface/Common/TextLineEdit/textlineedit.h"
#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"

class TextInput : public MultiCanvasObject
{
public:
    explicit TextInput(MultiCanvasObject* parent = nullptr);

    TextLineEdit* getLineEdit();

private:
    TextLineEdit* lineedit = nullptr;

};

#endif // TEXTINPUT_H
