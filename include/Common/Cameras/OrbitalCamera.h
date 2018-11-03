#ifndef ORBITAL_CAMERA_H
#define ORBITAL_CAMERA_H

#include <iostream>

#include <Math/MathTools.h>
#include <Graphics/Constants.h>

#include <Graphics/Camera.h>

class OrbitalCamera : public Camera {

public:
	OrbitalCamera();
	OrbitalCamera(Vec3f pos, Vec3f dir, Vec3f up);

	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();

	void setPosition(Vec3f p);
	
	void zoom(float yoffset);

};

#endif