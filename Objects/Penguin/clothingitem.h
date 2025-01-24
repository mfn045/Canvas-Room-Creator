#ifndef CLOTHINGITEM_H
#define CLOTHINGITEM_H

#include "../../canvasobject.h"

class ClothingItem : public CanvasObject
{
public:
    explicit ClothingItem(CanvasObject* parent = nullptr);
    void updateViewbox();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
};

#endif // CLOTHINGITEM_H
