#include <Shapes/glAxis.h>

#include <vector>
#include <Graphics/GeometryUtils.h>
#include <Core/Base.h>

using namespace std;
static int SIZE;

glAxis::glAxis(){
	model = models.LoadModel("assets/Models/Arrow.obj");

	program = shaders.LoadShader("ColorShader");
}


void glAxis::draw(){
	draw(Mat4x4());
}

void glAxis::draw(Mat4x4 transform){
	
	renderer.setProgram(*program);

	Mat4x4 trans = Translation(position);

	Mat4x4 view = renderer.getView();

	renderer.setMaterial(material);
	
	renderer.setMaterial(&blue);
	model->draw(transform * trans);

	renderer.setMaterial(&red);
	model->draw(transform * trans * RotateX(-3.14/2.0) );

	renderer.setMaterial(&green);
	model->draw(transform * trans * RotateZ(-3.14/2.0));

}

void glAxis::transform(Mat4x4 m){
}

void glAxis::print(){
    cout << "PRINTING glAxis" << endl;
}