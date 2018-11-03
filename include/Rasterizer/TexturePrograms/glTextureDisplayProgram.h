#ifndef GL_TEXTURE_DISPLAY_PROGRAM_H
#define GL_TEXTURE_DISPLAY_PROGRAM_H

#include <Core/glContextUtil.h>
#include <Shapes/glModel.h>

class glTextureDisplayProgram {
private:
	GLuint *texture;
	GLuint *program;
	glModel *quad;
public:
	glTextureDisplayProgram();
	void draw();
	void setTexture(GLuint *texture);
	void setProgram(GLuint *program);
};

#endif