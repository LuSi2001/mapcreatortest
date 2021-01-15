#include "autoplungeritem.h"
#include "geometrylib.h"
#include "velocityengine.h"
#include "readerproxy.h"

#include <QPainter>

AutoPlungerItem::AutoPlungerItem(PolygonItem *parent) :
    PolygonItem(parent)
{
    m_vertices = {
        Vec3(5, 25),
        Vec3(5, -20),
        Vec3(25, -20),
        Vec3(25, -25),
        Vec3(-25, -25),
        Vec3(-25, -20),
        Vec3(-5, -20),
        Vec3(-5, 25)
    };

    for(const auto& vertex : m_vertices)
    {
        m_edges.push_back(geo::LineSeg(vertex, vertex));
        m_extEdges.push_back(geo::LineSeg(vertex, vertex));
    }
    geo::calcEdges(m_vertices, m_edges, m_extEdges);
    geo::calcBisectrices(m_vertices, m_edges, m_bisectrices);
}

void AutoPlungerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                             QWidget *)
{
    painter->setPen(QPen(Qt::SolidLine));
    QPolygonF polygon;
    for(unsigned long i = 0; i < m_vertices.size(); i++)
    {
        polygon << v2q(m_vertices[i]);
    }
    polygon << v2q(m_vertices[0]);
    QPainterPath path;
    path.addPolygon(polygon);
    painter->drawPath(path);
}

QRectF AutoPlungerItem::boundingRect() const
{
    return {-25, -25, 50, 50};
}

const std::vector<geo::LineSeg>& AutoPlungerItem::edges() const
{
    return m_edges;
}

const std::vector<geo::LineSeg>& AutoPlungerItem::extentedEdges() const
{
    return m_extEdges;
}

const std::vector<Vec3>& AutoPlungerItem::vertices() const
{
    return m_vertices;
}

const std::map<Vec3, Vec3>& AutoPlungerItem::bisectrices() const
{
    return m_bisectrices;
}

QPainterPath AutoPlungerItem::shape() const
{
    QPolygonF polygon;
    for(unsigned long i = 0; i < m_vertices.size(); i++)
    {
        polygon << v2q(m_vertices[i]);
    }
    polygon << v2q(m_vertices[0]);
    QPainterPath path;
    path.addPolygon(polygon);
    return path;
}

const QString AutoPlungerItem::name() const
{
    return "autoPlunger";
}

void AutoPlungerItem::handleCollision(Vec3 &m_velocity, Vec3&, QTime& time)
{
    double dt = 0;
    velo::VelocityEngine::inst().preciseVelocityPolygon(time, dt, m_edges, m_extEdges,
                                                        m_vertices, m_velocity);
}

void AutoPlungerItem::readFromXML(const ReaderProxy &reader)
{
    reader.setCurPinballItem(name());
}
