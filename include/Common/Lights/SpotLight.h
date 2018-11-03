#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <Math/MathTools.h>
#include <Core/Light.h>
#include <Core/Renderable.h>

class PointLight : public Light , public Renderable{

private:
	Vec3f position;

	Vec3f ambient;
	Vec3f diffuse;
	Vec3f specular;

	float size;
	
	GLuint program;
	GLuint vao;

	Mat4x4 model;

	void setModel();

public:
	PointLight();

	void draw();

	Vec3f getPosition();
	Vec3f getAmbient();
	Vec3f getDiffuse();
	Vec3f getSpecular();

	void setPosition(Vec3f p);

	void print();

	void applyTransform(Mat4x4 m);

};


#endif