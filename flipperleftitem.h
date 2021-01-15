#ifndef FLIPPERLEFTITEM_H
#define FLIPPERLEFTITEM_H


#include "flipperitem.h"

class FlipperLeftItem : public FlipperItem
{
public:
    FlipperLeftItem(FlipperItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    const std::vector<geo::LineSeg>& edges() const override;
    const std::vector<geo::LineSeg>& extentedEdges() const override;
    const std::vector<Vec3>& vertices() const override;
    const std::vector<geo::Circle>& circles() const override;
//    void setAngularSpeed(double angle, double time);
//    double angularSpeed() const;
    const QString name() const override;
    const Vec3 lineDir() const override;
    void handleCollision(Vec3& m_velocity, Vec3 &, QTime &time) override;

private:
    std::vector<geo::Circle> mCircles;
    std::vector<geo::LineSeg> mEdges;
    std::vector<geo::LineSeg> mExtendedEdges;
    std::vector<Vec3> mVertices;
//    double mAngularSpeed;
};

#endif // FLIPPERLEFTITEM_H
