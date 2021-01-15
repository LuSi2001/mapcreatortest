#include "flipperleftitem.h"
#include "velocityengine.h"

#include <QPainter>

FlipperLeftItem::FlipperLeftItem(FlipperItem *parent) :
    FlipperItem(parent)
{
    mVertices = {
        Vec3(90, 10),
        Vec3(90, -10),
        Vec3(0, -15),
        Vec3(0, 15)
    };
    mCircles = {
        geo::Circle(Vec3(90, 0), 10),
        geo::Circle(Vec3(0, 0), 15)
    };
    mEdges = {
        geo::LineSeg(mVertices[1], mVertices[2]),
        geo::LineSeg(mVertices[3], mVertices[0])
    };
    mExtendedEdges = {
        geo::LineSeg(mEdges[0].p1 + mEdges[0].dir().normalized().perp2D() * BALL_RADIUS,
        mEdges[0].p0 + mEdges[0].dir().normalized().perp2D() * BALL_RADIUS),
        geo::LineSeg(mEdges[1].p1 + mEdges[1].dir().normalized().perp2D() * BALL_RADIUS,
        mEdges[1].p0 + mEdges[1].dir().normalized().perp2D() * BALL_RADIUS)
    };

    setOrientation(RIGHT);
}

void FlipperLeftItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                             QWidget *)
{
    painter->setPen(QPen(Qt::SolidLine));
    QPolygonF polygon;
    for(Vec3 vertex : mVertices)
    {
        polygon << v2q(vertex);
    }
    polygon << v2q(mVertices[0]);
    QPainterPath path;
    path.addEllipse(QRectF(80, -10, 20, 20));
    path.addPolygon(polygon);
    path.addEllipse(QRectF(-15, -15, 30, 30));
    painter->drawPath(path);
}

QRectF FlipperLeftItem::boundingRect() const
{
    return {-100, -15, 200, 30};
}

const std::vector<geo::Circle> &FlipperLeftItem::circles() const
{
    return mCircles;
}

const std::vector<geo::LineSeg> &FlipperLeftItem::edges() const
{
    return mEdges;
}

const std::vector<geo::LineSeg> &FlipperLeftItem::extentedEdges() const
{
    return mExtendedEdges;
}

const std::vector<Vec3>& FlipperLeftItem::vertices() const
{
    return mVertices;
}

QPainterPath FlipperLeftItem::shape() const
{
    QPolygonF polygon;
    for(Vec3 vertex : mVertices)
    {
        polygon << v2q(vertex);
    }
    polygon << v2q(mVertices[0]);
    QPainterPath path;
    path.addEllipse(QRectF(80, -10, 20, 20));
    path.addPolygon(polygon);
    path.addEllipse(QRectF(-15, -15, 30, 30));
    return path;
}

const QString FlipperLeftItem::name() const
{
    return "flipperLeft";
}

const Vec3 FlipperLeftItem::lineDir() const
{
    return Vec3(0, 0) + Vec3(90, 0);
}

void FlipperLeftItem::handleCollision(Vec3 &m_velocity, Vec3 &, QTime &time)
{
    double dt = 0;
    velo::VelocityEngine::inst().preciseVelocityCompound(time, dt, m_velocity);
    if(angularSpeed() != 0.0)
    {
        m_velocity = m_velocity - lineDir().normalized().perp2D() *
                      (angularSpeed() * 1000) / 1.5;
        decreaseRot();
    }
}
