#ifndef PONG_GAME_RENDERER_H
#define PONG_GAME_RENDERER_H

#include <Shapes/glObjectsAll.h>
#include <Cameras/glCamerasAll.h>
#include <vector>
#include <Math/MathTools.h>
#include <Core/Base.h>
#include <Pong/PongInputManager.h>
#include <Text/text.h>

#define PONG_WALL 0
#define PONG_BRICK_1 1
#define PONG_BACKGROUND_PLANE 2

#define PONG_2D 0
#define PONG_3D 1

class PongGameRenderer {

private:
	int render_mode;

	glObject *playerRenderable;
	glObject *ballRenderable;
	map<int, glObject*> objects; 
	Camera *camera;
	GLuint *program;

	TextRenderer *textRenderer;

	void updateShadows();

	vector<glObject *> generateMap();

	void setConfig();

public:
	PongGameRenderer();

	vector<PointLight *> pointLights;
	vector<DirectionalLight *> directionalLights;

	void draw();
};

#endif