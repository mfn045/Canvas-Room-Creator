#ifndef MASKEDMULTICANVASOBJECT_H
#define MASKEDMULTICANVASOBJECT_H

#include "../multicanvasobject.h"

class MaskedMultiCanvasObject : public MultiCanvasObject
{
public:
    explicit MaskedMultiCanvasObject(MultiCanvasObject* parent = nullptr);

    void setMask(QString filePath);

    QRegion& getRegion();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    QRegion region;
};

#endif // MASKEDMULTICANVASOBJECT_H
