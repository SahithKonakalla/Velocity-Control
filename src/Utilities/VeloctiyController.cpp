#include "VelocityController.h"
#include "RobotMap.h"

VelocityController::VelocityController(double setPoint){
	this->setPoint = setPoint;
	this->velocity = 0;
	this->error = setPoint;
	this->division[0] = setPoint/3;
	this->division[1] = setPoint/3.0+division[0];
	this->division[2] = setPoint/3.0+division[1];
	this->time1=(2*division[0])/VELOCITY_MAX;
	this->time2=(2*(division[1]-division[0]))/(VELOCITY_MAX*2);
	this->time3=(2*division[2])/VELOCITY_MAX;
	this->time_total=time1+time2+time3;
	this->acceleration = VELOCITY_MAX/time1;
}

double VelocityController::Tick(double measuredValue) {
	error = setPoint-measuredValue;
	if(measuredValue <= this->division[0]){ //in this case 2 since time=setpoint/2
		this->velocity +=acceleration/10000.0;
		return velocity;

	}
	else if(measuredValue<= this->division[1]){
		if(velocity>VELOCITY_MAX)
			this->velocity = VELOCITY_MAX;
		else
			return velocity;
		return velocity;
	}
	else{
		if(velocity<VELOCITY_MIN){
			return VELOCITY_MIN;
		}
		this->velocity -=acceleration/10000.0;
		return velocity;
	}
	return 0;
}

void VelocityController::SetSetPoint(double setPoint) {
	this->setPoint = setPoint;
	error = 0;
}

double VelocityController::GetSetPoint() {
	return setPoint;
}

double VelocityController::GetError() {
	return error;
}

double VelocityController::GetVelocity() {
	return velocity;
}
double VelocityController::GetAcceleration(){
	return acceleration;
}
