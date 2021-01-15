#ifndef BUMPERITEM_H
#define BUMPERITEM_H


#include "circleitem.h"

class BumperItem : public CircleItem
{
public:
    BumperItem(CircleItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    QPainterPath shape() const override;
    const QString name() const override;
    void handleCollision(Vec3& m_velocity, Vec3 &, QTime &time) override;
};

#endif // BUMPERITEM_H
