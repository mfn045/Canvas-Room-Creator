#ifndef BLUEBUTTON_H
#define BLUEBUTTON_H

#include <QGraphicsProxyWidget>
#include <QTextEdit>
#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"

class BlueButton : public AbstractButton
{
public:
    enum class SIZE {
        SMALL,
        MEDIUM,
        LARGE
    };
    explicit BlueButton(MultiCanvasObject* parent = nullptr, SIZE size = SIZE::SMALL);

    void setText(QString text);

private:
    QGraphicsProxyWidget* text = nullptr;
    QTextEdit* textEdit = nullptr;
};

#endif // BLUEBUTTON_H
