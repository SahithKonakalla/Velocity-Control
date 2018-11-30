#include "DriveForward.h"
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

DriveForward::DriveForward(double _setpoint) : setpoint(_setpoint),
		velocityCont(new VelocityController(setpoint)){
	time1 = 0;
	time2 = 0;
	velocity = 0;
	position_avg=0;

	Requires(drive);

}

void DriveForward::Initialize() {
	position_avg = fabs((drive->leftDistance() + drive->rightDistance()) / 2);
	velocity = velocityCont->Tick(position_avg,1);
	std::clock_t start;
	time1 = (std::clock()-start)/(double)CLOCKS_PER_SEC;
	drive->resetEncoders();
	drive->gyroReset();
}

// Called repeatedly when this Command is scheduled to run
void DriveForward::Execute() {
	std::clock_t start;
	time2 = (std::clock()-start)/(double)CLOCKS_PER_SEC;
	double time = time2-time1;
	cout<<"TIME: "<<time<<endl;
	position_avg = fabs((drive->leftDistance() + drive->rightDistance()) / 2);
	double velocity = velocityCont->Tick(position_avg,time);
	cout<<"VELOCTIY: "<<velocity<<endl;
	time1 = time2;
	//drive->tankDrive("magic",200, 200, 1000, 500);
	drive->tankDrive("auto",velocity,velocity);
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


