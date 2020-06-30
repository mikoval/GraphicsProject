#ifndef PONG_BALL_H
#define PONG_BALL_H

#include <Math/MathTools.h>

class PongBall {

private:
	

public:
	PongBall(Vec3f position, Vec3f velocity);
	Vec3f position;
	Vec3f velocity;
	float size;
	float speed;
};

#endif