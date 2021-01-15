#include "wallitem.h"
#include "velocityengine.h"

#include <QPainter>

WallItem::WallItem(PolygonItem *parent) :
    PolygonItem(parent)
{
    mVertices = {
        Vec3(450, 550),
        Vec3(450, -550),
        Vec3(0, -550),
        Vec3(0, -500),
        Vec3(292, -500),
        Vec3(312, -499),
        Vec3(322, -497),
        Vec3(332, -494),
        Vec3(342, -490),
        Vec3(352, -485),
        Vec3(362, -479),
        Vec3(372, -472),
        Vec3(379, -467 ),
        Vec3(385, -460),
        Vec3(390, -450),
        Vec3(394, -440),
        Vec3(397, -430),
        Vec3(399, -420),
        Vec3(400, -410),
        Vec3(400, 500),
        Vec3(350, 500),
        Vec3(350, -310),
        Vec3(340, -330),
        Vec3(325, -340),
        Vec3(310, -330),
        Vec3(300, -310),
        Vec3(300, 200),
        Vec3(75, 350),
        Vec3(75, 500),
        Vec3(-125, 500),
        Vec3(-125, 350),
        Vec3(-350, 200),
        Vec3(-350, 500),
        Vec3(-400, 500),
        Vec3(-400, -350),
        Vec3(-250, -500),
        Vec3(0, -500),
        Vec3(0, -550),
        Vec3(-450, -550),
        Vec3(-450, 550)
    };
    for(const auto& vertex : mVertices)
    {
        mEdges.push_back(geo::LineSeg(vertex, vertex));
        mExtEdges.push_back(geo::LineSeg(vertex, vertex));
    }
    geo::calcEdges(mVertices, mEdges, mExtEdges);
    geo::calcBisectrices(mVertices, mEdges, mBisectrices);
}

void WallItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
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

QRectF WallItem::boundingRect() const
{
    return {-450, -550, 900, 1100};
}

const std::vector<geo::LineSeg>& WallItem::edges() const
{
    return mEdges;
}

const std::vector<geo::LineSeg>& WallItem::extentedEdges() const
{
    return mExtEdges;
}

const std::vector<Vec3>& WallItem::vertices() const
{
    return mVertices;
}

const std::map<Vec3, Vec3>& WallItem::bisectrices() const
{
    return mBisectrices;
}

QPainterPath WallItem::shape() const
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

const QString WallItem::name() const
{
    return "wall";
}

void WallItem::handleCollision(Vec3 &m_velocity, Vec3 &, QTime &time)
{
    double dt = 0;
    velo::VelocityEngine::inst().preciseVelocityPolygon(time, dt, mEdges, mExtEdges,
                                                        mVertices, m_velocity);
}
