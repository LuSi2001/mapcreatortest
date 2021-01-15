#include "endzone.h"
#include "velocityengine.h"
#include "ballcounthandler.h"

#include "QPainter"
#include <QTime>

EndZone::EndZone(CounterMode mode, Zone *parent) :
    Zone(parent),
    m_countermode(mode)
{

}

void EndZone::setCounterMode(CounterMode mode)
{
    m_countermode = mode;
}

CounterMode EndZone::counterMode()
{
    return m_countermode;
}

QRectF EndZone::boundingRect() const
{
    return {-BALL_RADIUS, -BALL_RADIUS, BALL_RADIUS * 10, BALL_RADIUS * 3};
}

void EndZone::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::red);
    QPainterPath path;
    path.addRect(boundingRect());
    painter->drawPath(path);
}

QPainterPath EndZone::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

const QString EndZone::name() const
{
    return "endZone";
}

void EndZone::handleCollision(Vec3 &m_velocity, Vec3 &m_accl, QTime &time)
{
    PinballItem* ball = velo::VelocityEngine::inst().ball();
    if(ball->pos().y() - y() <= 0.001)
    {
        ball->setPos(375, 425 - PLUNGER_PULL_LIMIT + 50 - 5);
        if(m_countermode == COUNT_N_DISAPPEAR)
        {
            BallCountHandler::instance().increaseCount();
            m_velocity = Vec3();
            return;
        }
    }
    qreal   dt = qreal(time.elapsed()) * 0.001;
    Vec3    oldVel = m_velocity;
    m_velocity = m_velocity + dt * m_accl;
    PinballItem* m_ball = velo::VelocityEngine::inst().ball();
    m_ball->setPos(m_ball->pos() + v2q((oldVel + m_velocity) * 0.5 * dt * 100.0));
}
