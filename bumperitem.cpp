#include "bumperitem.h"
#include "velocityengine.h"

#include <QPainter>

BumperItem::BumperItem(CircleItem *parent) :
    CircleItem (50.0, parent)
{

}

void BumperItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::SolidLine);
    QPainterPath path;
    path.addEllipse(boundingRect());
    painter->drawPath(path);
}

QPainterPath BumperItem::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

const QString BumperItem::name() const
{
    return "bumper";
}

void BumperItem::handleCollision(Vec3 &m_velocity, Vec3 &, QTime &time)
{
    double dt = 0;
    velo::VelocityEngine::inst().preciseVelocityCircle(time, dt, m_velocity);
}
