#include <Core/glContextUtil.h>
#include <iostream> 

using namespace std;

static GLFWwindow* window;

float deltaTime = 0;
int WINDOW_WIDTH, WINDOW_HEIGHT;

int InitGLContext() {
	/* Initialize the library */
	if ( !glfwInit() )
	{
		return 0;
	}


	#ifdef __APPLE__
	/* We need to explicitly ask for a 3.2 context on OS X */
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#endif

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow( WIDTH, HEIGHT, "Hello World", NULL, NULL );

	printf("CREATING WINDOW\n");
	if (!window)
	{
	 	glfwTerminate();
	 	return 0;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	//glEnable(GL_MULTISAMPLE);  
	//glfwWindowHint(GLFW_SAMPLES, 4);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

	printf("WINDOW SIZE: %d %d \n", WINDOW_WIDTH, WINDOW_HEIGHT);

	//glEnable(GL_FRAMEBUFFER_SRGB);
	return 1;

}

void CloseGLContext() {
	window = NULL;
	glfwTerminate();
}

bool glRunning(){
	if(glfwWindowShouldClose(window)){
	 	return false;
	} else {
		return true;
	}

}

bool Display(){
	glfwSwapBuffers(window);
	return true;
}

bool Poll(){
	glfwPollEvents();
	return true;
}

void glNoCursor() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void glSetKeyCallback(GLFWkeyfun func){
	glfwSetKeyCallback(window, func);
}

void glSetScrollCallback(GLFWscrollfun func){
	glfwSetScrollCallback(window, func);
}

void glSetMouseMovementCallback(GLFWcursorposfun func){
	glfwSetCursorPosCallback(window, func);
}
void glSetMouseClickCallback(GLFWmousebuttonfun  func){
	glfwSetMouseButtonCallback(window, func);
}
