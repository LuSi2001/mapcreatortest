#include "flipperitem.h"
#include "constants.h"
#include "physicformulas.h"

FlipperItem::FlipperItem(CompoundObjectItem *parent) :
    CompoundObjectItem(parent),
    m_standardRot(0.0),
    m_multiplier(1.0),
    m_isIncreased(false)
{
    m_boolTermIncrease = (m_standardRot < FLIPPER_ROT_BORDER);
    m_boolTermDecrease = (m_standardRot > 0);
    m_boolTermLimit = (m_standardRot >= FLIPPER_ROT_BORDER or m_standardRot <= 0.0);
}

void FlipperItem::setAngularSpeed()
{
    if(m_isIncreased)
    {
        m_angularSpeed = formula::angularSpeed(m_standardRot * m_multiplier, m_time);
    }
    m_angularSpeed = formula::angularSpeed(FLIPPER_ROT_BORDER - m_standardRot * m_multiplier, m_time);
}

void FlipperItem::setAngularSpeedNull()
{
    m_angularSpeed = formula::angularSpeed(0, 0);
}

void FlipperItem::setOrientation(FlipperOrientation ori)
{
    m_ori = ori;
    if(ori == LEFT)
    {
        m_multiplier = 1.0;
        m_boolTermIncrease = (m_standardRot < FLIPPER_ROT_BORDER);
        m_boolTermDecrease = (m_standardRot > 0.0);
        m_boolTermLimit = (m_standardRot >= FLIPPER_ROT_BORDER or m_standardRot <= 0.0);
        m_isIncreased = true;
        return;
    }
    m_multiplier = -1.0;
    m_boolTermIncrease = (m_standardRot > -FLIPPER_ROT_BORDER);
    m_boolTermDecrease = (m_standardRot < 0.0);
    m_boolTermLimit = (m_standardRot <= -FLIPPER_ROT_BORDER or m_standardRot >= 0.0);
    m_isIncreased = false;
}

void FlipperItem::setTime(double time)
{
    m_time = time;
}

void FlipperItem::increaseRot()
{
    setOrientation(m_ori);
    if(m_boolTermIncrease)
    {
        m_standardRot += FLIPPER_ROT * m_multiplier;
        setRotation(rotation() + FLIPPER_ROT * m_multiplier);
        setAngularSpeed();
    }
    if(m_boolTermLimit)
    {
        setAngularSpeedNull();
    }
}

void FlipperItem::decreaseRot()
{
    setOrientation(m_ori);
    if(m_boolTermDecrease)
    {
        m_standardRot -= FLIPPER_ROT * m_multiplier;
        setRotation(rotation() - FLIPPER_ROT * m_multiplier);
        setAngularSpeed();
    }
    if(m_boolTermLimit)
    {
        setAngularSpeedNull();
    }
}

double FlipperItem::angularSpeed() const
{
    return m_angularSpeed;
}
