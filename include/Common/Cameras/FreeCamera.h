#ifndef FREE_CAMERA_H
#define FREE_CAMERA_H

#include <iostream>

#include <Math/MathTools.h>
#include <Graphics/Constants.h>

#include <Graphics/Camera.h>

class FreeCamera : public Camera {

private:
	float yaw, pitch, roll;
public:
	FreeCamera();
	FreeCamera(Vec3f pos, Vec3f dir, Vec3f up);

	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();
	
	void zoom(float yoffset);
	void turn(float xoffset, float yoffset);
	void setAngles();
};

#endif