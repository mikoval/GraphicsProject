#ifndef GL_BASE_H
#define GL_BASE_H

#include <Rasterizer/Core/Renderer.h>
#include <Rasterizer/Core/glContextUtil.h>
#include <Graphics/Constants.h>
#include <Shapes/ModelManager.h>
#include <Shaders/ShaderManager.h>
#include <Materials/MaterialManager.h>
#include <Controls/InputManager.h>

extern glRenderer renderer;
extern ModelManager models;
extern ShaderManager shaders;
extern MaterialManager materials;
extern float deltaTime;

#endif
