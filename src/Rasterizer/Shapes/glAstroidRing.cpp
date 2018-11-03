#include <Shapes/glAstroidRing.h>

#include <vector>
#include <Graphics/GeometryUtils.h>
#include <Core/Base.h>

using namespace std;
static int SIZE;

#define RAND ((float)rand() / (float)RAND_MAX)

glAstroidRing::glAstroidRing(float radius, int count){
	this->radius = radius;
	this->count = count;

	this->loadModel("assets/Models/rock/rock.obj");
	this->genModels(radius, count);
	this->model->setInstanceable(count, positions);

	program = shaders.LoadShader("PhongInstanceShader");
				cout << __func__ << ", " << __LINE__ << " : PRINTING ERROR: " << glGetError() << endl;
    cout << "PROGRAM: " <<  *program << endl;
}


void glAstroidRing::draw(){
	draw(Mat4x4());
}

void glAstroidRing::draw(Mat4x4 transform){
	glEnable(GL_CULL_FACE);  
	glCullFace(GL_FRONT); 

	renderer.setProgram(*program);

	Mat4x4 transl = Translation(position) ;
	Mat4x4 scale_mat = Scale(scale);
	Mat4x4 view = renderer.getView();


	renderer.setMaterial(material);
	
	Mat4x4 m =  transform * transl * scale_mat;
	
	/*
	for(int i = 0; i < count ; i++){
		Mat4x4 trans = positions[i] * m;
		renderer.setInverse(view * trans);

		model->draw(trans);
	}
	*/
	
	model->drawInstanced(count, m);

	glDisable(GL_CULL_FACE);
}


void glAstroidRing::print(){
    cout << "PRINTING glAstroidRing" << endl;
}
void glAstroidRing::loadModel(string path){
    model = models.LoadModel(path.data());
    float minX, maxX, minY, maxY, minZ, maxZ;
    model->getMinMax(&minX, &maxX, &minY, &maxY, &minZ, &maxZ);
    float width = maxX - minX;
    float height = maxY - minY;
    float depth = maxZ - minZ;


    float m = 1.0 / max(max(width, height), depth);
    scale = Vec3f(m,m,m);
}

void glAstroidRing::genModels(float radius, int count){
	positions = (Mat4x4 *)malloc(count * sizeof(Mat4x4));
	for(int i = 0; i < count; i++){
		Vec3f s;
		float baseSize = RAND * 6.0;
		s.x = baseSize;
		s.y = baseSize;
		s.z = baseSize;

		Mat4x4 rotation;
		Vec3f axis = Vec3f((RAND-0.5), (RAND-0.5), (RAND-0.5)).norm();
		rotation = Rotate(axis, Vec3f(), (RAND-0.5) * 10.0);

		Vec3f position;
		float len = radius + (RAND-0.5) * radius / 2.0;
		float theta = RAND * 2.0 * PI;
		position.x = cos(theta) * len;
		position.z = sin(theta) * len;
		position.y = (RAND-0.5) * radius / 3.0;

		positions[i] = Translation(position) * rotation * Scale(s);
	}
}