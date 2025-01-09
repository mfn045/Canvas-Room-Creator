#ifndef WHITESQUAREBUTTON_H
#define WHITESQUAREBUTTON_H

#include "../AbstractButton/abstractbutton.h"

class WhiteSquareButton : public AbstractButton
{
public:
    enum class SIZE {
        SMALL,
        MEDIUM
    };
    explicit WhiteSquareButton(CanvasObject *parent = nullptr, SIZE size = SIZE::SMALL);
    void setIcon(QString filePath) override;

private:
    SIZE size = SIZE::SMALL;
};

#endif // BLUECIRCLEBUTTON_H
