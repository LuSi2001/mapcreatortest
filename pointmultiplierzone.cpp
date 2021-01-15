#include "scorehandler.h"
#include "pointmultiplierzone.h"
#include "velocityengine.h"

#include <QPainter>
#include <QTime>

PointMultiplierField::PointMultiplierField(double multiplier, Zone *parent) :
    Zone(parent),
    m_multiplier(multiplier)
{

}

double PointMultiplierField::multiplier() const
{
    return m_multiplier;
}

QRectF PointMultiplierField::boundingRect() const
{
    return {-20, -20, 40, 40};
}

void PointMultiplierField::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::SolidLine);
    QPainterPath path;
    path.addRect(boundingRect());
    path.addText(QPointF(-8, 5), QFont(), QString::number(m_multiplier) + "x");
    painter->drawPath(path);
}

QPainterPath PointMultiplierField::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    path.addText(QPointF(-8  , 5), QFont(), QString::number(m_multiplier) + "x");
    return path;
}

const QString PointMultiplierField::name() const
{
    return "multiplier";
}

void PointMultiplierField::handleCollision(Vec3 &m_velocity, Vec3 &m_accl, QTime &time)
{
    ScoreHandler::instance().setMultiplier(multiplier());
    qreal   dt = qreal(time.elapsed()) * 0.001;
    Vec3    oldVel = m_velocity;
    m_velocity = m_velocity + dt * m_accl;
    PinballItem* m_ball = velo::VelocityEngine::inst().ball();
    m_ball->setPos(m_ball->pos() + v2q((oldVel + m_velocity) * 0.5 * dt * 100.0));
}
