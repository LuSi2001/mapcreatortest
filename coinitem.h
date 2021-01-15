#ifndef COINITEM_H
#define COINITEM_H

#include "circleitem.h"
#include "scorehandler.h"

class QTime;

class CoinItem : public CircleItem
{
public:
    CoinItem(CircleItem* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void outputScore(ScoreHandler& sh);

    QPainterPath shape() const override;
    const QString name() const override;
    int points() const;
    void handleCollision(Vec3& m_velocity, Vec3 &m_accl, QTime &time) override;

private:
    bool m_hasCooldown;
    bool hasCooldown();

    QTime* m_timer;
};

#endif // COINITEM_H
