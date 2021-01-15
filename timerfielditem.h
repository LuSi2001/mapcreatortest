#ifndef TIMERFIELDITEM_H
#define TIMERFIELDITEM_H

#include "fielditem.h"
#include <QTime>

class TimerFieldItem : public FieldItem
{
public:
    TimerFieldItem(int h = 0, int m = 0, int s = 0, int ms = 0, FieldItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void start();
    void stop();
    void resume();
    void updateTxt();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    const QString name() const override;
    void handleCollision(Vec3& m_velocity, Vec3 &m_accl, QTime &time) override;

private:
    QTime* m_timer;
    QString m_timerStr;

    bool m_stopped;
    int m_reference;
};

#endif // TIMERFIELDITEM_H
