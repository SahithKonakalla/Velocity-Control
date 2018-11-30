#ifndef VELOCITYCONTROLLER_H
#define VELOCITYCONTROLLER_H

class VelocityController {
public:
	VelocityController(double setPoint);
	double Tick(double measuredValue, double time);
	void SetSetPoint(double setPoint);
	double GetSetPoint();
	double GetError();
	double GetVelocity();
	double GetAcceleration();

private:
	double setPoint;
	double velocity;
	double error;
	double acceleration;
	double distance1;
	double distance2;
	double distance3;
	double time1;
	double time2;
	double time3;
	double time_total;
};

#endif
