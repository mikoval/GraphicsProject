#ifndef GL_SPHERE_H
#define GL_SPHERE_H

#include <iostream>
#include <Graphics/Renderable.h>
#include <Materials/Materials.h>
#include <Shapes/glObject.h>


class glSphere : public glObject {

public:
	glSphere();

	void draw();
	void draw(Mat4x4 transform);
	void drawShadow();
	void drawShadow(Mat4x4 transform);
	void print();
	void transform(Mat4x4 m);
private:
	glModel *model;

	unsigned int mesh_size;
};

#endif