#include "collisionengine.h"

namespace col
{

/*! Checks if a collision between a ball and another object happened
 * \brief checkForCollision
 * \param ball          -   QGraphicsItem : actual pinball
 * \param objects       -   std::vector : all objects relevant in scene
 * \param velo          -   Vector3 object : velocity of the ball
 * \param accl          -   Vector3 object : acceleration of the ball
 * \param time          -   QTime : Timer
 * \param index         -   unsigned long : index of item in objects list
 * \return bool - if a collision happened
 */
bool checkForCollision(QGraphicsItem *ball, std::vector<PinballItem *> objects, Vec3 &velo,
                       Vec3 &accl, QTime &time, unsigned long &index)
{
    qreal   dt = qreal(time.elapsed()) * 0.001;
    Vec3    oldVel = velo;
    QPointF oldPos = ball->pos();
    velo = velo + dt * accl;
    ball->setPos(ball->pos() + v2q((oldVel + velo) * 0.5 * dt * 100.0));
    for(unsigned long i = 0; i < objects.size(); i++)
    {
        if(ball->collidesWithItem(objects[i], Qt::IntersectsItemShape))
        {
            velo = oldVel;
            ball->setPos(oldPos);
            index = i;
            return true;
        }
    }
    velo = oldVel;
    ball->setPos(oldPos);
    return false;
}

/*! Calculates how the ball has to bounce of a circle
 * \brief CircleOp
 * \param ball          -   QGraphicsItem : actual pinball
 * \param velo          -   Vector3 object : velocity of the ball
 * \param dt            -   double : time that has passed since the last TimerEvent
 * \param p             -   Vector3 object : point the ball intersected the circle of an extended vertex
 */
void CircleOp(QGraphicsItem *ball, Vec3 &velo, const double dt, const Vec3 &p)
{
    Vec3 dVec = q2v(ball->pos() - v2q(p));
    const Vec3 &pv = dVec.perp2D().normalized();
    velo = (velo - (velo * pv) * pv * 2.0) * -1.0;
    velo.y() *= VELOCITY_LOSS_Y;
    velo.x() *= VELOCITY_LOSS_X;
    ball->setPos(ball->pos() + v2q(velo) * dt);
}

/*! Calculates how the ball has to bounce of a polygon's edges
 * \brief PolygonLineOp
 * \param ball          -   QGraphicsItem : actual pinball
 * \param velo          -   Vector3 object : velocity of the ball
 * \param l             -   LineSeg : line segment of an extended edge which the ball intersected
 * \param dt            -   double : time that has passed since the last TimerEvent
 */
void PolygonLineOp(QGraphicsItem *ball, Vec3 &velo, const geo::LineSeg &l, double dt)
{
    const Vec3 &dVec = l.normDir();
    velo = (velo - (velo * dVec) * dVec * 2.0) * -1.0;
    velo.y() *= VELOCITY_LOSS_Y;
    velo.x() *= VELOCITY_LOSS_X;
    ball->setPos(ball->pos() + v2q(velo) * dt);
}

}
