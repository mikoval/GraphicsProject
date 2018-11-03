#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <Math/MathTools.h>
#include <Graphics/Constants.h>

class Camera {

protected:
	Vec3f pos;
	Vec3f dir;
	Vec3f up;
	Vec3f right;

	Vec3f worldUp;
	Vec3f target;

	float near;
	float far;
	float fov;

	float speed;

public:
	Camera();
	Camera(Vec3f pos, Vec3f dir, Vec3f up);

	Mat4x4 view();
	Mat4x4 projection();
	void transform(Mat4x4 transform);
	virtual void setPosition(Vec3f position);
	void setAxis();

	virtual void moveForward();
	virtual void moveBack();
	virtual void moveLeft();
	virtual void moveRight();
	virtual void turn(float xoffset, float yoffset);
	
	virtual void zoom(float yoffset);

	virtual void print();

	void lookAt(Vec3f target);


};

#endif