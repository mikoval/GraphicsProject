#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <Math/MathTools.h>
#include <Graphics/Light.h>
#include <Graphics/Renderable.h>
#include <Shapes/glModel.h>


class PointLight : public Light , public Renderable{

private:
	Vec3f position;

	Vec3f ambient;
	Vec3f diffuse;
	Vec3f specular;
	Vec3f attenuation;

	float size;
	
	GLuint *program;
	GLuint vao;

	Mat4x4 trans;

	glModel *model;

	void setModel();

public:
	PointLight();

	void draw();

	Vec3f getPosition();
	Vec3f getAmbient();
	Vec3f getDiffuse();
	Vec3f getSpecular();
	Vec3f getAttenuation();

	void setPosition(Vec3f p);

	void print();

	void applyTransform(Mat4x4 m);

};


#endif