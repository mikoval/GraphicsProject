#ifndef GL_ASTROID_RING_H
#define GL_ASTROID_RING_H

#include <iostream>
#include <Graphics/Renderable.h>
#include <Materials/Materials.h>
#include <Shapes/glObject.h>


class glAstroidRing : public glObject {

public:
	glAstroidRing(float radius, int count);

	void draw();
	void draw(Mat4x4 transform);
	void print();
private:
	float radius;
	int count;
	Mat4x4 *positions;
	glModel *model;

	void loadModel(string path);
	void genModels(float radius, int count);

	unsigned int mesh_size;
};

#endif