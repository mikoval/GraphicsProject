#ifndef LIGHT_H
#define LIGHT_H

#include <Math/MathTools.h>


class Light {
private:
	Vec3f ambient;
	Vec3f diffuse;
	Vec3f specular;

public:
	void setAmbient(Vec3f c);
	void setDiffuse(Vec3f c);
	void setSpecular(Vec3f c);
	Vec3f getAmbient();
	Vec3f getDiffuse();
	Vec3f getSpecular();
};


#endif