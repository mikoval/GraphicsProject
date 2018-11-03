#include <Shapes/glCube.h>

#include <vector>
#include <Graphics/GeometryUtils.h>
#include <Core/Base.h>

using namespace std;
static int SIZE;

glCube::glCube(){
	model = models.LoadModel("assets/Models/Cube.obj");

	program = shaders.LoadShader("ColorShader");
	shadowProgram = shaders.LoadShader("ShadowShader");
}


void glCube::draw(){
	draw(Mat4x4());
}

void glCube::draw(Mat4x4 transform){
	renderer.setProgram(*program);

	Mat4x4 s = Scale(scale);
	Mat4x4 trans = Translation(position);

	Mat4x4 view = renderer.getView();

	renderer.setInverse((view * trans).inverse().transpose());

	renderer.setMaterial(material);
	
	model->draw(transform * trans * s);
}

void glCube::drawShadow(){
	drawShadow(Mat4x4());
}


void glCube::drawShadow(Mat4x4 transform){
	renderer.setProgram(*shadowProgram);

	Mat4x4 s = Scale(scale);
	Mat4x4 trans = Translation(position);

	model->draw(transform * trans * s);
}

void glCube::transform(Mat4x4 m){
}

void glCube::print(){
    cout << "PRINTING glCube" << endl;
}