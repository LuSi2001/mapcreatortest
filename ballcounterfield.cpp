#include "ballcounterfield.h"

#include <QPainter>

BallCounterField::BallCounterField(int startCount, FieldItem *parent) :
    FieldItem(parent),
    m_count(startCount)
{

}

void BallCounterField::setCount(int count)
{
    m_count = count;
    update(boundingRect());
}

QRectF BallCounterField::boundingRect() const
{
    return {-50, -20, 100, 40};
}

void BallCounterField::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::SolidLine);
    QPainterPath path;
    path.addRect(boundingRect());
    path.addText(QPointF(-38, 5), QFont(), QString::number(m_count) + " Ball");
    painter->drawPath(path);
}

QPainterPath BallCounterField::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    path.addText(QPointF(-38, 5), QFont(), QString::number(m_count) + " Ball");
    return path;
}

const QString BallCounterField::name() const
{
    return "ballCounterField";
}

void BallCounterField::handleCollision(Vec3 &m_velocity, Vec3 &m_accl, QTime &time)
{

}
