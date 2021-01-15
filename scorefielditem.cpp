#include "scorefielditem.h"

#include <QPainter>

ScoreFieldItem::ScoreFieldItem(int startScore, FieldItem *parent) :
    FieldItem(parent),
    m_score(startScore)
{

}

void ScoreFieldItem::setScore(int points)
{
    m_score = points;
    update(boundingRect());
}

QRectF ScoreFieldItem::boundingRect() const
{
    return {-50, -20, 100, 40};
}

void ScoreFieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::SolidLine);
    QPainterPath path;
    path.addRect(boundingRect());
    path.addText(QPointF(-38, 5), QFont(), QString::number(m_score) + " pts");
    painter->drawPath(path);
}

QPainterPath ScoreFieldItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    path.addText(QPointF(-38, 5), QFont(), QString::number(m_score) + " pts");
    return path;
}

const QString ScoreFieldItem::name() const
{
    return "scoreField";
}

void ScoreFieldItem::handleCollision(Vec3 &m_velocity, Vec3 &m_accl, QTime &time)
{

}
