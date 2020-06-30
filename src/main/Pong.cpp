#include <Pong/pongSimulation.h>

int main(int argc, char** argv)
{
	Simulation *simulation = new pongSimulation();

	simulation->simulate();
}