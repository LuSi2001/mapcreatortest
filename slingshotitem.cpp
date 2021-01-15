#include "slingshotitem.h"
#include "geometrylib.h"
#include "velocityengine.h"

#include <QPainter>

SlingshotItem::SlingshotItem(PolygonItem *parent) :
    PolygonItem(parent)
{
    mVertices = {
        Vec3(25, 25),
        Vec3(-25, -25),
        Vec3(-25, 25)
    };
    for(const auto& vertex : mVertices)
    {
        mEdges.push_back(geo::LineSeg(vertex, vertex));
        mExtEdges.push_back(geo::LineSeg(vertex, vertex));
    }
    geo::calcEdges(mVertices, mEdges, mExtEdges);
    geo::calcBisectrices(mVertices, mEdges, mBisectrices);
}

void SlingshotItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                             QWidget *)
{
    painter->setPen(QPen(Qt::SolidLine));
    QPolygonF polygon;
    for(unsigned long i = 0; i < mVertices.size(); i++)
    {
        polygon << v2q(mVertices[i]);
    }
    polygon << v2q(mVertices[0]);
    QPainterPath path;
    path.addPolygon(polygon);
    painter->drawPath(path);
}

QRectF SlingshotItem::boundingRect() const
{
    return {-25, -25, 50, 50};
}

const std::vector<geo::LineSeg>& SlingshotItem::edges() const
{
    return mEdges;
}

const std::vector<geo::LineSeg>& SlingshotItem::extentedEdges() const
{
    return mExtEdges;
}

const std::vector<Vec3>& SlingshotItem::vertices() const
{
    return mVertices;
}

const std::map<Vec3, Vec3>& SlingshotItem::bisectrices() const
{
    return mBisectrices;
}

QPainterPath SlingshotItem::shape() const
{
    QPolygonF polygon;
    for(unsigned long i = 0; i < mVertices.size(); i++)
    {
        polygon << v2q(mVertices[i]);
    }
    polygon << v2q(mVertices[0]);
    QPainterPath path;
    path.addPolygon(polygon);
    return path;
}

const QString SlingshotItem::name() const
{
    return "slingshot";
}

void SlingshotItem::handleCollision(Vec3 &m_velocity, Vec3 &, QTime &time)
{
    double dt = 0;
    velo::VelocityEngine::inst().preciseVelocityPolygon(time, dt, mEdges, mExtEdges,
                                                        mVertices, m_velocity);
}
