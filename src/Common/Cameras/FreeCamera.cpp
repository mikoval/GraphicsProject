#include <Cameras/FreeCamera.h>   
#include <Rasterizer/Core/Base.h>

FreeCamera::FreeCamera() : Camera() {
	setAngles();
	glNoCursor();
	speed = 5;
}

FreeCamera::FreeCamera(Vec3f pos, Vec3f forward, Vec3f up) : Camera(pos, forward, up) {
	setAngles();
	glNoCursor();
	speed = 5;
}

void FreeCamera::moveForward(){
	pos = pos + speed * dir * deltaTime;
}

void FreeCamera::moveRight(){
	pos = pos - speed * right * deltaTime;
}

void FreeCamera::moveLeft(){
	pos = pos + speed * right * deltaTime;
}
void FreeCamera::moveBack(){
	pos = pos - speed * dir * deltaTime;
}

void FreeCamera::turn(float xoffset, float yoffset){
	yaw   += xoffset * .1;
    pitch += yoffset * .1;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

   	dir.x = cos(radians(yaw)) * cos(radians(pitch));
    dir.y = sin(radians(pitch));
    dir.z = sin(radians(yaw)) * cos(radians(pitch));

    Camera::setAxis();

}

void FreeCamera::setAngles(){
	pitch = degrees(asin(dir.y));
	yaw = degrees(asin(dir.z / cos(radians(pitch))));
	roll = 0;
	cout << "TURNING " << endl;
	turn(0.0, 0.0);
	cout << "TURNED " << endl;
}

void FreeCamera::zoom(float delta){
	if(fov >= 1 && fov <= 45){
	  	fov = fov - delta * .01f * speed;
	}
	if(fov <= 1){
		fov = 1;
	}

	if(fov >= 45){
		fov = 45;
	}


}