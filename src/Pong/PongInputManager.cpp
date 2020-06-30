#include <Pong/PongInputManager.h>

PongInputManager::PongInputManager(PongGame *game){
	this->game = game;
}




void PongInputManager::processInput(){
	if(w){  game->processUp(); }
	if(a){  game->processLeft(); }
	if(s){  game->processDown(); }
	if(d){  game->processRight(); }
} 