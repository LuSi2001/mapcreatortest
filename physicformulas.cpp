#include "physicformulas.h"
#include "constants.h"
#include "math.h"

#include <QDebug>

#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(8)

namespace formula
{

//Inclined plane

/*! Calculates the force acting on an object with a speific mass
 * \brief weightForce
 * \param m             -   double : mass
 * \return double       -   weight in Newton [N]
 */
double weightForce(double m)
{
    return m * ACCELERATION_OF_GRAVITY;
}

/*! Calculates the downhill force of a body on an inclined plane
 * \brief downHillForce
 * \param m             -   double : mass
 * \param alpha         -   double : angle of the inclined plane
 * \return double       -   downhill force in Newton [N]
 */
double downHillForce(double m, double alpha)
{
    return m * ACCELERATION_OF_GRAVITY * sin(alpha * PI/180);
}

double downHillForceByMeasurements(double m, double h, double l)
{
    return weightForce(m) * (h / l);
}

/*! Calculates the normal force of an object and its direction is perpendicular to surface the object contacts
 * \brief normalForce
 * \param m             -   double : mass of the object
 * \param alpha         -   double : angle of inclined plane
 * \return double       -   normal force in Newton [N]
 */
double normalForce(double m, double alpha)
{
    return m * ACCELERATION_OF_GRAVITY * cos(alpha * PI/180);
}

double normalForceByMeasurements(double m, double b, double l)
{
    return weightForce(m) * (b / l);
}

//Friction
double dynamicFriction(double m, double alpha)
{
    return COEFFICIENT_OF_STATIC_FRICTION * normalForce(m, alpha);
}

//Consistent accelerated motion
double pathTimeLaw(double accl, double time)
{
    return 0.5 * accl * (time * time);
}

double pathTimeLawAdv(double accl, double time, double startVelo, double startPos)
{
    return 0.5 * accl * (time * time) + startVelo * time + startPos;
}

double velocityTimeLaw(double accl, double time, double startVelo)
{
    return accl * time + startVelo;
}

double actionPrinciple(double m, double accl)
{
    return m * accl;
}

//Other values
double heightPinballBoard(double boardLength, double angle)
{
    return boardLength * sin(angle * PI/180);
}

/*! Calculates the velocity of an object at the end of an inclined plane
 * \brief maxVelo
 * \param boardLength   -   double : length of the board
 * \param angle         -   double : angle of the board
 * \return double       -   velocity in metre per second [m/s]
 */
double maxVelo(double boardLength, double angle)
{
    return sqrt(2 * ACCELERATION_OF_GRAVITY * heightPinballBoard(boardLength, angle)) *
           sqrt(5/7);
}

double angularSpeed(double angle, double rotTime)
{
    if(rotTime == 0.0 or angle == 0.0)
    {
        return 0.0;
    }
    return (angle * PI/180) / rotTime;
}

} //namespace
