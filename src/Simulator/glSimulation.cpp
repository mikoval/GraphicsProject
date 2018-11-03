#include <Simulator/glSimulation.h>
#include <Core/glContextUtil.h>
#include <Controls/Controls.h>
#include <Core/SceneLoader.h>
#include <Core/Base.h>
#include <Cameras/OrbitalCamera.h>
#include <Controls/CameraInputManager.h>
#include <Utils/FBOUtils.h>
#include <TexturePrograms/glTextureDisplayProgram.h>
#include <TexturePrograms/glTextureBlurProgram.h>

const double maxFPS = 60.0;
const double maxPeriod = 1.0 / maxFPS;

static FBO fbo;
static FBO fbo2;


glTextureDisplayProgram *textureDisplayer;
glTextureBlurProgram *textureBlurrer;

static inline void SwapBuffers(FBO a, FBO b){
	FBO tmp = a;
	a = b;
	b = tmp;
}

glSimulation::glSimulation() {
	InitGLContext();
	initMaterials();
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void glSimulation::simulate() {
	// Enable blending
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	fbo = GenerateFBO(WIDTH, HEIGHT);
	fbo2 = GenerateFBO(WIDTH, HEIGHT);

	textureDisplayer = new glTextureDisplayProgram();
	textureBlurrer = new glTextureBlurProgram();


	cout << "error: " <<  glGetError() << endl;
	double lastTime = 0.0;

	int framecount = 0;
	double startTime =  glfwGetTime();
	while (glRunning())
	{
		double time = glfwGetTime();

		deltaTime = time - lastTime;
	
		if(time-startTime > 5 ){
			cout << "FPS: " << framecount << endl;
			startTime = time;
			framecount = 0;
		}
		
		if( deltaTime >= maxPeriod ) {
			framecount++;

		    lastTime = time;
		    
		    inputManager->processInput();

		    draw();

		    Display();

		    Poll();

		}

	}
}

void glSimulation::updateShadows(){
	glCullFace(GL_FRONT);

	for(int i = 0; i < directionalLights.size(); i++){
		directionalLights[i]->updateShadows();

		for(int i = 0; i < objects.size(); i++){
			objects[i]->drawShadow();
		}

	}
	glCullFace(GL_BACK);
	
}

void glSimulation::drawImage(){

	updateShadows();

	glViewport(0, 0, WIDTH, HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo.fbo);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer.setProj(camera->projection());
    renderer.setView(camera->view());
	for(int i = 0; i < objects.size(); i++){
		objects[i]->draw();
	}

	for(int i = 0; i < pointLights.size(); i++){
		pointLights[i]->draw();
	}
}

void glSimulation::postProcess(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	textureBlurrer->setTexture(&fbo.texture);
	textureBlurrer->draw();

	SwapBuffers(fbo, fbo2);
}

void glSimulation::display(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	textureDisplayer->setTexture(&fbo.texture);
	textureDisplayer->draw();
}

void glSimulation::draw(){

	drawImage();

	postProcess();

	display();

}

void glSimulation::setInputManager(InputManager *im) {

	inputManager = im;
	BindControls(inputManager);
}

void glSimulation::loadScene(string scene){
	glLoadScene(scene, this);

    CameraInputManager *im = new CameraInputManager(camera);
    setInputManager(im);
}


void glSimulation::addLight(DirectionalLight *light) {
	directionalLights.push_back(light);
}
void glSimulation::addLight(PointLight *light) {
	pointLights.push_back(light);
}
void glSimulation::addObject(glObject *obj) {
	objects.push_back(obj);
}

void glSimulation::setCamera(Camera *cam) {
	camera = cam;
}