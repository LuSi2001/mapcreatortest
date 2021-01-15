#ifndef PHYSICFORMULAS_H
#define PHYSICFORMULAS_H

namespace formula
{

//Inclined plane
extern double weightForce(double m);
extern double downHillForce(double m, double alpha);
extern double downHillForceByMeasurements(double m, double h, double l);
extern double normalForce(double m, double alpha);
extern double normalForceByMeasurements(double m, double b, double l);

//Friction
extern double dynamicFriction(double m, double alpha);

//Consistent accelerated motion
extern double pathTimeLaw(double accl, double time); //initial position
extern double pathTimeLawAdv(double accl, double time, double startVelo, double startPos);
extern double velocityTimeLaw(double accl, double time, double startVelo);

//Forces
extern double actionPrinciple(double m, double accl);

//Other
extern double heightPinballBoard(double boardLength, double angle);
extern double maxVelo(double boardLength, double angle);
extern double angularSpeed(double angle, double rotTime);
extern double numRotPerTimeUnit(double rotTime);

} //namespace

#endif // PHYSICFORMULAS_H
