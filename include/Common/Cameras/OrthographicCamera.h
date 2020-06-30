#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include <iostream>

#include <Math/MathTools.h>
#include <Graphics/Constants.h>

#include <Graphics/Camera.h>

class OrthographicCamera : public Camera {
private:
	float left;
    float right;
    float top;
    float bottom;
    float near;
    float far;

public:
	OrthographicCamera(float left, float right, float top,
                       float bottom, float near, float far);

	Mat4x4 projection();
};

#endif
