#include <Rasterizer/Core/Renderer.h>

glRenderer renderer = glRenderer();

void glRenderer::setVao(GLuint vao) {
		this->vao = vao;
		glBindVertexArray(vao);
	
}
void glRenderer::setProgram(GLuint program) {
		this->program = program;

		glUseProgram(program);

		setModel(model);

		setView(view);

		setProj(proj);

		setInverse(inverse);

		setMaterial(material);

		setDirectionalLight(scene.dirLight);
		setLights();

		setLightSpace(lightSpace);
		setShadowMap(shadowMap);
}
void glRenderer::setEye(Vec3f eye) {
		this->scene.eye = eye;
}
void glRenderer::setModel(Mat4x4 model) {
		this->model = model;
		GLuint model_u = glGetUniformLocation (program, "model");
		glUniformMatrix4fv(model_u, 1, GL_TRUE, &model.m[0][0]);
}
void glRenderer::setView(Mat4x4 view) {
		this->view = view;
		if(program){
			GLuint view_u = glGetUniformLocation (program, "view");
			glUniformMatrix4fv(view_u, 1, GL_TRUE, &view.m[0][0]);
		}
}
void glRenderer::setProj(Mat4x4 proj) {
		this->proj = proj;
		if(program){
			GLuint proj_u = glGetUniformLocation (program, "proj");
			glUniformMatrix4fv(proj_u, 1, GL_TRUE, &proj.m[0][0]);
		}

}

void glRenderer::setMaterial(Material *material_input){

	this->material = material_input;

	GLuint ambientTexture = 0;
	GLuint diffuseTexture  = 0;
	GLuint specularTexture  = 0;

	Vec3f ambient = Vec3f();
	Vec3f diffuse = Vec3f();
	Vec3f specular = Vec3f();

	if(material_input != NULL){
        ambientTexture  = material->diffuseTexture;
        diffuseTexture  = material->diffuseTexture;
        specularTexture  = material->specularTexture;

        ambient = material->ambient;
        diffuse = material->diffuse;
        specular = material->specular;
	}
	
	GLuint ambient_u = glGetUniformLocation (program, "material.ambient");
	GLuint diffuse_u = glGetUniformLocation (program, "material.diffuse");
	GLuint specular_u = glGetUniformLocation (program, "material.specular");

	GLuint ambientTexture_u = glGetUniformLocation (program, "material.ambientTexture");
	GLuint diffuseTexture_u = glGetUniformLocation (program, "material.diffuseTexture");
	GLuint specularTexture_u = glGetUniformLocation (program, "material.specularTexture");

	GLuint shiny_u = glGetUniformLocation (program, "material.shininess");


	glUniform3f(ambient_u, ambient.x, ambient.y, ambient.z);
	glUniform3f(diffuse_u, diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(specular_u, specular.x, specular.y, specular.z);



	glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, specularTexture);

//	cout << "ERROR: " << __LINE__ << " : " << glGetError() << endl;

	glUniform1i(ambientTexture_u, 0);
	glUniform1i(diffuseTexture_u, 0);
	glUniform1i(specularTexture_u, 1);


	float shininess = 0.25;
	glUniform1f(shiny_u, shininess);
//	cout << "DIFFUSE: " << diffuse << ", ERROR: " << __LINE__ << " : " << glGetError() << endl;
	//	cout << "ERROR: " << __LINE__ << " : " << glGetError() << endl;


}

void glRenderer::addPointLight(PointLight *p) {
		scene.pointLights.push_back(p);
		setLights();
}

void glRenderer::setDirectionalLight(DirectionalLight *light){

	if(light == NULL ){
		return;
	}

	scene.dirLight = light;
	if(program == 0){
		return;
	}
	
	GLuint dir_u = glGetUniformLocation (program, "dirLight.direction");
	GLuint amb_u = glGetUniformLocation (program, "dirLight.ambient");
	GLuint dif_u = glGetUniformLocation (program, "dirLight.diffuse");
	GLuint spec_u = glGetUniformLocation (program, "dirLight.specular");

	Vec3f dir = light->getDirection();
	Vec3f ambient = light->getAmbient();
	Vec3f diffuse = light->getDiffuse();
	Vec3f specular = light->getSpecular();

	glUniform3f(dir_u, dir.x, dir.y, dir.z);
	glUniform3f(amb_u, ambient.x, ambient.y, ambient.z);
	glUniform3f(dif_u, diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(spec_u, specular.x, specular.y, specular.z);

}

DirectionalLight *glRenderer::getDirectionalLight(){
	return scene.dirLight;
}

Mat4x4 glRenderer::getView() {
	return view;
}

void glRenderer::setLightSpace(Mat4x4 lightSpace) {
	//if(this->transform != transform){
		this->lightSpace = lightSpace;


		GLuint lightSpace_u = glGetUniformLocation (program, "lightSpace");
		glUniformMatrix4fv(lightSpace_u, 1, GL_TRUE, &lightSpace.m[0][0]);
	//}
}

void glRenderer::setShadowMap(GLuint shadowMap) {
		this->shadowMap = shadowMap;
		GLuint shadowMap_u = glGetUniformLocation (program, "shadowMap");
		
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, shadowMap);
		glUniform1i(shadowMap_u, 3);
}

void glRenderer::setInverse(Mat4x4 inverse) {
	//if(this->transform != transform){
		this->inverse = inverse;
		GLuint inverse_u = glGetUniformLocation (program, "inverse");
		glUniformMatrix4fv(inverse_u, 1, GL_TRUE, &inverse.m[0][0]);
	//}
}


void glRenderer::drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices) {
	glDrawElements(mode, count, type, indices);
}

void glRenderer::drawArrays(GLenum mode, GLint first, GLsizei count){
	glDrawArrays(mode, first, count);
}

void glRenderer::setLights(){
	for(int i = 0; i < scene.pointLights.size(); i++){
		string num = to_string(i);

		GLuint position_u = glGetUniformLocation (program, ("pointLight["+num+"].position").c_str());
		GLuint ambient_u = glGetUniformLocation (program, ("pointLight["+num+"].ambient").c_str());
		GLuint diffuse_u = glGetUniformLocation (program, ("pointLight["+num+"].diffuse").c_str());
		GLuint specular_u = glGetUniformLocation (program, ("pointLight["+num+"].specular").c_str());
		GLuint constant_u = glGetUniformLocation (program, ("pointLight["+num+"].constant").c_str());
		GLuint linear_u = glGetUniformLocation (program, ("pointLight["+num+"].linear").c_str());
		GLuint quadratic_u = glGetUniformLocation (program, ("pointLight["+num+"].quadratic").c_str());

	    if(!scene.pointLights[i]){
	    	return;
	    }

		Vec3f pos = scene.pointLights[i]->getPosition();
		Vec3f ambient = scene.pointLights[i]->getAmbient();
		Vec3f diffuse = scene.pointLights[i]->getDiffuse();
		Vec3f specular = scene.pointLights[i]->getSpecular();
		Vec3f attenuation = scene.pointLights[i]->getAttenuation();

		glUniform3f(position_u, pos.x, pos.y, pos.z);
		glUniform3f(ambient_u, ambient.x, ambient.y, ambient.z);
		glUniform3f(diffuse_u, diffuse.x, diffuse.y, diffuse.z);
		glUniform3f(specular_u, specular.x, specular.y, specular.z);
		glUniform1f(constant_u, attenuation.x);
		glUniform1f(linear_u, attenuation.y);
		glUniform1f(quadratic_u, attenuation.z);
	}
}


