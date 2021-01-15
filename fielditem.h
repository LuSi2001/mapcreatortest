#ifndef FIELDITEM_H
#define FIELDITEM_H

#include "pinballitem.h"

class FieldItem : public PinballItem
{
public:
    FieldItem(PinballItem *parent = nullptr);

    CollisionObject objectType() const override
    {
        return TEXT_FIELD;
    }
};

#endif // FIELDITEM_H
