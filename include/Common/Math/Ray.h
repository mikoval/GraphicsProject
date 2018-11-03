#ifndef RAY_H
#define RAY_H

#include <iostream>

#include <Math/MathTools.h>

class Ray {
	Vec3f o;
	Vec3f d;
public:
	Ray();
	Ray(Vec3f o, Vec3f d);

	Vec3f operator() (float t);

	void print();
};

#endif
