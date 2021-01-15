#ifndef BALLCOUNTERFIELD_H
#define BALLCOUNTERFIELD_H

#include "fielditem.h"

class BallCounterField : public FieldItem
{
public:
    BallCounterField(int startCount = 1, FieldItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void setCount(int count);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    const QString name() const override;
    void handleCollision(Vec3& m_velocity, Vec3 &m_accl, QTime &time) override;

private:
    int m_count;
};

#endif // BALLCOUNTERFIELD_H
