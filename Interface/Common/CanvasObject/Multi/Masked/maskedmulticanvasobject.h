#ifndef MASKEDMULTICANVASOBJECT_H
#define MASKEDMULTICANVASOBJECT_H

#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"

class MaskedMultiCanvasObject : public MultiCanvasObject
{
public:
    explicit MaskedMultiCanvasObject(MultiCanvasObject* parent = nullptr);

    void setMask(QString filePath);
    void setMask(QRegion region);

    QRegion& getRegion();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    QRegion region;
};

#endif // MASKEDMULTICANVASOBJECT_H
