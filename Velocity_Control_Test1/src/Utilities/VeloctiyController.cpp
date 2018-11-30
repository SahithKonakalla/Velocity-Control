#include "VelocityController.h"
#include "RobotMap.h"
#include <iostream>

VelocityController::VelocityController(double setPoint){
	this->setPoint = setPoint*(4096.0/(6.0*3.1415));
	this->velocity = VELOCITY_MIN;
	this->error = setPoint;
	this->distance1 = setPoint/5.0;
	this->distance2 = 3.0*setPoint/5.0+distance1;
	this->distance3 = setPoint/5.0+distance2;
	this->time1=(2*distance1)/(VELOCITY_MAX+VELOCITY_MIN);
	this->time2=(2*(distance2-distance1))/(VELOCITY_MAX*2);
	this->time3=(2*distance3)/(VELOCITY_MAX+VELOCITY_MIN);
	this->time_total=time1+time2+time3;
	this->acceleration = (VELOCITY_MAX-VELOCITY_MIN)/time1;
}

double VelocityController::Tick(double measuredValue, double time) {
	std::cout << "Acceleration: " << acceleration << std::endl;
	error = setPoint-measuredValue;
	if(measuredValue <= this->distance1){
		this->velocity +=acceleration*time;
		return velocity;

	}
	else if(measuredValue<= this->distance2){
		if(velocity>VELOCITY_MAX)
			this->velocity = VELOCITY_MAX;
		else
			return velocity;
		return velocity;
	}
	else if(error < 0){
		velocity = -VELOCITY_MIN;
	}
	else{
		if(velocity<VELOCITY_MIN){
			return VELOCITY_MIN;
		}
		this->velocity -=acceleration*time;
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
