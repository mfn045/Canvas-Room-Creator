#ifndef MASKEDCANVASOBJECT_H
#define MASKEDCANVASOBJECT_H

#include "../../canvasobject.h"

class MaskedCanvasObject : public CanvasObject
{
public:
    explicit MaskedCanvasObject(CanvasObject* parent = nullptr);

    void setMask(QString filePath);

    QRegion& getRegion();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    QRegion region;
};

#endif // MASKEDCANVASOBJECT_H
