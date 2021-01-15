#ifndef POINTMULTIPLIERZONE_H
#define POINTMULTIPLIERZONE_H

#include "zone.h"

class PointMultiplierField : public Zone
{
public:
    PointMultiplierField(double multiplier, Zone *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    double multiplier() const;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    const QString name() const override;
    void handleCollision(Vec3& m_velocity, Vec3 &m_accl, QTime &time) override;

private:
    double m_multiplier;
};

#endif // POINTMULTIPLIERZONE_H
