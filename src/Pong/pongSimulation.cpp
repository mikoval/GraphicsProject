#include <Pong/pongSimulation.h>
#include <Core/glContextUtil.h>
#include <Controls/Controls.h>
#include <Core/SceneLoader.h>
#include <Core/Base.h>
#include <Text/text.h>


const double maxFPS = 60.0;
const double maxPeriod = 1.0 / maxFPS;


pongSimulation::pongSimulation(int RENDER_MODE) {

	this->render_mode = RENDER_MODE;

	InitGLContext();
	initMaterials();

	

	glClearColor(0.0, 0.0, 0.0, 1.0);
	game = new PongGame();
	gameRenderer = new PongGameRenderer();
	gameRenderer->setRenderMode(PONG_2D);
	gameRenderer->setGame(game);


	textRenderer = new TextRenderer(ARIEL_FONT, shaders.LoadShader("TextShader"));

	setConfig();


	playerRenderable = new glCube();
	playerRenderable->setScale(Vec3f(0.5, 0.5, 0.5));

	ballRenderable = new glSphere();
	ballRenderable->setScale(Vec3f(0.5, 0.5, 0.5));

	generateMap();

    Material *player_material = materials.LoadMaterial("CyanPlastic");
    Material *ball_material = materials.LoadMaterial("Emerald");

    playerRenderable->setProgram(program);
    ballRenderable->setProgram(program);

    playerRenderable->setMaterial(player_material);
    ballRenderable->setMaterial(ball_material);


    inputManager = new PongInputManager(game);
    BindControls(inputManager);
}

void pongSimulation::simulate() {
	printf("SIMULATING \n");
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	double lastTime = 0.0;

	int framecount = 0;
	double startTime =  glfwGetTime();
	while (glRunning())
	{
		double time = glfwGetTime();

		deltaTime = time - lastTime;
	
		if(time-startTime > 10 ){
			cout << "FPS: " << framecount << endl;
			startTime = time;
			framecount = 0;
		}
		
		if( deltaTime >= maxPeriod ) {
			framecount++;

		    lastTime = time;


		    inputManager->processInput();

		    game->update(deltaTime);

		    {
				PongPlayer *player = game->getPlayer();
				PongBall *ball = game->getBall();
				playerRenderable->setPosition(player->position);
				playerRenderable->setScale(Vec3f(0.5 * player->width, 0.5, 0.5));
				ballRenderable->setPosition(ball->position);
				ballRenderable->setScale(Vec3f(ball->size, ball->size, ball->size));
			}

			updateShadows();
		    display();
		    Display();
		    Poll();
		}

	}
}

void pongSimulation::display(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//glViewport(0, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

	float width, height;
	game->getDimensions(width, height);

	if(render_mode == PONG_2D) {
		float vHeight = WINDOW_HEIGHT * 0.9;
		float vWidth = vHeight * width / height; 
		glViewport(WINDOW_WIDTH / 2 - vWidth / 2, 0 ,   vWidth,  vHeight);
	} else if (render_mode == PONG_3D){
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	}
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{
		glEnable(GL_DEPTH_TEST);

		renderer.setProj(camera->projection());
	    renderer.setView(camera->view());

		draw();
	}

	{
		float sx = 2.0 /WINDOW_WIDTH;
		float sy = 2.0 /WINDOW_HEIGHT;

		string score = "SCORE: " + std::to_string(game->getScore());
		string lives = "LIVES: " + std::to_string(game->getPlayer()->lives);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glDisable(GL_DEPTH_TEST);
		textRenderer->drawText(score.data(),
						1 - 500 * sx,   1 - 80 * sy,    sx, sy);
		textRenderer->drawText(lives.data(),
						-1 + 32 * sx,   1 - 80 * sy,    sx, sy);
	}
}

void pongSimulation::draw(){
	    Material *red_material = materials.LoadMaterial("RedPhong");
	    Material *green_material = materials.LoadMaterial("GreenPhong");
    	Material *blue_material = materials.LoadMaterial("BluePhong");
    	Material *black_tile_material = materials.LoadMaterial("BlackTileSmall");


		playerRenderable->draw();
		ballRenderable->draw();

		objects.find(PONG_BACKGROUND_PLANE)->second->draw();

		vector<PongBrick *> walls = game->getBricks();


		glObject *wall = objects.find(PONG_BRICK_1)->second;
		for(int i = 0; i < walls.size(); i++){
			wall->setPosition(walls[i]->position);
			if(walls[i]->type == PONG_RED){
				wall->setMaterial(red_material);
			} else if(walls[i]->type == PONG_GREEN){
				wall->setMaterial(green_material);
			} else if(walls[i]->type == PONG_BLUE){
				wall->setMaterial(blue_material);
			} else if(walls[i]->type == PONG_WALL){
				wall->setMaterial(black_tile_material);
			}
			//printf("PRINTING WALL DIMENSIONS : %f %f \n", walls[i]->width, walls[i]->height);
			wall->setScale(0.5 * Vec3f(walls[i]->width, walls[i]->height, 1));
			
			wall->draw();
		}
}
vector<glObject *> pongSimulation::generateMap(){

	vector<glObject *> ret;
	vector<PongBrick *> walls = game->getBricks();

	float width, height;

	game->getDimensions(width, height);


    Material *red_material = materials.LoadMaterial("Red");

    Material *white_material = materials.LoadMaterial("White");


    glMeshObject *plane = new glMeshObject();
    plane->loadModel("assets/Models/Quad.obj");
	plane->setOrientation(RotateX(radians(180)));
	plane->setPosition(Vec3f(0.0, 0.0, 2.55));
	plane->setMaterial(white_material);
	plane->setProgram(program);


	plane->applyScale(Vec3f(width, height, 1));
	objects.insert({PONG_BACKGROUND_PLANE, plane});


		glObject *obj = new glCube();
	    obj->setMaterial(red_material);
	    obj->setPosition(Vec3f(0.0, 0.0, 0.0));
		obj->setProgram(program);
		obj->setScale(Vec3f(0.5, 0.5, 0.5));

		objects.insert({PONG_BRICK_1, obj});

	return ret;
}


void pongSimulation::updateShadows(){
	glCullFace(GL_FRONT);

	for(int i = 0; i < directionalLights.size(); i++){
		directionalLights[i]->updateShadows();

		draw();

	}
	glCullFace(GL_BACK);
	
}

void pongSimulation::setConfig(){
	float width, height;
	game->getDimensions(width, height);


	if(render_mode == PONG_2D) {
		camera = new OrthographicCamera(-width/2, width/2, height/2, -height/2, .1, 30);
		program = shaders.LoadShader("ColorShader");
	} else if (render_mode == PONG_3D){
		camera = new FreeCamera();
		camera->setPosition(Vec3f(0.0, -25.0, -15.0));
		//camera->setPosition(Vec3f(0.0, 0.0, 50.0));

		camera->lookAt(Vec3f(0.0, -5.0, 0.0));
		camera->lookAt(Vec3f(0.0, 0.0, 0.0));
		program = shaders.LoadShader("PhongShader");


		{
			DirectionalLight *light = new DirectionalLight();
			light->setDirection(Vec3f(0.4, -0.3, 1.0));
			light->setAmbient(Vec3f(1.0, 1.0, 1.0));
			light->setDiffuse(Vec3f(1.0, 1.0, 1.0));
			light->setSpecular(Vec3f(1.0, 1.0, 1.0));

			
			light->enableShadows(2, -20, 20, -20, 20, 0.1, 20);

			directionalLights.push_back(light);
		}

	}

}