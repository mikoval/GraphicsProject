#ifndef PONG_BRICK_H
#define PONG_BRICK_H

#include <Math/MathTools.h>

class PongBrick {

#define PONG_NONE  -1
#define PONG_WALL  0
#define PONG_RED   1
#define PONG_GREEN 2
#define PONG_BLUE  3



private:
	

public:
	PongBrick(Vec3f position, float width, float height, int health);
	Vec3f position;
	float width;
	float height;
	int health;
	int points;
	int type;
	bool processHit(int &points);
};

#endif