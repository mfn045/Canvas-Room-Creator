#ifndef BADGE_H
#define BADGE_H

#include "../../CanvasObject/Multi/multicanvasobject.h"
#include "../../CanvasObject/Multi/Masked/maskedmulticanvasobject.h"
#include "../Constants/constants.h"

class Badge : public MultiCanvasObject
{
public:
    explicit Badge(MultiCanvasObject* parent = nullptr, PENGUIN::BADGE badgeType = PENGUIN::BADGE::NONE);
    ~Badge();

    void setBadge(PENGUIN::BADGE badgeType);

    void clearBadge();

private:
    MaskedMultiCanvasObject* flashy = nullptr;
    MultiCanvasObject* star = nullptr;
    MultiCanvasObject* ribbon_front = nullptr;
    MultiCanvasObject* ribbon_back = nullptr;
    MultiCanvasObject* chevron = nullptr;

    PROPERTIES* backgroundProperties = nullptr;
};

#endif // BADGE_H
