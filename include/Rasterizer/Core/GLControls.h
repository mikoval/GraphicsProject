#ifndef GL_CONTROLS_H
#define GL_CONTROLS_H

#include <Rasterizer/Core/glContextUtil.h>

static inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS || action == GLFW_RELEASE){
		inputManager.keyInput(key, action == GLFW_PRESS);
	}

}

static inline void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	inputManager.scrollInput(yoffset);
}

static inline void mouse_movement_callback(GLFWwindow* window, double xpos, double ypos)
{
	inputManager.mouseMovement(xpos, ypos);
}  
static inline void mouse_click_callback(GLFWwindow* window, int button, int action, int mods)
{
	inputManager.mouseClick(button, action);
}  

void BindControls() {
	glSetKeyCallback(key_callback);
	glSetScrollCallback(scroll_callback);
	glSetMouseMovementCallback(mouse_movement_callback);
	glSetMouseClickCallback(mouse_click_callback);

}


#endif