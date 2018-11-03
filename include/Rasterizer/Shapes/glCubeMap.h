#ifndef GL_CUBE_MAP_H
#define GL_CUBE_MAP_H

#include <iostream>
#include <Graphics/Renderable.h>
#include <Materials/Materials.h>
#include <Shapes/glObject.h>

class glCubeMap : public glObject {

public:
	glCubeMap();

	void draw();
	void draw(Mat4x4 transform);
	void print();
	void loadCubeMap(string path);
private:
	glModel *model;
};

#endif