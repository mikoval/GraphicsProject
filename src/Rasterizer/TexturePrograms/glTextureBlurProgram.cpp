#include <TexturePrograms/glTextureBlurProgram.h>
#include <Core/Base.h>

glTextureBlurProgram::glTextureBlurProgram(){
	program = shaders.LoadShader("BlurImageShader");

	quad = models.LoadModel("assets/Models/Quad.obj");
}
void glTextureBlurProgram::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer.setProgram(*program);

	GLuint texture_u = glGetUniformLocation (*program, "texture");
	glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, *texture);
	glUniform1i(texture_u, 0);

	GLuint res_u = glGetUniformLocation (*program, "res");
	glUniform2f(res_u, WIDTH, HEIGHT);

	quad->draw();
}

void glTextureBlurProgram::setTexture(GLuint *texture){
	this->texture = texture;
}
void glTextureBlurProgram::setProgram(GLuint *program){
	this->program = program;
}
