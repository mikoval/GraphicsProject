#ifndef GL_MODEL_H
#define GL_MODEL_H
#include <Math/MathTools.h>
#include <vector>
#include <Shapes/glMesh.h>

class glModel {

public:
	void draw();
	void draw(Mat4x4 trans);
	void print();
	void getMinMax(float *minX_out, float *maxX_out, float *minY_out, float *maxY_out, float *minZ_out, float *maxZ_out);
	void setInstanceable(int count, Mat4x4* m);
	void drawInstanced(int count, Mat4x4 transform);

	vector<glMesh> meshes;
};

#endif