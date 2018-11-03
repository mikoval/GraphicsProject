#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <iostream>
#include <Math/MathTools.h>
#include <Rasterizer/Shaders/Shaders.h>

using namespace std;

class Renderable {

public:
	virtual void draw() = 0;
	virtual void print() = 0;
	unsigned int mesh_size;
};

#endif