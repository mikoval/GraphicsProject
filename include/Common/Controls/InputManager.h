#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Graphics/Camera.h>

class InputManager {

protected:
	bool w = 0, a = 0, s = 0, d = 0;

	bool firstMouse;
	float mouseX, mouseY, mouseLastX, mouseLastY;

	float scroll;

	bool mouseDown;

	Camera *camera;

public:
	InputManager();

	void keyInput(unsigned int input, bool pressed);
	void scrollInput(float yoffset);
	virtual void processInput();
	void mouseMovement(float xOffset, float yOffset);
	void mouseClick(int button, int action);
	void setCamera(Camera *camera);
};

#endif