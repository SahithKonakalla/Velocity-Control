#ifndef DriveForward_H
#define DriveForward_H

#include <Utilities/AutoWVPIDController.h>
#include <Utilities/VelocityController.h>
#include "../CommandBase.h"

class DriveForward : public CommandBase {
private:
	double setpoint;
	double position_avg;
	double velocity;
	double time1;
	double time2;
	VelocityController* velocityCont;
public:
	DriveForward(double _setpoint);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void setAngle();
};

#endif  // DriveForward_H
