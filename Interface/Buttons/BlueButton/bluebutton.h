#ifndef BLUEBUTTON_H
#define BLUEBUTTON_H

#include "../AbstractButton/abstractbutton.h"
#include <QGraphicsProxyWidget>
#include <QTextEdit>

class BlueButton : public AbstractButton
{
public:
    enum class SIZE {
        SMALL,
        MEDIUM,
        LARGE
    };
    explicit BlueButton(CanvasObject* parent = nullptr, SIZE size = SIZE::SMALL);

    void setText(QString text);

private:
    QGraphicsProxyWidget* text = nullptr;
    QTextEdit* textEdit = nullptr;
};

#endif // BLUEBUTTON_H
