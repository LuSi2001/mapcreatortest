#ifndef BALLITEM_H
#define BALLITEM_H


#include "circleitem.h"

class BallItem : public CircleItem
{
public:
    BallItem(CircleItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    QPainterPath shape() const override;
    const QString name() const override;
    void handleCollision(Vec3& m_velocity, Vec3 &, QTime &time) override;

    void readFromXML(const ReaderProxy& reader) override;

    friend QDataStream &operator<<(QDataStream &str, const BallItem &item)
    {
        return str << item.radius();
    }

    void write(QDataStream &str) const override
    {
        PinballItem::write(str);
        str << m_radius;
    }

    virtual void read(QDataStream &str) override
    {
        PinballItem::read(str);
        str >> m_radius;
    }

private:
    double m_radius;
    QColor m_color;

};

#endif // BALLITEM_H
