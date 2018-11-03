#ifndef GL_SIMULATION_H
#define GL_SIMULATION_H

#include <Simulator/Simulation.h>
#include <vector>
#include <Shapes/glObject.h>
#include <Graphics/Camera.h>
#include <Lights/PointLight.h>
#include <Lights/DirectionalLight.h>
class glSimulation : public Simulation {

private:
	vector<glObject *> objects;
	vector<PointLight *> pointLights;
	vector<DirectionalLight *> directionalLights;
	Camera *camera;
	//glRenderer renderer();

	void updateShadows();

public:
	glSimulation();
	void simulate();
	void setInputManager(InputManager *im);
	void loadScene(string scene);
	void draw();

	void drawImage();
	void postProcess();
	void display();

	void setCamera(Camera *camera);
	void addObject(glObject *);
	void addLight(PointLight *);
	void addLight(DirectionalLight *);

};

#endif