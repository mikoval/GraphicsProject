#include <TexturePrograms/glTextureDisplayProgram.h>
#include <Core/Base.h>

glTextureDisplayProgram::glTextureDisplayProgram(){
	program = shaders.LoadShader("DisplayImageShader");

	quad = models.LoadModel("assets/Models/Quad.obj");
}
void glTextureDisplayProgram::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(*program);

	GLuint texture_u = glGetUniformLocation (*program, "texture");
	glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, *texture);
	glUniform1i(texture_u, 0);

	quad->draw();

}

void glTextureDisplayProgram::setTexture(GLuint *texture){
	this->texture = texture;
}
void glTextureDisplayProgram::setProgram(GLuint *program){
	this->program = program;
}
