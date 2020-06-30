#include <Pong/PongBall.h>

PongBall::PongBall(Vec3f position, Vec3f velocity){
	this->position = position;
	this->velocity = velocity;
	this->size = 0.5;
	this->speed = 10;
}