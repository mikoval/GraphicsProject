#ifndef PONG_PLAYER_H
#define PONG_PLAYER_H

#include <Math/MathTools.h>

class PongPlayer {

private:
	

public:
	PongPlayer(Vec3f position_input);
	Vec3f position;
	float width;
	float height;

	int lives;

	float getWidth();
	float getHeight();
};

#endif