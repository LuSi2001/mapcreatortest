#ifndef ZONE_H
#define ZONE_H

#include "pinballitem.h"

class Zone : public PinballItem
{
public:
    Zone(PinballItem *parent = nullptr);

    CollisionObject objectType() const override
    {
        return ZONE;
    }
};

#endif // ZONE_H
