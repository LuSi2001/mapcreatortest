#ifndef WALLITEM_H
#define WALLITEM_H

#include "polygonitem.h"

class WallItem : public PolygonItem
{
public:
    WallItem(PolygonItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    const std::vector<geo::LineSeg>& edges() const override;
    const std::vector<geo::LineSeg>& extentedEdges() const override;
    const std::vector<Vec3>& vertices() const override;
    const std::map<Vec3, Vec3>& bisectrices() const override;
    const QString name() const override;
    void handleCollision(Vec3& m_velocity, Vec3 &, QTime &time) override;

private:
    std::map<Vec3, Vec3> mBisectrices;

    std::vector<Vec3> mVertices;

    std::vector<geo::LineSeg> mEdges;
    std::vector<geo::LineSeg> mExtEdges;
};

#endif // WALLITEM_H
