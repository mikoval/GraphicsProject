#include <Shapes/glSphere.h>

#include <vector>
#include <Graphics/GeometryUtils.h>
#include <Core/Base.h>

using namespace std;
static int SIZE;

glSphere::glSphere(){
	model = models.LoadModel("assets/Models/Sphere.obj");

	program = shaders.LoadShader("ColorShader");
	shadowProgram = shaders.LoadShader("ShadowShader");
}


void glSphere::draw(){
	draw(Mat4x4());
}

void glSphere::draw(Mat4x4 transform){

	renderer.setProgram(*program);

	Mat4x4 s = Scale(scale);
	Mat4x4 trans = Translation(position);

	Mat4x4 view = renderer.getView();

	renderer.setInverse((view * trans).inverse().transpose());

	renderer.setMaterial(material);
	
	model->draw(transform * trans * s);
}

void glSphere::drawShadow(){
	drawShadow(Mat4x4());
}


void glSphere::drawShadow(Mat4x4 transform){
	renderer.setProgram(*shadowProgram);

	Mat4x4 s = Scale(scale);
	Mat4x4 trans = Translation(position);

	model->draw(transform * trans * s);
}

void glSphere::print(){
    cout << "PRINTING glSphere" << endl;
}
