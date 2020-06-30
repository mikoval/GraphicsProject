#ifndef PONG_SIMULATION_H
#define PONG_SIMULATION_H

#include <Simulator/Simulation.h>
#include <Pong/PongGame.h>
#include <Pong/PongGameRenderer.h>


class pongSimulation : public Simulation {

private:
	void display();
	PongGame *game;
	PongGameRenderer *gameRenderer;

public:
	pongSimulation();
	void simulate();

};

#endif