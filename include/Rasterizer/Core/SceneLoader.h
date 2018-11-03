#ifndef GL_SCENE_LOADER_H
#define GL_SCENE_LOADER_H

#include <Shapes/glObjectsAll.h>
#include <Lights/PointLight.h>

#include <Graphics/Camera.h>
#include <Simulator/glSimulation.h>
#include <vector>

void glLoadScene(string file, glSimulation *);

#endif