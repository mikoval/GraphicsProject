#ifndef CAMERA_INPUT_MANAGER_H
#define CAMERA_INPUT_MANAGER_H

#include <Graphics/Camera.h>
#include <Controls/InputManager.h>

class CameraInputManager : public InputManager {

public:
	CameraInputManager(Camera *cam);

	void processInput();
};

#endif