#ifndef FLIPPERITEM_H
#define FLIPPERITEM_H

#include "compoundobjectitem.h"
#include "constants.h"

class FlipperItem : public CompoundObjectItem
{
public:
    FlipperItem(CompoundObjectItem *parent = nullptr);
    void setOrientation(FlipperOrientation ori = LEFT);
    void setTime(double time);
    void increaseRot();
    void decreaseRot();
    double angularSpeed() const;
    virtual const Vec3 lineDir() const = 0;

private:
    FlipperOrientation m_ori;
    double m_angularSpeed;
    double m_standardRot;
    double m_multiplier;
    double m_time;
    bool m_boolTermIncrease;
    bool m_boolTermDecrease;
    bool m_boolTermLimit;
    bool m_isIncreased;

    void setAngularSpeed();
    void setAngularSpeedNull();
};

#endif // FLIPPERITEM_H
