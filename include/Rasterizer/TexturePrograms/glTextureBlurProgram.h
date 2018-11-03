#ifndef GL_TEXTURE_BLUR_PROGRAM_H
#define GL_TEXTURE_BLUR_PROGRAM_H

#include <Core/glContextUtil.h>
#include <Shapes/glModel.h>

class glTextureBlurProgram {
private:
	GLuint *texture;
	GLuint *program;
	glModel *quad;
public:
	glTextureBlurProgram();
	void draw();
	void setTexture(GLuint *texture);
	void setProgram(GLuint *program);
};

#endif