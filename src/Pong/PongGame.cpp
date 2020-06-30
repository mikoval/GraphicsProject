#include <Pong/PongGame.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <fstream>

#define DEPTH 2
PongGame::PongGame() {
	
	time = 0.0;
	score = 0;



	speed = 20.0;

	loadMap();

	player = new PongPlayer(Vec3f(0.0, -height/2 + 0.5, DEPTH));

	ball = new PongBall(Vec3f(0.0, 0.0, DEPTH), Vec3f(-1.0, 1.0, 0.0));
}

void PongGame::update(float dt) {
	if(dt > 1.0 / 30.0 ) { 
		dt = 1.0 / 30.0;
	}

	time += dt;


	//player->position.x =  * sin(time);
	float maxDist = ((width - player->width - 2)/2.0 );

	player->position.x = player->position.x + direction * speed * dt; 
	if(player->position.x < -maxDist) {
		player->position.x = -maxDist;
	} else if(player->position.x > maxDist) {
		player->position.x = maxDist;
	}
	direction = NONE;
	processCollisions(dt);


	ball->position = ball->position + ball->velocity * dt * ball->speed;

	if(ball->position.y < -height/2 - 1.0) {
		player->lives--;
		ball->position.x = 0.0;
		ball->position.y = 0.0;
	}


}
void PongGame::processCollisions(float dt) {

	float CircleX = ball->position.x; float CircleY = ball->position.y;
	Vec3f dir(0.0, 0.0, 0.0);

	float minDist = 1000000;
	int minIndex = 0;

	for(int i = 0; i < walls.size(); i++){
		Vec3f nearestPoint = getNearestPoint(&walls[i], ball);
		float distX = CircleX - nearestPoint.x; 
		float distY = CircleY - nearestPoint.y;
		float dist = distX*distX + distY*distY;


		if(dist < ball->size * ball->size){
			if(dist < minDist){
				
				minDist = dist;
				minIndex = i;
				dir = Vec3f(ball->position.x - nearestPoint.x, ball->position.y - nearestPoint.y,0); 
				
			}
		}
	}
	if(dir.x != 0.0 || dir.y != 0.0){
		ball->velocity = reflect(ball->velocity, dir);
		int points = 0;
		if(walls[minIndex].processHit(points)){
			walls.erase(walls.begin() + minIndex);
		}
		score += points;
		if(points != 0){
			
			printf("SCORE: %d \n ", score);
		}
		
		
	}


	float dist = getDistance(player, ball);
}

float PongGame::getDistance(PongBrick *brick, PongBall *ball){


	float dist = 0.0;


	return dist;
}

float PongGame::getDistance(PongPlayer *player, PongBall *ball){
	float CircleX = ball->position.x; float CircleY = ball->position.y;
	Vec3f nearestPoint = getNearestPoint(player, ball);
	float distX = CircleX - nearestPoint.x; 
	float distY = CircleY - nearestPoint.y;

	float dist = distX*distX + distY*distY;
	

	if(dist < ball->size * ball->size){
		Vec3f dir = Vec3f(ball->position.x - nearestPoint.x, ball->position.y - nearestPoint.y,0); 
		ball->velocity = reflect(ball->velocity, dir);
	}

	return dist;
}

Vec3f PongGame::reflect(Vec3f vec, Vec3f norm){
	norm.normalize();
	float mag = vec.dot(norm);
	if(mag < 0){
		vec = vec - 2 * norm * mag;
	}
	

	return vec;
}

Vec3f PongGame::getNearestPoint(PongBrick *brick, PongBall *ball){
	float CircleX = ball->position.x; float CircleY = ball->position.y;
	float RectWidth = brick->width ;
	float RectHeight = brick->height;
	float RectX = brick->position.x - RectWidth / 2.0;
	float RectY = brick->position.y - RectHeight  / 2.0;



	float NearestX = max(RectX, min(CircleX, RectX + RectWidth));
	float NearestY = max(RectY, min(CircleY, RectY + RectHeight));
	//printf("NEAREST POINT : position: %f , left: %f, width: %f | %f %f \n" ,player->position.x, RectX, RectWidth, NearestX, NearestY);
	return Vec3f(NearestX, NearestY, 0.0);
}

Vec3f PongGame::getNearestPoint(PongPlayer *player, PongBall *ball){
	float CircleX = ball->position.x; float CircleY = ball->position.y;
	float RectWidth = player->width ;
	float RectHeight = player->height;
	float RectX = player->position.x - RectWidth / 2.0;
	float RectY = player->position.y - RectHeight  / 2.0;



	float NearestX = max(RectX, min(CircleX, RectX + RectWidth));
	float NearestY = max(RectY, min(CircleY, RectY + RectHeight));
	//printf("NEAREST POINT : position: %f , left: %f, width: %f | %f %f \n" ,player->position.x, RectX, RectWidth, NearestX, NearestY);
	return Vec3f(NearestX, NearestY, 0.0);
}

PongPlayer *PongGame::getPlayer() {
	return player;
}
PongBall *PongGame::getBall() {
	return ball;
}

vector<PongBrick *> PongGame::getBricks() {
	vector<PongBrick *> ret;
	for(int i = 0; i < walls.size(); i++){
		ret.push_back(&walls[i]);
	}
	return ret;	
}


void PongGame::loadMap(){

	string path("include/Pong/Map1.txt");


	FILE * file = fopen(path.data(), "r");

	if( file == NULL ){
		printf("Unable to open the file\n");
		return;
	}

	vector<string> lines;


	while( 1 ){
		char lineHeader[128];
		int res;
		// read the first word of the line


		res = fscanf(file, "%[^\n]\n", lineHeader);


		if (res == EOF){
			break;
		}

		string line(lineHeader);
		lines.push_back(line);
	}
	//for(int i = 0; i < 1; i++){

	float start_height = (lines.size() -1 ) / 2.0;

	width = (lines[0].length() + 1) / 2;
	height = lines.size();
	float lineDist = (width - 1.0)/2.0;
	for(int i = 0; i < lines.size(); i++){
		string line = lines[i];
		printf("LINE: %d : %s \n", i, line.data());
		
		float lineLength = line.length();
		
		int ind; float j;
		for(j = -lineDist, ind = 0; ind < lineLength; j++, ind++) {
			char c = line[ind];
			int type;
			if(c == 'x'){
				type = PONG_WALL;
			} else if (c == 'r') {
				type = PONG_RED;
			} else if (c == 'g') {
				type = PONG_GREEN;
			} else if (c == 'b') {
				type = PONG_BLUE;
			} else if (c == '|') {
				j--;
				type = PONG_NONE;
			} else if (c == ' ') {
				j--;
				type = PONG_NONE;
			}else {
				type = PONG_NONE;
			}

			if(line[ind] == 'x') {
				PongBrick wall(Vec3f(j, start_height - i, DEPTH), 1, 1, PONG_WALL);
				walls.push_back(wall);
			} else if(walls[walls.size() - 1].type == type && line[ind - 1] != '|') {
				walls[walls.size() - 1].width += 1;
				walls[walls.size() - 1].position.x += 0.5;
			} else if (type == PONG_NONE) {
			} else {
				PongBrick wall(Vec3f(j, start_height - i, DEPTH), 1, 1, type);
				walls.push_back(wall);
			}
			
		}
	}	
}

int PongGame::getScore(){
	return score;
}



void PongGame::getDimensions(float &width_i, float &height_i){
	width_i = width;
	height_i = height;
}

void PongGame::processUp(){
	printf("UP\n");
}
void PongGame::processLeft(){
	direction = LEFT;
}
void PongGame::processDown(){
	printf("DOWN\n");
}
void PongGame::processRight(){
	direction = RIGHT;
}