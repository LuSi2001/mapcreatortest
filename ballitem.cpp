#include "ballitem.h"
#include "velocityengine.h"
#include "readerproxy.h"

#include <QPainter>

BallItem::BallItem(CircleItem *parent) :
    CircleItem(BALL_RADIUS, parent)
{

}

void BallItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::SolidLine);
    QPainterPath path;
    path.addEllipse(boundingRect());
    painter->drawPath(path);
}

QPainterPath BallItem::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

const QString BallItem::name() const
{
    return "ball";
}

void BallItem::handleCollision(Vec3 &m_velocity, Vec3 &, QTime &time)
{
    double dt = 0;
    velo::VelocityEngine::inst().preciseVelocityCircle(time, dt, m_velocity);
}

void BallItem::readFromXML(const ReaderProxy& reader)
{
    reader.setCurPinballItem(name());
    reader.readXML("radius", m_radius);
    reader.readXML("color", m_color);
}
