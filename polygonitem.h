#ifndef POLYGONITEM_H
#define POLYGONITEM_H


#include "pinballitem.h"
#include "geometrylib.h"

class PolygonItem : public PinballItem
{
public:
    PolygonItem(PinballItem *parent = nullptr);

    CollisionObject objectType() const override { return POLYGON; }
    virtual const std::vector<geo::LineSeg>& edges() const = 0;
    virtual const std::vector<geo::LineSeg>& extentedEdges() const = 0;
    virtual const std::vector<Vec3>& vertices() const = 0;
    virtual const std::map<Vec3, Vec3>& bisectrices() const = 0;
};

#endif // POLYGONITEM_H
