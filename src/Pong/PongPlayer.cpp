#include <Pong/PongPlayer.h>

PongPlayer::PongPlayer(Vec3f position_input){
	position = position_input;
	width = 3.0;
	height = 1.0;
	lives = 3;
}

float PongPlayer::getWidth() {
	return width;
}
float PongPlayer::getHeight() {
	return height;
}