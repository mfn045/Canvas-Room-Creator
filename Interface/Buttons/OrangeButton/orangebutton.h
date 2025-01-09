#ifndef ORANGEBUTTON_H
#define ORANGEBUTTON_H

#include "../AbstractButton/abstractbutton.h"
#include <QGraphicsProxyWidget>
#include <QTextEdit>

class OrangeButton : public AbstractButton
{
public:
    enum class SIZE {
        SMALL,
        MEDIUM,
        LARGE
    };
    explicit OrangeButton(CanvasObject* parent = nullptr, SIZE size = SIZE::SMALL);

    void setText(QString text);

private:
    QGraphicsProxyWidget* text = nullptr;
    QTextEdit* textEdit = nullptr;
};

#endif // ORANGEBUTTON_H
