#ifndef PLUNGERITEM_H
#define PLUNGERITEM_H


#include "polygonitem.h"

class PlungerItem : public PolygonItem
{
public:
    PlungerItem(PolygonItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void setLaunchSpeed(double launchSpeed);
    void pull();
    void push();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    const std::vector<geo::LineSeg>& edges() const override;
    const std::vector<geo::LineSeg>& extentedEdges() const override;
    const std::vector<Vec3>& vertices() const override;
    const std::map<Vec3, Vec3>& bisectrices() const override;
    const QString name() const override;
    double launchSpeed() const;
    Vec3 lineDir();
    void handleCollision(Vec3& m_velocity, Vec3 &, QTime &time) override;

private:
    double m_launchSpeed;
    double m_plungerPullBack;
    bool m_plungerPullLimit;
    bool m_plungerPushLimit;
    bool m_plungerLimits;

    std::map<Vec3, Vec3> mBisectrices;

    std::vector<Vec3> mVertices;

    std::vector<geo::LineSeg> mEdges;
    std::vector<geo::LineSeg> mExtEdges;

    void setBools();
};

#endif // PLUNGERITEM_H
