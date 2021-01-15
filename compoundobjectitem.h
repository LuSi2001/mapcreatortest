#ifndef COMPOUNDOBJECTITEM_H
#define COMPOUNDOBJECTITEM_H


#include "pinballitem.h"
#include "geometrylib.h"

class CompoundObjectItem : public PinballItem
{
public:
    CompoundObjectItem(PinballItem *parent = nullptr);

    CollisionObject objectType() const override{ return COMPOUND_OBJECT; }
    virtual const std::vector<geo::LineSeg>& edges() const = 0;
    virtual const std::vector<geo::LineSeg>& extentedEdges() const = 0;
    virtual const std::vector<Vec3>& vertices() const = 0;
    virtual const std::vector<geo::Circle>& circles() const = 0;
};

#endif // COMPOUNDOBJECTITEM_H
