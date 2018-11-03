#include <Graphics/Camera.h>   
#include <Rasterizer/Core/Base.h>
#include <Math/Mat4x4.h>

Camera::Camera() : Camera(Vec3f(),  Vec3f(0.0, 0.0, 1.0), Vec3f(0.0, 1.0, 0.0)) {
}

Camera::Camera(Vec3f pos, Vec3f forward, Vec3f up){
	this->pos = pos;

	this->dir = forward;
	this->worldUp = up;

	this->near = 0.1;
	this->far = 1000;

	this->fov = 45.0; /* 45° */

	this->speed = 3.0;

	this->right = cross(worldUp, dir).norm();
	this->up = cross(dir, right).norm();
}

void Camera::transform(Mat4x4 transform){
	pos = transform * pos;
}

void Camera::setPosition(Vec3f p){
	pos = p;
		cout << "setting normal camera position" << endl;

}

Mat4x4 Camera::view(){
	Mat4x4 m = Mat4x4();

	m.m[0][0] = right.x;
	m.m[1][0] = right.y;
	m.m[2][0] = right.z;

	m.m[0][1] = up.x;
	m.m[1][1] = up.y;
	m.m[2][1] = up.z;

	m.m[0][2] = dir.x;
	m.m[1][2] = dir.y;
	m.m[2][2] = dir.z;

	m.m[0][3] = pos.x;
	m.m[1][3] = pos.y;
	m.m[2][3] = pos.z;

	return m.inverse();
}

Mat4x4 Camera::projection(){
	return PerspectiveProjection(fov, near, far, ASPECT);
	//return OrthographicProjection(-10, 10, 10, -10, near, far);
}

void Camera::moveForward(){

}

void Camera::moveRight(){

}
void Camera::moveLeft(){

}
void Camera::moveBack(){

}

void Camera::turn(float xoffset, float yoffset){

}

void Camera::zoom(float delta){
}

void Camera::print(){
	cout << "camera object" << endl;
}

void Camera::lookAt(Vec3f target){
	dir = (target - pos).norm();
	setAxis();
}

void Camera::setAxis(){
	right = cross(worldUp, dir).norm();
	up = cross(dir, right).norm();
}