#include <Simulator/glSimulation.h>

int main(int argc, char** argv)
{
  Simulation *simulation = new glSimulation();

  string scene = "Scenes/" + string(argv[1]);
  simulation->loadScene(scene);


  simulation->simulate();
}