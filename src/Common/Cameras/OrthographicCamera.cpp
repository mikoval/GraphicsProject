#include <Cameras/OrthographicCamera.h>   
#include <Rasterizer/Core/Base.h>


OrthographicCamera::OrthographicCamera(float left, float right,
         float top, float bottom, float near, float far) : Camera() {
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
    this->near = near;
    this->far = far;
}

Mat4x4 OrthographicCamera::projection() {
	return OrthographicProjection(left, right, top, bottom, near, far);
}

