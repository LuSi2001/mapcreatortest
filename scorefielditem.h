#ifndef SCOREFIELDITEM_H
#define SCOREFIELDITEM_H

#include "fielditem.h"

class ScoreFieldItem : public FieldItem
{
public:
    ScoreFieldItem(int startScore = 0, FieldItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void setScore(int points);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    const QString name() const override;
    void handleCollision(Vec3& m_velocity, Vec3 &m_accl, QTime &time) override;

private:
    int m_score;
    double m_multiplier;
};

#endif // SCOREFIELDITEM_H
