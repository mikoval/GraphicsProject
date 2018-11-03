#ifndef GL_MESH_OBJECT_H
#define GL_MESH_OBJECT_H

#include <iostream>
#include <Graphics/Renderable.h>
#include <Materials/Materials.h>
#include <Shapes/glObject.h>


class glMeshObject : public glObject {

public:
	glMeshObject();

	void draw();
	void draw(Mat4x4 transform);
	void drawShadow();
	void drawShadow(Mat4x4 transform);
	void print();
	void transform(Mat4x4 m);
	void loadModel(string path);
private:
	glModel *model;

	unsigned int mesh_size;
};

#endif