#include <Graphics/GeometryUtils.h>   
#include <Graphics/Light.h>

void Light::setAmbient(Vec3f c){
	this->ambient = c;
}

Vec3f Light::getAmbient(){
	return ambient;
}

void Light::setDiffuse(Vec3f c){
	this->diffuse = c;
}

Vec3f Light::getDiffuse(){
	return diffuse;
}

void Light::setSpecular(Vec3f c){
	this->specular = c;
}

Vec3f Light::getSpecular(){
	return specular;
}