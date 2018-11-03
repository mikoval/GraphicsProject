#include <Graphics/GeometryUtils.h>   
#include <Lights/PointLight.h>
#include <Core/Base.h>


PointLight::PointLight() {
	model = models.LoadModel("assets/Models/Sphere.obj");
	program = shaders.LoadShader("ColorShader");
	renderer.setProgram(*program);
	renderer.addPointLight(this);

	size = 0.2;

	ambient = Vec3f(0.1, 0.1, 0.1);
	diffuse = Vec3f(0.6, 0.6, 0.6);
	specular = Vec3f(1.0, 1.0, 1.0);
	attenuation = Vec3f(1.0, 0.0, 0.0);

}

void PointLight::setPosition(Vec3f p){
	position = p;
	setModel();
}

void PointLight::setModel(){
	trans = Translation(position) * Scale(size, size, size);
}

Vec3f PointLight::getPosition(){
	return position;
}

Vec3f PointLight::getAmbient(){
	return ambient;
}
Vec3f PointLight::getDiffuse(){
	return diffuse;
}
Vec3f PointLight::getSpecular(){
	return specular;
}

Vec3f PointLight::getAttenuation(){
	return attenuation;
}

void PointLight::print(){
	cout << "POINT LIGHT" << endl;
}


void PointLight::draw(){
	renderer.setProgram(*program);
	renderer.setVao(vao);
	renderer.setMaterial(&white);

	model->draw(trans);
}