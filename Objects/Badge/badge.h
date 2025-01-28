#ifndef BADGE_H
#define BADGE_H

#include "../../canvasobject.h"
#include "../MaskedCanvasObject/maskedcanvasobject.h"
#include "../Constants/constants.h"

class Badge : public CanvasObject
{
public:
    explicit Badge(CanvasObject* parent = nullptr, PENGUIN::BADGE badgeType = PENGUIN::BADGE::NONE);

    void setBadge(PENGUIN::BADGE badgeType);
};

#endif // BADGE_H
