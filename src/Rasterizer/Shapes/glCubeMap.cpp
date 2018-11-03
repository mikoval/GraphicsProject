#include <Shapes/glCubeMap.h>

#include <vector>
#include <Graphics/GeometryUtils.h>
#include <Core/Base.h>

using namespace std;
static int SIZE;

glCubeMap::glCubeMap(){
	model = models.LoadModel("assets/Models/Cube.obj");

	program = shaders.LoadShader("CubeMapShader");
}


void glCubeMap::draw(){
	draw(Mat4x4());
}

void glCubeMap::draw(Mat4x4 transform){
	renderer.setProgram(*program);

	Mat4x4 s = Scale(scale);
	Mat4x4 trans = Translation(position);
	renderer.setModel(transform * trans * s);

	Mat4x4 view = renderer.getView();

	renderer.setInverse((view * trans).inverse().transpose());

	glBindTexture(GL_TEXTURE_CUBE_MAP, material->diffuseTexture);

	model->draw(transform * trans * s);
	//renderer.drawArrays(GL_TRIANGLES, 0, mesh_size);
}

void glCubeMap::print(){
    cout << "PRINTING glCubeMap" << endl;
}