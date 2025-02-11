#ifndef BLUERECTBUTTON_H
#define BLUERECTBUTTON_H

#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"

class BlueRectButton : public AbstractButton
{
    Q_OBJECT
public:
    explicit BlueRectButton(MultiCanvasObject *parent = nullptr);

    MultiCanvasObject* setIcon(QString filePath) override;
};

#endif // BLUERECTBUTTON_H
