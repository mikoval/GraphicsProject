
#include <Controls/CameraInputManager.h>

#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

CameraInputManager::CameraInputManager(Camera *cam){
    firstMouse = true;
    scroll = 0;
    mouseDown = false;
    camera = cam;
}

void CameraInputManager::processInput(){
	if(w){ camera->moveForward(); }
	if(a){ camera->moveRight(); }
	if(s){  camera->moveBack(); }
	if(d){  camera->moveLeft(); }

	if(scroll){
		camera->zoom(scroll);
		scroll = 0;
	}

	if(mouseDown) {
		float xoffset = mouseX - mouseLastX;
		float yoffset = mouseY - mouseLastY;
		mouseLastX = mouseX;
		mouseLastY = mouseY;
		camera->turn(-xoffset, -yoffset);

	}
}