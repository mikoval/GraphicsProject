#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include <Math/MathTools.h>
#include <Materials/Materials.h>
#include <Shapes/glModel.h>


class glObject {

public:
	virtual void draw();
	virtual void draw(Mat4x4 trans);

	virtual void drawShadow();
	virtual void drawShadow(Mat4x4 trans);

	virtual void print();

	void setPosition(Vec3f pos);
	void setOrientation(Mat4x4 rotation);
	void setScale(Vec3f scale);
	void applyScale(Vec3f s);
	
	void setMaterial(Material *material);
	void setProgram(GLuint *program);

protected:
	Vec3f position = Vec3f();
	Vec3f scale = Vec3f(1, 1, 1);
	Mat4x4 rotation;
	GLuint *program;
	GLuint *shadowProgram;

	Material *material = nullptr;
};

#endif