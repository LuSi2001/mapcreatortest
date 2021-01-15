#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H


#include "pinballitem.h"

class CircleItem : public PinballItem
{
public:
    CircleItem(double radius, PinballItem *parent = nullptr);
    void setRadius(double radius) { mRadius = radius; }

    CollisionObject objectType() const override { return CIRCLE2D; }
    double radius() const { return mRadius; }
    QRectF boundingRect() const override
    {
        return {-mRadius, -mRadius, 2 * mRadius, 2 * mRadius};
    }

private:
    double mRadius = 1.0;
};

#endif // CIRCLEITEM_H
