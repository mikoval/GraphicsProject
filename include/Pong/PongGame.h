#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <Pong/PongGame.h>
#include <Pong/PongPlayer.h>
#include <Pong/PongBall.h>
#include <Pong/PongBrick.h>

#include <Math/MathTools.h>
#include <vector>

class PongGame {

#define LEFT -1
#define RIGHT 1
#define NONE 0
private:
	PongPlayer *player;
	PongBall *ball;
	float time;
	int width;
	int height;
	int score;

	int direction;
	float speed;

	vector<PongBrick> walls;

	void loadMap();

	Vec3f getNearestPoint(PongPlayer *player, PongBall *ball);
	Vec3f getNearestPoint(PongBrick *brick, PongBall *ball);
	void processCollisions(float dt);
	float getDistance(PongPlayer *player, PongBall *ball);
	float getDistance(PongBrick *brick, PongBall *ball);
	Vec3f reflect(Vec3f vec, Vec3f norm);
public:
	PongGame();
	void update(float dt);
	PongPlayer *getPlayer();
	PongBall *getBall();

	void getDimensions(float &width, float &height);

	void processUp();
	void processLeft();
	void processDown();
	void processRight();

	vector<PongBrick *> getBricks();

	int getScore();

};

#endif