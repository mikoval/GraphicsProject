
#include <Controls/InputManager.h>

#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

InputManager::InputManager(){
    firstMouse = true;
    scroll = 0;
    mouseDown = false;
}

void InputManager::keyInput(unsigned int key, bool pressed){
	if(key == GLFW_KEY_W) { w = pressed; }
	else if(key == GLFW_KEY_A) { a = pressed; }
	else if(key == GLFW_KEY_S) { s = pressed; }
	else if(key == GLFW_KEY_D) { d = pressed; }

	else { cout << "unregistered key: " << key << endl; }
}
void InputManager::scrollInput(float yOffset){
	scroll = yOffset;
}

void InputManager::mouseMovement(float xpos, float ypos) {
	if(firstMouse)
    {
        mouseLastX = xpos;
        mouseLastY = ypos;
        mouseX = xpos;
    	mouseY = ypos;
        firstMouse = false;
    } else {
    	mouseX = xpos;
    	mouseY = ypos;
    }
}


void InputManager::mouseClick(int button, int action) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
    	if(action == GLFW_PRESS){
    		mouseDown = true;
    		firstMouse = true;
    		mouseLastX = mouseX;
    		mouseLastY = mouseY;
    	} else if (action == GLFW_RELEASE){
			mouseDown = false;
    	}
    }
}


void InputManager::processInput(){
	bool key = false;
	if(w){ cout << "W "; key = true; }
	if(a){ cout << "A "; key = true; }
	if(s){ cout << "S "; key = true; }
	if(d){ cout << "D "; key = true; }
	if(key){ cout << endl; }

	if(scroll){
		cout << "SCROLL: " << scroll <<endl;
		scroll = 0;
	}

	if(mouseDown) {
		float xoffset = mouseX - mouseLastX;
		float yoffset = mouseY - mouseLastY;
		mouseLastX = mouseX;
		mouseLastY = mouseY;
	}
}

void InputManager::setCamera(Camera *cam){
	camera = cam;
}

