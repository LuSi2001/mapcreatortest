#ifndef GEOMETRYLIB_H
#define GEOMETRYLIB_H

#include "utils.h"
#include "constants.h"

#include <QDebug>

#define GEO_CIRCLE_NONE             0
#define GEO_CIRCLE_TOUCH            1
#define GEO_CIRCLE_INTERSECT        2

#define GEO_LINES_COINCIDENT        -2
#define GEO_LINES_TRUEPARALLEL      -1
#define GEO_LINES_INTERSECT_NONE    0
#define GEO_LINES_INTERSECT_ONE     1
#define GEO_LINES_INTERSECT_BOTH    2

#define GEO_POLYGON_NONE            0
#define GEO_POLYGON_TOUCH           1
#define GEO_POLYGON_INTERSECT       2

#define GEO_NOT_POINT_ON_LINE       0
#define GEO_POINT_ON_LINE_SEGMENT   1

namespace geo
{

inline double sqr(double v) {return v * v;}

struct Circle
{
    Vec3 mp;
    double r;
    Circle(Vec3 mp, double r){
        this->mp = mp;
        this->r = r;
    }
    double area() const {return PI * sqr(r);}
    double diameter() const {return 2 * r;}
    double perimeter() const {return 2 * PI * r;}
};

struct LineSeg
{
    Vec3 p0, p1;
    LineSeg(Vec3 p0, Vec3 p1)
    {
        this->p0 = p0;
        this->p1 = p1;
    }

    void setPoints(Vec3 p0, Vec3 p1)
    {
        this->p0 = p0;
        this->p1 = p1;
    }
    double  length() const {return (p1 - p0).length();}
    Vec3    dir() const {return p1 - p0;}
    Vec3    normDir() const {return (p1 - p0).normalized();}
    Vec3    perp() const {return dir().perp2D();}
};

extern int linesegCircleIntersection(const LineSeg &ls, const Vec3 &cCenter, double radius, Vec3 ip[]);
extern int linesegLinesegIntersection(const LineSeg &ls1, const LineSeg &ls2, Vec3 &ip);
extern int pointOnLineseg(const Vec3 &point, const LineSeg &ls);
extern double angleVectorVector(Vec3 &first, Vec3 &second);
extern bool hasLinesegCircleIntersection(const LineSeg &ls, const Vec3 &cCenter, double radius, Vec3 ip[], double t[]);
extern bool hasLinesegLinesegIntersection(const LineSeg &ls1, const LineSeg &ls2, Vec3 &ip);
extern bool isPointOnLine(const Vec3 &point, const LineSeg &ls);
extern const Vec3& nearestPoint(const Vec3& point, const Vec3& cPoint1, const Vec3& cPoint2);
extern void calcBisectrices(const std::vector<Vec3>& vertices, std::vector<LineSeg> &edges,
                            std::map<Vec3, Vec3> &bisectrices);
extern void calcEdges(const std::vector<Vec3>& vertices, std::vector<LineSeg> &edges, std::vector<LineSeg> &extEdges);
extern void rotateEdges(std::vector<LineSeg>& edges, double angle);
extern void rotatePoints(std::vector<Circle>& circlesMps, double angle);
extern void rotatePoints(std::vector<Vec3>& points, double angle);
extern void setOffset(std::vector<Circle>& circlesMps, const Vec3& offset);
extern void setOffset(std::vector<LineSeg>& edges, const Vec3& offset);

} //namespace

#endif // GEOMETRYLIB_H
