#ifndef GL_CUBE_H
#define GL_CUBE_H

#include <iostream>
#include <Graphics/Renderable.h>
#include <Materials/Materials.h>
#include <Shapes/glObject.h>

class glCube : public glObject {

public:
	glCube();

	void draw();
	void draw(Mat4x4 transform);
	void drawShadow();
	void drawShadow(Mat4x4 transform);
	void print();
	void transform(Mat4x4 m);

private:
	glModel *model;
};

#endif