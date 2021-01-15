#include "geometrylib.h"

namespace geo
{

/*! Calculates the intersection points of a line and a circle
 * \brief linesegCircleIntersection
 * \param ls            -   struct LineSeg : line segment
 * \param cCenter       -   Vector3 object : circle center
 * \param radius        -   double : radius of the circle
 * \param ip            -   Array of Vector3 objects : stores intersection points
 * \return int          -   type of intersection
 */
int linesegCircleIntersection(const LineSeg &ls, const Vec3 &cCenter, double radius, Vec3 ip[2])
{
    Vec3 d = ls.dir();
    double disSegment = d.lengthSquared();
    double D = (ls.p0 - cCenter ^ ls.p1 - cCenter).z();
    double delta = sqr(radius) * disSegment - sqr(D);

    if(delta < 0.0){ return GEO_CIRCLE_NONE; }

    delta = sqrt(delta);
    Vec3 dd(D * d);

    if(delta < 0.001)
    {
        ip[0] = cCenter + Vec3(dd.y(), -dd.x(), dd.z()) / disSegment;
        ip[1] = Vec3();
        return GEO_CIRCLE_TOUCH;
    }

    double tx = (d.y() < 0.0 ? -1.0 : 1.0) * d.x() * delta;
    double ty = fabs(d.y()) * delta;

    Vec3 pseudo1(dd.y() + tx, -dd.x() + ty);
    Vec3 pseudo2(dd.y() - tx, -dd.x() - ty);
    ip[0] = cCenter + pseudo1 / disSegment;
    ip[1] = cCenter + pseudo2 / disSegment;

    return GEO_CIRCLE_INTERSECT;
}

/*! Calculates the intersection point of two lines using two line segments
 * \brief linesegLinesegIntersection
 * \param ls1           -   struct LineSeg : first line segment
 * \param ls2           -   struct LineSeg : second line segment
 * \param ip            -   Vector3 object : stores intersection point
 * \return int          -   type of intersection
 */
int linesegLinesegIntersection(const LineSeg &ls1, const LineSeg &ls2, Vec3 &ip)
{
    Vec3 firstDir = ls1.dir();
    Vec3 secondDir = ls2.dir();
    bool chanceParallel = false;
    if(firstDir.x() != 0.0 and secondDir.x() != 0.0)
    {
        firstDir = firstDir/firstDir.x();
        secondDir = secondDir/secondDir.x();
        chanceParallel = true;
    }
    if(firstDir.y() != 0.0 and secondDir.y() != 0.0)
    {
        firstDir = firstDir/firstDir.y();
        secondDir = secondDir/secondDir.y();
        chanceParallel = true;
    }
    if(firstDir == secondDir and chanceParallel)
    {
        Vec3 pointOnFirst = ls1.p0 + 5 * firstDir;
        Vec3 pointOnSecond = ls2.p0 + 5 * secondDir;
        ip = Vec3();
        if(pointOnFirst == pointOnSecond){ return GEO_LINES_COINCIDENT; }
        return GEO_LINES_TRUEPARALLEL;
    }
    if(firstDir.invert() == secondDir and chanceParallel)
    {
        Vec3 pointOnFirst = ls1.p0 + 5 * firstDir.invert();
        Vec3 pointOnSecond = ls2.p0 + 5 * secondDir;
        ip = Vec3();
        if(pointOnFirst == pointOnSecond){ return GEO_LINES_COINCIDENT; }
        return GEO_LINES_TRUEPARALLEL;
    }
    double s = (secondDir.perp2D() * (ls2.p0 - ls1.p0))/(secondDir.perp2D() * firstDir);
    ip = ls1.p0 + s * firstDir;
    double t = (firstDir.perp2D() * (ls1.p0 - ls2.p0))/(firstDir.perp2D() * secondDir);
    //Vec3 ip2 = ls2.p0 + t * secondDir;
    if(s <= 1 and s >= 0 and t <= 1 and t >= 0){ return GEO_LINES_INTERSECT_BOTH; }
    if((s <= 1 and s >= 0) or (t <= 1 and t >= 0)){ return GEO_LINES_INTERSECT_ONE; }
    return GEO_LINES_INTERSECT_NONE;
}

/*! Checks if a point lies on a specific line segment
 * \brief pointOnLineseg
 * \param point         -   Vector3 object : given point
 * \param ls            -   struct LineSeg : line segment
 * \return int          -   type of relation
 */
int pointOnLineseg(const Vec3 &point, const LineSeg &ls){
    double AB = sqrt(sqr(ls.p1.x() - ls.p0.x()) + sqr(ls.p1.y() - ls.p0.y()) +
                     sqr(ls.p1.z() - ls.p0.z()));
    double AP = sqrt(sqr(point.x() - ls.p0.x()) + sqr(point.y() - ls.p0.y()) +
                     sqr(point.z() - ls.p0.z()));
    double PB = sqrt(sqr(ls.p1.x() - point.x()) + sqr(ls.p1.y() - point.y()) +
                     sqr(ls.p1.z() - point.z()));
    if(abs(AB - (AP + PB)) <= 0.0000001){
        return GEO_POINT_ON_LINE_SEGMENT;
    }
    return GEO_NOT_POINT_ON_LINE;
}

/*! Calculates the angle between two vectors in degrees
 * \brief angleVectorVector
 * \param first         -   Vector3 object : first vector
 * \param second        -   Vector3 object : second vector
 * \return double       -   angle in degrees
 */
double angleVectorVector(Vec3 &first, Vec3 &second)
{
    double scalar = first * second;
    return acos(scalar/(first.length() * second.length())) * (180/PI);
}

/*! Calculates the intersection points of a line and a circle if existend
 * \brief hasLinesegCircleIntersection
 * \param ls            -   struct LineSeg : line segment
 * \param cCenter       -   Vector3 object : circle center
 * \param radius        -   double : radius of the circle
 * \param ip            -   Array of Vector3 objects : stores intersection points
 * \return bool         -   if the line segment and the circle intersect
 */
bool hasLinesegCircleIntersection(const LineSeg &ls, const Vec3 &cCenter, double radius,
                                  Vec3 ip[2], double t[2])
{
    Vec3 d = ls.dir();
    double disSegment = d.lengthSquared();
    double D = (ls.p0 - cCenter ^ ls.p1 - cCenter).z();
    double delta = sqr(radius) * disSegment - sqr(D);

    if(delta < 0.0){ return false; }

    delta = sqrt(delta);
    Vec3 dd(D * d);

    if(delta < 0.001){ return false; }

    double tx = (d.y() < 0.0 ? -1.0 : 1.0) * d.x() * delta;
    double ty = fabs(d.y()) * delta;

    Vec3 pseudo1(dd.y() + tx, -dd.x() + ty);
    Vec3 pseudo2(dd.y() - tx, -dd.x() - ty);
    ip[0] = cCenter + pseudo1 / disSegment;
    ip[1] = cCenter + pseudo2 / disSegment;
    t[0] = d * (ip[0] - ls.p0) / disSegment;
    t[1] = d * (ip[1] - ls.p0) / disSegment;

    return true;
}

/*! Calculates the intersection point of two lines using two line segments if existend
 * \brief hasLinesegLinesegIntersection
 * \param ls1           -   struct LineSeg : first line segment
 * \param ls2           -   struct LineSeg : second line segment
 * \param ip            -   Vector3 object : stores intersection point
 * \return bool         -   if the first and the second line segement intersect
 */
bool hasLinesegLinesegIntersection(const LineSeg &ls1, const LineSeg &ls2, Vec3 &ip)
{
    Vec3 firstDir = ls1.dir();
    Vec3 secondDir = ls2.dir();
    bool chanceParallel = false;
    if(firstDir.x() != 0.0 and secondDir.x() != 0.0)
    {
        firstDir = firstDir/firstDir.x();
        secondDir = secondDir/secondDir.x();
        chanceParallel = true;
    }
    if(firstDir.y() != 0.0 and secondDir.y() != 0.0)
    {
        firstDir = firstDir/firstDir.y();
        secondDir = secondDir/secondDir.y();
        chanceParallel = true;
    }
    if(firstDir == secondDir and chanceParallel){ return false; }
    if(firstDir.invert() == secondDir and chanceParallel){ return false; }
    double s = (secondDir.perp2D() * (ls2.p0 - ls1.p0))/(secondDir.perp2D() * firstDir);
    ip = ls1.p0 + s * firstDir;
    //double t = (firstDir.perp2D() * (ls1.p0 - ls2.p0))/(firstDir.perp2D() * secondDir);
    //Vec3 ip2 = ls2.p0 + t * secondDir;
    return true;
}

/*! Checks if a point lies on a specific line segment
 * \brief isPointOnLine
 * \param point         -   Vector3 object : given point
 * \param ls            -   struct LineSeg : line segment
 * \return              -   if point is on line segment
 */
bool isPointOnLine(const Vec3 &point, const LineSeg &ls)
{
    const double &p0x = ls.p0.x();
    const double &p0y = ls.p0.y();
    const double &p0z = ls.p0.z();
    const double &p1x = ls.p1.x();
    const double &p1y = ls.p1.y();
    const double &p1z = ls.p1.z();
    const double &p2x = point.x();
    const double &p2y = point.y();
    const double &p2z = point.z();
    double AB = sqrt(sqr(p1x - p0x) + sqr(p1y - p0y) +
                     sqr(p1z - p0z));
    double AP = sqrt(sqr(p2x - p0x) + sqr(p2y - p0y) +
                     sqr(p2z - p0z));
    double PB = sqrt(sqr(p1x - p2x) + sqr(p1y - p2y) +
                     sqr(p1z - p2z));
    if(abs(AB - (AP + PB)) <= 0.0000001){ return true; }
    return false;
}

/*! Given two points and one compare point this function returns the point with the smallest distance to the compare point
 * \brief nearestPoint
 * \param point         -   Vector3 object : point which is compared to
 * \param cPoint1       -   Vector3 object : first point
 * \param cPoint2       -   Vector3 object : second point
 * \return Vec3         -   the nearest Vector3 object
 */
const Vec3 &nearestPoint(const Vec3& point, const Vec3& cPoint1, const Vec3& cPoint2)
{
    if((cPoint1 - point).length() > (cPoint2 - point).length()){ return cPoint2; }
    return cPoint1;
}

/*! Calculates the bisectrix of every concave vertex of a polygon
 * \brief calcBisectrices
 * \param vertices      -   std::vector<Vector3 object> : vertices of polygon
 * \param edges         -   std::vector<LineSeg> : stores edges
 * \param bisectrices   -   std::map<Vector3 object, Vector3 object> : stores bisectrices
 */
void calcBisectrices(const std::vector<Vec3>& vertices, std::vector<geo::LineSeg>& edges,
                     std::map<Vec3, Vec3>& bisectrices)
{
    for(unsigned long i = 0; i < vertices.size() - 1; i++)
    {
        if((edges[i].dir().normalized() ^ edges[i + 1].dir().normalized()).z() > 0)
        {
            Vec3 bisectrix = edges[i].p1 +
                             (edges[i].dir() - edges[i + 1].dir()).invert() * BALL_RADIUS;
            bisectrices.insert(std::pair<Vec3, Vec3>(edges[i].p1, bisectrix));
        }
    }
}

/*! Calculates edge vectors and extended edge vectors of a polygon
 * \brief calcEdges
 * \param vertices      -   std::vector<Vector3 object> : vertices of polygon
 * \param edges         -   std::vector<LineSeg> : stores edges
 * \param extEdges      -   std::vector<LineSeg> : stores extended edges
 */
void calcEdges(const std::vector<Vec3>& vertices, std::vector<geo::LineSeg>& edges,
               std::vector<geo::LineSeg>& extEdges)
{
    unsigned long counter = 0;
    for(auto vertex : vertices)
    {
        if(counter < vertices.size() - 1)
        {
            edges[counter].setPoints(vertex, vertices[counter + 1]);
            extEdges[counter].p0 = vertex + edges[counter].dir().perp2D().normalized() *
                                   BALL_RADIUS;
            extEdges[counter].p1 = vertices[counter + 1] +
                                   edges[counter].dir().perp2D().normalized() *
                                   BALL_RADIUS;
            counter++;
        }
        if(counter == vertices.size() - 1)
        {
            edges[counter].p0 = vertices[vertices.size() - 1];
            edges[counter].p1 = vertices[0];
            extEdges[counter].p0 = vertices[vertices.size() - 1] +
                                   edges[counter].dir().perp2D().normalized() *
                                   BALL_RADIUS;
            extEdges[counter].p1 = vertices[0] +
                                   edges[counter].dir().perp2D().normalized() *
                                   BALL_RADIUS;
            counter++;
        }
    }
}

void rotateEdges(std::vector<LineSeg>& edges, double angle)
{
    angle = angle * PI/180;
    for(auto& edge : edges)
    {
        Vec3 tmpP0 = edge.p0;
        Vec3 tmpP1 = edge.p1;
        edge.p0.x() = tmpP0.x() * cos(angle) - tmpP0.y() * sin(angle);
        edge.p0.y() = tmpP0.x() * sin(angle) + tmpP0.y() * cos(angle);
        edge.p1.x() = tmpP1.x() * cos(angle) - tmpP1.y() * sin(angle);
        edge.p1.y() = tmpP1.x() * sin(angle) + tmpP1.y() * cos(angle);
    }
}

void rotatePoints(std::vector<Circle>& circlesMps, double angle)
{
    angle = angle * PI/180;
    for(auto &circle : circlesMps)
    {
        Vec3 tmp = circle.mp;
        circle.mp.x() = tmp.x() * cos(angle) - tmp.y() * sin(angle);
        circle.mp.y() = tmp.x() * sin(angle) + tmp.y() * cos(angle);
    }
}

void rotatePoints(std::vector<Vec3>& points, double angle)
{
    angle = angle * PI/180;
    for(auto &point : points)
    {
        Vec3 tmp = point;
        point.x() = tmp.x() * cos(angle) - tmp.y() * sin(angle);
        point.y() = tmp.x() * sin(angle) + tmp.y() * cos(angle);
    }
}

void setOffset(std::vector<Circle>& circlesMps, const Vec3& offset)
{
    for(auto &circle : circlesMps)
    {
        circle.mp.x() += offset.x();
        circle.mp.y() += offset.y();
    }
}

void setOffset(std::vector<LineSeg>& edges, const Vec3& offset)
{
    for(auto& edge : edges)
    {
        edge.p0.x() += offset.x();
        edge.p0.y() += offset.y();
        edge.p1.x() += offset.x();
        edge.p1.y() += offset.y();
    }
}

} // namespace
