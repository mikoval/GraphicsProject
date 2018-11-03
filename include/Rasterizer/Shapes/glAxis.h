#ifndef GL_AXIS_H
#define GL_AXIS_H

#include <iostream>
#include <Graphics/Renderable.h>
#include <Materials/Materials.h>
#include <Shapes/glObject.h>

class glAxis : public glObject {

public:
	glAxis();

	void draw();
	void draw(Mat4x4 transform);
	void print();
	void transform(Mat4x4 m);

private:
	GLuint *program;
	glModel *model;
};

GLuint BasicShader();

#endif