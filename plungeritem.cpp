#include "plungeritem.h"
#include "geometrylib.h"
#include "velocityengine.h"

#include <QPainter>

PlungerItem::PlungerItem(PolygonItem *parent) :
    PolygonItem(parent),
    m_plungerPullBack(0.0)
{
    mVertices = {
        Vec3(5, 25),
        Vec3(5, -20),
        Vec3(25, -20),
        Vec3(25, -25),
        Vec3(-25, -25),
        Vec3(-25, -20),
        Vec3(-5, -20),
        Vec3(-5, 25)
    };
    for(const auto& vertex : mVertices)
    {
        mEdges.push_back(geo::LineSeg(vertex, vertex));
        mExtEdges.push_back(geo::LineSeg(vertex, vertex));
    }
    geo::calcEdges(mVertices, mEdges, mExtEdges);
    geo::calcBisectrices(mVertices, mEdges, mBisectrices);
    setBools();
}

void PlungerItem::setLaunchSpeed(double launchSpeed)
{
    m_launchSpeed = launchSpeed;
}

void PlungerItem::setBools()
{
    m_plungerPullLimit = (m_plungerPullBack < PLUNGER_PULL_LIMIT);
    m_plungerPushLimit = (m_plungerPullBack > 0.0);
    m_plungerLimits = (m_plungerPullBack < PLUNGER_PULL_LIMIT and
                       m_plungerPullBack > 0.0);
}

void PlungerItem::pull()
{
    setBools();
    if(m_plungerPullLimit)
    {
        setPos(pos().x(), pos().y() + PLUNGER_PULL_BACK);
        m_plungerPullBack += PLUNGER_PULL_BACK;
    }
    setLaunchSpeed(0.0);
}

void PlungerItem::push()
{
    setBools();
    if(m_plungerPushLimit)
    {
        setPos(pos().x(), pos().y() - PLUNGER_LAUNCH);
        m_plungerPullBack -= PLUNGER_LAUNCH;
        setLaunchSpeed(PLUNGER_LAUNCH * (m_plungerPullBack / PLUNGER_PULL_LIMIT * 10));
        return;
    }
    if(not m_plungerLimits)
    {
        setLaunchSpeed(0.0);
    }
}

void PlungerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
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

QRectF PlungerItem::boundingRect() const
{
    return {-25, -25, 50, 50};
}

const std::vector<geo::LineSeg>& PlungerItem::edges() const
{
    return mEdges;
}

const std::vector<geo::LineSeg>& PlungerItem::extentedEdges() const
{
    return mExtEdges;
}

const std::vector<Vec3>& PlungerItem::vertices() const
{
    return mVertices;
}

const std::map<Vec3, Vec3>& PlungerItem::bisectrices() const
{
    return mBisectrices;
}

QPainterPath PlungerItem::shape() const
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

const QString PlungerItem::name() const
{
    return "plunger";
}

double PlungerItem::launchSpeed() const
{
    return m_launchSpeed;
}

Vec3 PlungerItem::lineDir()
{
    return Vec3(-25, -25) - Vec3(25, -25);
}

void PlungerItem::handleCollision(Vec3 &m_velocity, Vec3 &, QTime &time)
{
    double dt = 0;
    velo::VelocityEngine::inst().preciseVelocityPolygon(time, dt, mEdges, mExtEdges,
                                                        mVertices, m_velocity);
    if(launchSpeed() != 0.0)
    {
        m_velocity = m_velocity + lineDir().normalized().perp2D() *
                     launchSpeed();
        for(int i = 0; i < 6; i++)
        {
            pull();
        }
    }
}
