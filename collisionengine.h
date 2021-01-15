#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include <QGraphicsItem>
#include <QTime>

#include "geometrylib.h"
#include "pinballitem.h"

namespace col
{

    extern bool checkForCollision(QGraphicsItem *ball, std::vector<PinballItem*> objects,
                                  Vec3 &velo, Vec3 &accl, QTime &time, unsigned long &index);
    extern void CircleOp(QGraphicsItem *ball, Vec3 &velo, const double dt, const Vec3 &p);
    extern void PolygonLineOp(QGraphicsItem *ball, Vec3 &velo, const geo::LineSeg &l, double dt);

} //namespace

#endif // COLLISIONENGINE_H
