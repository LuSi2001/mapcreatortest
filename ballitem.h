#ifndef BALLITEM_H
#define BALLITEM_H


#include "circleitem.h"

class BallItem : public CircleItem
{
public:
    BallItem(CircleItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    QPainterPath shape() const override;
    const QString name() const override;
    void handleCollision(Vec3& m_velocity, Vec3 &, QTime &time) override;
};

#endif // BALLITEM_H
