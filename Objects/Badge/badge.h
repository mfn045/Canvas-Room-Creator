#ifndef BADGE_H
#define BADGE_H

#include "../../CanvasObject/Multi/multicanvasobject.h"
#include "../../CanvasObject/Multi/Masked/maskedmulticanvasobject.h"
#include "../Constants/constants.h"

class Badge : public MultiCanvasObject
{
public:
    explicit Badge(MultiCanvasObject* parent = nullptr, PENGUIN::BADGE badgeType = PENGUIN::BADGE::NONE);

    void setBadge(PENGUIN::BADGE badgeType);
};

#endif // BADGE_H
