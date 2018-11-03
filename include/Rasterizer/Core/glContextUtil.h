#ifndef GL_CONTEXT_UTIL_H
#define GL_CONTEXT_UTIL_H

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <Graphics/Constants.h>
#include <Controls/InputManager.h>

extern int WINDOW_WIDTH, WINDOW_HEIGHT;

int InitGLContext();

void CloseGLContext();

bool glRunning();

bool Display();

bool Poll();

void glNoCursor();

void glSetKeyCallback(GLFWkeyfun func);
void glSetScrollCallback(GLFWscrollfun func);
void glSetMouseCallback(GLFWcursorposfun func);
void glSetMouseMovementCallback(GLFWcursorposfun func);
void glSetMouseClickCallback(GLFWmousebuttonfun  func);

void bindInputManager(InputManager *);

#endif