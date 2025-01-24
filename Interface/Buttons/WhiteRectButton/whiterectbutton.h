#ifndef WHITERECTBUTTON_H
#define WHITERECTBUTTON_H

#include "../AbstractButton/abstractbutton.h"
#include "../../TextLabel/textlabel.h"

class WhiteRectButton : public AbstractButton
{
public:
    enum class SIZE {
        SMALL,
        MEDIUM
    };
    enum class TYPE {
        WITHOUT_ARROW,
        WITH_ARROW
    };

    explicit WhiteRectButton(CanvasObject *parent = nullptr, SIZE size = SIZE::SMALL, TYPE type = TYPE::WITHOUT_ARROW);
    CanvasObject* setIcon(QString filePath) override;
    void setText(QString text);

private:
    TextLabel* label = nullptr;
    SIZE size = SIZE::SMALL;
    TYPE type = TYPE::WITHOUT_ARROW;
};

#endif // WHITERECTBUTTON_H
