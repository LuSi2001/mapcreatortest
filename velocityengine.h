#ifndef VELOCITYENGINE_H
#define VELOCITYENGINE_H

#include "utils.h"
#include "constants.h"
#include "geometrylib.h"

class PinballItem;
class QTime;

namespace velo
{

class VelocityEngine
{
public:
    static VelocityEngine& inst();
    void setBall(PinballItem* ball);
    void setAccl(const Vec3& accl);
    PinballItem* ball();
    void setCollisionItem(PinballItem *colItem);
    void calcRestVelocity(Vec3 p, const QPointF &curPoint, const QPointF &nextPoint,
                          double dt, double &t, const geo::LineSeg &l, Vec3 &m_velocity, std::vector<Vec3> m_polygonVertices);
    void preciseVelocityCircle(QTime &time, double &t, Vec3 &m_velocity);
    void preciseVelocityCompound(QTime &time, double &t, Vec3 &m_velocity);
    double preciseVelocityPolygon(QTime &time, double &t, std::vector<geo::LineSeg>& edges,
                                  std::vector<geo::LineSeg>& extEdges,
                                  std::vector<Vec3>& polygonVertices, Vec3 &m_velocity);

private:
    PinballItem* m_ball;
    PinballItem* m_collisionItem;
    CollisionType m_curCollisionType;
    Vec3 m_accl;

    VelocityEngine() = default;
    VelocityEngine(const VelocityEngine &) = delete;
    VelocityEngine &operator=(const VelocityEngine &) = delete;
    void calcRestVelo(Vec3 p, const QPointF &curPoint, const QPointF &nextPoint,
                                       double dt, double &t, Vec3 &m_velocity);
};

} //namespace

#endif // VELOCITYENGINE_H
