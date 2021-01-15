#include "flipperrightitem.h"
#include "velocityengine.h"

#include <QPainter>

FlipperRightItem::FlipperRightItem(FlipperItem *parent) :
    FlipperItem(parent)
{
    mVertices = {
        Vec3(0, 15),
        Vec3(0, -15),
        Vec3(-90, -10),
        Vec3(-90, 10)
    };
    mCircles = {
        geo::Circle(Vec3(-90, 0), 10),
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

    setOrientation(LEFT);
}

void FlipperRightItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
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
    path.addEllipse(QRectF(-100, -10, 20, 20));
    path.addPolygon(polygon);
    path.addEllipse(QRectF(-15, -15, 30, 30));
    painter->drawPath(path);
}

QRectF FlipperRightItem::boundingRect() const
{
    return {-100, -15, 200, 30};
}

const std::vector<geo::Circle> &FlipperRightItem::circles() const
{
    return mCircles;
}

const std::vector<geo::LineSeg> &FlipperRightItem::edges() const
{
    return mEdges;
}

const std::vector<geo::LineSeg> &FlipperRightItem::extentedEdges() const
{
    return mExtendedEdges;
}

const std::vector<Vec3>& FlipperRightItem::vertices() const
{
    return mVertices;
}

QPainterPath FlipperRightItem::shape() const
{
    QPolygonF polygon;
    for(Vec3 vertex : mVertices)
    {
        polygon << v2q(vertex);
    }
    polygon << v2q(mVertices[0]);
    QPainterPath path;
    path.addEllipse(QRectF(-100, -10, 20, 20));
    path.addPolygon(polygon);
    path.addEllipse(QRectF(-15, -15, 30, 30));
    return path;
}

const QString FlipperRightItem::name() const
{
    return "flipperRight";
}

const Vec3 FlipperRightItem::lineDir() const
{
    return Vec3() - Vec3(-90, 0);
}

void FlipperRightItem::handleCollision(Vec3 &m_velocity, Vec3 &, QTime &time)
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
