#include <Shapes/glMeshObject.h>

#include <vector>
#include <Graphics/GeometryUtils.h>
#include <Core/Base.h>

using namespace std;
static int SIZE;

glMeshObject::glMeshObject(){
	model = models.LoadModel("assets/Models/Cube.obj");

	program = shaders.LoadShader("PhongShader");
	shadowProgram = shaders.LoadShader("ShadowShader");
}


void glMeshObject::draw(){
	draw(Mat4x4());
}

void glMeshObject::draw(Mat4x4 transform){
	renderer.setProgram(*program);

	Mat4x4 trans = Translation(position) * rotation;
	Mat4x4 scale_mat = Scale(scale);

	Mat4x4 view = renderer.getView();

	renderer.setInverse((view * trans).inverse().transpose());

	renderer.setMaterial(material);
	
	model->draw(transform * trans * scale_mat);
	//renderer.drawArrays(GL_TRIANGLES, 0, mesh_size);
}

void glMeshObject::drawShadow(){
	drawShadow(Mat4x4());
}


void glMeshObject::drawShadow(Mat4x4 transform){
	renderer.setProgram(*shadowProgram);

	Mat4x4 s = Scale(scale);
	Mat4x4 trans = Translation(position) * rotation;

	model->draw(transform * trans * s);
}

void glMeshObject::transform(Mat4x4 m){
}

void glMeshObject::print(){
    cout << "PRINTING glMeshObject" << endl;
}
void glMeshObject::loadModel(string path){
    model = models.LoadModel(path.data());
    float minX, maxX, minY, maxY, minZ, maxZ;
    model->getMinMax(&minX, &maxX, &minY, &maxY, &minZ, &maxZ);
    float width = maxX - minX;
    float height = maxY - minY;
    float depth = maxZ - minZ;

/*
    cout << "===============MIN X: " << minX << " , MAX X: " << maxX << endl;
    cout << "===============MIN Y: " << minY << " , MAX Y: " << maxY << endl;
    cout << "===============MIN Z: " << minZ << " , MAX Z: " << maxZ << endl;
*/

    float m = 1.0 / max(max(width, height), depth);
    if(m < 100000){
    	 scale = Vec3f(m,m,m);
    }
   
}