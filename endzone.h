#ifndef ENDZONE_H
#define ENDZONE_H

#include "zone.h"

class EndZone : public Zone
{
public:
    EndZone(CounterMode mode = COUNT_ONLY, Zone *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void setCounterMode(CounterMode mode);
    CounterMode counterMode();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    const QString name() const override;
    void handleCollision(Vec3& m_velocity, Vec3 &m_accl, QTime &time) override;

private:
    CounterMode m_countermode;
};

#endif // ENDZONE_H
