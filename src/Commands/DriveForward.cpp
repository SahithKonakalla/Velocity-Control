#include "DriveForward.h"
#include <iostream>
#include <cmath>
using namespace std;

DriveForward::DriveForward(double _setpoint) : setpoint(_setpoint),
		velocityCont(new VelocityController(setpoint)){
	velocity = 0;
	position_avg=0;

	Requires(drive);

}

void DriveForward::Initialize() {
	position_avg = fabs((drive->leftDistance() + drive->rightDistance()) / 2); //change
	velocity = velocityCont->Tick(position_avg);
	drive->resetEncoders();
	drive->gyroReset();
}

// Called repeatedly when this Command is scheduled to run
void DriveForward::Execute() {
	position_avg = fabs((drive->leftDistance() + drive->rightDistance()) / 2); //change
	double velocity = velocityCont->Tick(position_avg);
	//cout<<"test3 "<<velocity<<endl;
	drive->tankDrive("magic",200, 200, 1000, 500);
	//drive->tankDrive("auto",velocity,velocity);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForward::IsFinished() {
	return fabs(position_avg - setpoint) < 3;
}

// Called once after isFinished returns true
void DriveForward::End() {
	std::cout << "error is finished and REACHED END " << fabs(position_avg - setpoint) << std::endl;
	drive->arcadeDrive(0, 0, 0.2);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForward::Interrupted() {
}


