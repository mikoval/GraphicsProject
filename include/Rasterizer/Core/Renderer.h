#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include <Math/MathTools.h>
#include <Rasterizer/Core/glContextUtil.h>

#include <Lights/PointLight.h>
#include <Lights/DirectionalLight.h>

#include <Materials/Materials.h>
#include <vector>

struct sceneSettings {
	Vec3f eye;
	vector<PointLight *> pointLights;
	size_t pointLightCount;
	DirectionalLight *dirLight;
};

class glRenderer {

private:
	GLuint vao;
	GLuint program;
	sceneSettings scene;
	Mat4x4 model;
	Mat4x4 view;
	Mat4x4 proj;
	Material *material = nullptr;
	Mat4x4 inverse;
	Mat4x4 lightSpace;
	GLuint shadowMap;

	void setLights();

public:
	void setVao(GLuint vao);
	void setProgram(GLuint program);
	void setEye(Vec3f eye);
	void setModel(Mat4x4 m);
	void setView(Mat4x4 m);
	void setProj(Mat4x4 m);
	void setMaterial(Material *material);

	void addPointLight(PointLight *p);
	void setDirectionalLight(DirectionalLight *p);
	DirectionalLight *getDirectionalLight();

	void setLightSpace(Mat4x4 lightSpace);
	void setShadowMap(GLuint shadowMap);

	Mat4x4 getView();

	void setInverse(Mat4x4 inverse);

	void drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices);
	void drawArrays(GLenum mode, GLint first, GLsizei count);
};

#endif