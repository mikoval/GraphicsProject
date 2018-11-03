#include <Cameras/OrbitalCamera.h>   
#include <Rasterizer/Core/Base.h>

OrbitalCamera::OrbitalCamera() : Camera() {
	lookAt(Vec3f(0.0, 0.0, 0.0));
	cout << "SETTING LOOKAT!!! ------ 1" << endl;
}

OrbitalCamera::OrbitalCamera(Vec3f pos, Vec3f forward, Vec3f up) : Camera(pos, forward, up) {
	lookAt(Vec3f(0.0, 0.0, 0.0));
	cout << "SETTING LOOKAT!!! ------ 2" << endl;

}

void OrbitalCamera::moveForward(){
	if(dir.dot(worldUp) < -0.95) { return; }

	pos = Rotate(right, Vec3f(), speed * deltaTime) * pos;
	lookAt(target);
}

void OrbitalCamera::moveRight(){
	pos = RotateY(-1 * speed * deltaTime) * pos;
	lookAt(target);
}
void OrbitalCamera::moveLeft(){
	pos = RotateY(speed * deltaTime) * pos;
	lookAt(target);
}
void OrbitalCamera::moveBack(){
	if(dir.dot(worldUp) > 0.95) { return; }
	pos = Rotate(right, Vec3f(), -speed * deltaTime) * pos;
	lookAt(target);
}

void OrbitalCamera::zoom(float delta){
	float dist = (target - pos).length();
	if(dist < 1 && delta < 0.0) { return; }
	dist += dist * delta * 0.01;

	pos = target + (pos - target).norm() * dist;

}

void OrbitalCamera::setPosition(Vec3f p){
	pos = p;
	lookAt(target);
}