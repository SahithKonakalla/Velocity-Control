#ifndef Turn_H
#define Turn_H

#include <Utilities/AutoWVPIDController.h>
#include "../CommandBase.h"

class Turn : public CommandBase {
	public:
	Turn(double _setpoint);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double setpoint;
	double fDistance;
};

#endif  // Turn_H
