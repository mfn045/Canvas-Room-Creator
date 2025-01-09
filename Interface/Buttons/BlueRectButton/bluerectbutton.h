#ifndef BLUERECTBUTTON_H
#define BLUERECTBUTTON_H

#include "../AbstractButton/abstractbutton.h"

class BlueRectButton : public AbstractButton
{
    Q_OBJECT
public:
    explicit BlueRectButton(CanvasObject *parent = nullptr);

    void setIcon(QString filePath) override;
};

#endif // BLUERECTBUTTON_H
