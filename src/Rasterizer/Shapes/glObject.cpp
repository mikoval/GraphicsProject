#include <Shapes/glObject.h>



void glObject::draw(){

}

void glObject::draw(Mat4x4 transform){

}

void glObject::drawShadow(){

}

void glObject::drawShadow(Mat4x4 transform){

}

void glObject::print(){
    cout << "PRINTING glObject" << endl;
}

void glObject::setPosition(Vec3f position) {
	this->position = position;
}
void glObject::setOrientation(Mat4x4 rotation) {
	this->rotation = rotation;
}
void glObject::setScale(Vec3f scale) {
	this->scale = scale;
}

void glObject::applyScale(Vec3f s) {
	this->scale = this->scale * s;
}

void glObject::setMaterial(Material *material){
	this->material = material;
}

void glObject::setProgram(GLuint *program){
	this->program = program;
}
