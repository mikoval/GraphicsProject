#ifndef PONG_INPUT_MANAGER_H
#define PONG_INPUT_MANAGER_H

#include <Pong/PongGame.h>
#include <Controls/InputManager.h>

class PongInputManager : public InputManager {
private:
	PongGame *game;
public:
	PongInputManager(PongGame *game);

	void processInput();
};

#endif