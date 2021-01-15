#include "coinitem.h"
#include "velocityengine.h"

#include <QPainter>
#include <QTime>

CoinItem::CoinItem(CircleItem *parent) :
    CircleItem(10.0, parent),
    m_hasCooldown(false)
{
    m_timer = new QTime();
    m_timer->start();
}

void CoinItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::SolidLine);
    QPainterPath path;
    path.addEllipse(boundingRect());
    painter->drawPath(path);
}

QPainterPath CoinItem::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

const QString CoinItem::name() const
{
    return "coin";
}

int CoinItem::points() const
{
    return COIN_PTS;
}

void CoinItem::outputScore(ScoreHandler &sh)
{
    if(not hasCooldown())
    {
        sh.increaseScore(points());
        m_timer->restart();
        m_hasCooldown = true;
    }
}

bool CoinItem::hasCooldown()
{
    if(m_hasCooldown)
    {
       if(m_timer->elapsed() >= 3000)
       {
           return false;
       }
       return true;
    }
    return false;
}

void CoinItem::handleCollision(Vec3 &m_velocity, Vec3 &m_accl, QTime &time)
{
    outputScore(ScoreHandler::instance());
    qreal   dt = qreal(time.elapsed()) * 0.001;
    Vec3    oldVel = m_velocity;
    m_velocity = m_velocity + dt * m_accl;
    PinballItem* m_ball = velo::VelocityEngine::inst().ball();
    m_ball->setPos(m_ball->pos() + v2q((oldVel + m_velocity) * 0.5 * dt * 100.0));
}
