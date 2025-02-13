#ifndef CHECKBOXBUTTON_H
#define CHECKBOXBUTTON_H

#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"

class CheckBoxButton : public AbstractButton
{
public:
    explicit CheckBoxButton(MultiCanvasObject* parent = nullptr);

    MultiCanvasObject* setIcon(QString filePath) override;

private slots:
    void toggledOn();
    void toggledOff();
};

#endif // CHECKBOXBUTTON_H
