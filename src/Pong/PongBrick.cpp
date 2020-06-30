#include <Pong/PongBrick.h>

PongBrick::PongBrick(Vec3f position, float width, float height, int type){
	this->position = position;
	this->width = width;
	this->height = height;
	this->health = 1;
	if(type == PONG_WALL){
		this->health = -1;
	} else {
		this->points = 100;
		this->width *= 0.9;
		this->height *= 0.9;
	}
	this->type = type;
}

bool PongBrick::processHit(int &points){
	if(health == -1){
		return false;
	}
	health--;
	if(health == 0){
		points = this->points;
		return true;
	}
	return false;
}