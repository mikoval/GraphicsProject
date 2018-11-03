#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <Math/MathTools.h>
#include <Graphics/Light.h>
#include <Utils/FBOUtils.h>


class DirectionalLight : public Light {

private:
	Vec3f direction;

	bool shadows = false;

	FBO shadowBuffer;

	float shadow_x1;
	float shadow_x2;
	float shadow_y1;
	float shadow_y2;
	float shadow_near;
	float shadow_far;
	float shadow_multiplier;




public:
	DirectionalLight();

	Vec3f getDirection();

	void setDirection(Vec3f p);

	void print();

	void enableShadows(float multiplier, float shadow_x1, float shadow_x2, float shadow_y1, float shadow_y2, float near,  float far);

	void updateShadows();



};


#endif