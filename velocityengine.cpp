#include "velocityengine.h"
#include "collisionengine.h"
#include "pinballitem.h"
#include "compoundobjectitem.h"
#include "polygonitem.h"

#include <QPoint>
#include <QTime>

namespace velo
{

VelocityEngine& VelocityEngine::inst()
{
    static VelocityEngine obj;
    return obj;
}

void VelocityEngine::setBall(PinballItem *ball)
{
    m_ball = ball;
}

void VelocityEngine::setAccl(const Vec3& accl)
{
    m_accl = accl;
}

PinballItem* VelocityEngine::ball()
{
    return m_ball;
}

void VelocityEngine::setCollisionItem(PinballItem *colItem)
{
    m_collisionItem = colItem;
}

void VelocityEngine::preciseVelocityCircle(QTime &time, double &t, Vec3& m_velocity)
{
    QPointF curPoint = m_ball->pos();

    qreal   dt = qreal(time.elapsed()) * 0.001;
    Vec3    oldVel = m_velocity;
    QPointF oldPos = m_ball->pos();
    m_velocity = m_velocity + dt * m_accl;
    m_ball->setPos(m_ball->pos() + v2q((oldVel + m_velocity) * 0.5 * dt * 100.0));

    QPointF nextPoint = m_ball->pos();

    m_velocity = oldVel;
    m_ball->setPos(oldPos);


    geo::LineSeg ls(q2v(curPoint), q2v(nextPoint));
    Vec3 ip[2] = {Vec3(), Vec3()};
    double  tt[2];

    if(geo::hasLinesegCircleIntersection(ls, q2v(m_collisionItem->pos()),
                                         m_collisionItem->boundingRect().width()/2 + BALL_RADIUS,
                                         ip, tt))
    {
        Vec3 intersectionPoint2;
        if(tt[0] > tt[1])
        {
            intersectionPoint2 = ip[1];
        } else {
            intersectionPoint2 = ip[0];
        }

        // ds = 1/2 * a * t² + v0 * t + s0; -> s0 fällt weg, da nicht vorhanden
        // 0 = 1/2 * a * t² + v0 * t - ds | * 2
        // 0 = a * t² + 2* v0 * t - 2 * ds | a
        // 0 = t² + (2 * v0 * t) / a - (2 * ds) / a
        // 0 = ((-2 * v0) / a) / 2 + sqrt(((2 * v0 / a) / 2)² + (2 * ds) / a)
        // 0 = ((-2 * v0) / a) / 2 - sqrt(((2 * v0 / a) / 2)² + (2 * ds) / a)

        double t1 = ((-2 * m_velocity.length()) / m_accl.length()) / 2 +
                    sqrt(geo::sqr((2 * m_velocity.length() / m_accl.length()) / 2) +
                         (2 * ls.dir().length()) / m_accl.length());
        //double t2 = ((-m_velocity.length()) / a) - sqrt(sqr(m_velocity.length() / a) +
        //(2 * d.length()) / a);

        t1 *= 0.001;
        t = dt - t1;

        m_velocity = m_velocity + t1 * m_accl;
        m_ball->setPos(v2q(intersectionPoint2));

        col::CircleOp(m_ball, m_velocity, dt, q2v(m_collisionItem->pos()));
    }
}

void VelocityEngine::preciseVelocityCompound(QTime &time, double &t, Vec3& m_velocity)
{
    QPointF curPoint = m_ball->pos();

    qreal   dt = qreal(time.elapsed()) * 0.001;
    Vec3    oldVel = m_velocity;
    QPointF oldPos = m_ball->pos();
    m_velocity = m_velocity + dt * m_accl;
    m_ball->setPos(m_ball->pos() + v2q((oldVel + m_velocity) * 0.5 * dt * 100.0));

    QPointF nextPoint = m_ball->pos();

    m_velocity = oldVel;
    m_ball->setPos(oldPos);

    int intersectionCounter = 0;
    Vec3 nearestP = Vec3();

    CompoundObjectItem* compoundItem = static_cast<CompoundObjectItem*>(m_collisionItem);

    geo::Circle c(Vec3(), 0);
    geo::LineSeg ls(Vec3(0, 0, 0), Vec3(0, 0, 0));
    geo::LineSeg ls1(q2v(curPoint), q2v(nextPoint));
    std::vector<geo::Circle> circleList = compoundItem->circles();
    std::vector<geo::LineSeg> extEdgeList = compoundItem->extentedEdges();
    geo::rotateEdges(extEdgeList, m_collisionItem->rotation());
    geo::rotatePoints(circleList, m_collisionItem->rotation());
    geo::setOffset(extEdgeList, q2v(m_collisionItem->pos()));
    geo::setOffset(circleList, q2v(m_collisionItem->pos()));


    for(const auto &circle : circleList)
    {
        Vec3 ip[2] = {Vec3(), Vec3()};
        double  t[2];
        if(geo::hasLinesegCircleIntersection(ls1, circle.mp, circle.r + BALL_RADIUS, ip, t))
        {
            if(intersectionCounter == 0)
            {
                nearestP = ip[1];
                intersectionCounter++;
                c = circle;
                m_curCollisionType = CIRCLE;
                continue;
            }
            nearestP = geo::nearestPoint(q2v(m_ball->pos()), nearestP, ip[1]);
            if(nearestP == ip[1])
            {
                c = circle;
                m_curCollisionType = CIRCLE;
            }
        }
    }
    for(const auto &edge : extEdgeList)
    {
        Vec3 ip[2] = {Vec3(), Vec3()};
        if(geo::hasLinesegLinesegIntersection(ls1, edge, ip[0]))
        {
            if(intersectionCounter == 0)
            {
                nearestP = ip[0];
                intersectionCounter++;
                m_curCollisionType = LINE;
                ls = edge;
                continue;
            }
            nearestP = geo::nearestPoint(q2v(m_ball->pos()), nearestP, ip[0]);
            if(nearestP == ip[0])
            {
                m_curCollisionType = LINE;
                ls = edge;
            }
        }
    }
    if(m_curCollisionType == LINE)
    {
        calcRestVelocity(nearestP, curPoint, nextPoint, dt, t, ls, m_velocity, std::vector<Vec3>());
        return;
    }

    Vec3 ip[2] = {Vec3(), Vec3()};
    double  tt[2];

    if(geo::hasLinesegCircleIntersection(ls1, c.mp, c.r + BALL_RADIUS, ip, tt))
    {
        Vec3 intersectionPoint2;
        if(tt[0] > tt[1])
        {
            intersectionPoint2 = ip[1];
        } else {
            intersectionPoint2 = ip[0];
        }

        double t1 = ((-2 * m_velocity.length()) / m_accl.length()) / 2 +
                    sqrt(geo::sqr((2 * m_velocity.length() / m_accl.length()) / 2) +
                         (2 * ls1.dir().length()) / m_accl.length());

        t1 *= 0.001;
        t = dt - t1;

        m_velocity = m_velocity + t1 * m_accl;
        m_ball->setPos(v2q(intersectionPoint2));
        col::CircleOp(m_ball, m_velocity, dt, c.mp);
    }
}

double VelocityEngine::preciseVelocityPolygon(QTime &time, double &t,
                                              std::vector<geo::LineSeg> &edges,
                                              std::vector<geo::LineSeg> &extEdges,
                                              std::vector<Vec3> &polygonVertices,
                                              Vec3& m_velocity)
{
    std::vector<geo::LineSeg> m_edges = edges;
    std::vector<geo::LineSeg> m_extEdges = extEdges;
    std::vector<Vec3> m_polygonVertices = polygonVertices;
    PolygonItem* polygonItem = static_cast<PolygonItem*>(m_collisionItem);
    std::vector<Vec3> tempVertices;
    std::vector<Vec3> toBeRotated = polygonItem->vertices();
    geo::rotatePoints(toBeRotated, m_collisionItem->rotation());
    for(auto &vertex : toBeRotated)
    {
        tempVertices.push_back(Vec3(vertex.x() + q2v(m_collisionItem->pos()).x(),
                            vertex.y() + q2v(m_collisionItem->pos()).y()));
        m_edges.push_back(geo::LineSeg(vertex, vertex));
        m_extEdges.push_back(geo::LineSeg(vertex, vertex));
    }
    m_polygonVertices = tempVertices;
    geo::calcEdges(m_polygonVertices, m_edges, m_extEdges);

    QPointF curPoint = m_ball->pos();

    qreal   dt = qreal(time.elapsed()) * 0.001;
    Vec3    oldVel = m_velocity;
    QPointF oldPos = m_ball->pos();
    m_velocity = m_velocity + dt * m_accl;
    m_ball->setPos(m_ball->pos() + v2q((oldVel + m_velocity) * 0.5 * dt * 100.0));

    QPointF nextPoint = m_ball->pos();

    m_velocity = oldVel;
    m_ball->setPos(oldPos);

    Vec3 nearestP(0.0, 0.0, 0.0);
    bool hasIntersection = false;
    int intersectionCounter = 0;
    unsigned long counter = 0;
    geo::LineSeg ls(Vec3(0, 0, 0), Vec3(0, 0, 0));
    geo::LineSeg ls1(q2v(curPoint), q2v(nextPoint));

    for(const auto &vertex : m_polygonVertices)
    {
        geo::LineSeg ls2(m_extEdges[counter].p0, m_extEdges[counter].p1);
        Vec3 ip[2] = {Vec3(), Vec3()};
        double t[2];
        if(geo::hasLinesegCircleIntersection(ls1, vertex, m_ball->boundingRect().width()/2, ip, t)){
            if(intersectionCounter == 0)
            {
                nearestP = ip[1];
                intersectionCounter++;
                m_curCollisionType = CIRCLE;
            }
            else
            {
                nearestP = geo::nearestPoint(q2v(m_ball->pos()), nearestP, ip[1]);
                if(nearestP == ip[1])
                {
                    m_curCollisionType = CIRCLE;
                }
            }
            hasIntersection = true;
        }
        if(geo::hasLinesegLinesegIntersection(ls1, ls2, ip[0]))
        {
            if(intersectionCounter == 0)
            {
                nearestP = ip[0];
                intersectionCounter++;
                m_curCollisionType = LINE;
                ls = ls2;
            }
            else
            {
                nearestP = geo::nearestPoint(q2v(m_ball->pos()), nearestP, ip[0]);
                if(nearestP == ip[0])
                {
                    m_curCollisionType = LINE;
                    ls = ls2;
                }
            }
            hasIntersection = true;
        }
        if(counter <= m_polygonVertices.size() - 1)
        {
            counter++;
        }
    }
    if(not hasIntersection)
    {
        return GEO_POLYGON_NONE;
    }
    calcRestVelocity(nearestP, curPoint, nextPoint, dt, t, ls, m_velocity, m_polygonVertices);
    return GEO_POLYGON_INTERSECT;
}

/*! Calculates the remaining distance the ball has to go until he collides of a polygon, and thus, the residual velocity addition the ball would receive
 * \brief VelocityEngine::calcRestVelocity
 * \param p             -   Vector3 object : point the ball intersected the extended area
 * \param curPoint      -   QPointF : current position pinball
 * \param nextPoint     -   QPointF : predicted position pinball in next intervall
 * \param dt            -   double : time that has passed since the last TimerEvent
 * \param t             -   double : remaining time until collision
 * \param l             -   LineSeg : line segment of an extended edge which the ball intersected
 */
void VelocityEngine::calcRestVelocity(Vec3 p, const QPointF &curPoint, const QPointF &nextPoint,
                                 double dt, double &t, const geo::LineSeg &l, Vec3& m_velocity,
                                      std::vector<Vec3> m_polygonVertices)
{
    calcRestVelo(p, curPoint, nextPoint, dt, t, m_velocity);
    if(m_curCollisionType == CIRCLE)
    {
        int counter = 0;
        Vec3 nearestVertex;
        for(Vec3 vertex : m_polygonVertices)
        {
            if(counter == 0)
            {
                nearestVertex = vertex;
                counter++;
            }
            nearestVertex = geo::nearestPoint(p, nearestVertex, vertex);
        }
        col::CircleOp(m_ball, m_velocity, dt, nearestVertex);
        return;
    }
    col::PolygonLineOp(m_ball, m_velocity, l, dt);
}

void VelocityEngine::calcRestVelo(Vec3 p, const QPointF &curPoint, const QPointF &nextPoint,
                                   double dt, double &t, Vec3& m_velocity)
{
    Vec3 d = q2v(nextPoint) - q2v(curPoint);
    double t1 = ((-2 * m_velocity.length()) / m_accl.length()) / 2 +
                sqrt(geo::sqr((2 * m_velocity.length() / m_accl.length()) / 2) +
                     (2 * d.length()) / m_accl.length());
    //double t2 = ((-m_velocity.length()) / m_accl.length()) - sqrt(geo::sqr(m_velocity.length() / m_accl.length()) + (2 * d.length()) / m_accl.length());

    t1 *= 0.001;
    t = dt - t1;
    m_velocity = m_velocity + t1 * m_accl;


    m_ball->setPos(v2q(p));
}

} //namespace
