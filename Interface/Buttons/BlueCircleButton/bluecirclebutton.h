#ifndef BLUECIRCLEBUTTON_H
#define BLUECIRCLEBUTTON_H

#include "../AbstractButton/abstractbutton.h"

class BlueCircleButton : public AbstractButton
{
public:
    explicit BlueCircleButton(CanvasObject *parent = nullptr);
    void setIcon(QString filePath) override;
};

#endif // BLUECIRCLEBUTTON_H
