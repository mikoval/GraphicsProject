#ifndef SIMULATION_H
#define SIMULATION_H

#include <Math/MathTools.h>
#include <Controls/InputManager.h>

class Simulation {
protected:
	InputManager *inputManager;
public:
	Simulation();
	void Draw();
	void Update();
	
	virtual void setInputManager(InputManager *im);
	virtual void simulate();
	virtual void loadScene(string scene);
	
};

#endif