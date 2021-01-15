#ifndef AUTOPLUNGERITEM_H
#define AUTOPLUNGERITEM_H

#include "polygonitem.h"

class AutoPlungerItem : public PolygonItem
{
public:
    AutoPlungerItem(PolygonItem *parent = nullptr);
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
    std::map<Vec3, Vec3> m_bisectrices;

    std::vector<Vec3> m_vertices;

    std::vector<geo::LineSeg> m_edges;
    std::vector<geo::LineSeg> m_extEdges;
};

#endif // AUTOPLUNGERITEM_H
