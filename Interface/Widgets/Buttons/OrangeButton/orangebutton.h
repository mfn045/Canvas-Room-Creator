#ifndef ORANGEBUTTON_H
#define ORANGEBUTTON_H

#include <QGraphicsProxyWidget>
#include <QTextEdit>
#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"

class OrangeButton : public AbstractButton
{
public:
    enum class SIZE {
        SMALL,
        MEDIUM,
        LARGE
    };
    explicit OrangeButton(MultiCanvasObject* parent = nullptr, SIZE size = SIZE::SMALL);

    void setText(QString text);

private:
    QGraphicsProxyWidget* text = nullptr;
    QTextEdit* textEdit = nullptr;
};

#endif // ORANGEBUTTON_H
