#include <Lights/DirectionalLight.h>
#include <Core/Base.h>

#define SHADOW_SIZE 1

DirectionalLight::DirectionalLight(){
	renderer.setDirectionalLight(this);
}

Vec3f DirectionalLight::getDirection(){
	return direction;
}

void DirectionalLight::setDirection(Vec3f dir){

	this->direction = dir;
	
}

void DirectionalLight::enableShadows(float multiplier, float shadow_x1, float shadow_x2, float shadow_y1, float shadow_y2, float near,  float far){
	this->shadows = true;

	this->shadow_multiplier = multiplier;
	this->shadow_x1 = shadow_x1;
	this->shadow_x2 = shadow_x2;
	this->shadow_y1 = shadow_y1;
	this->shadow_y2 = shadow_y2;
	this->shadow_near = near;
	this->shadow_far = far;

	printf("printing size : %f , %f ",  shadow_multiplier, shadow_multiplier );
	shadowBuffer = GenerateDepthBuffer(WIDTH * shadow_multiplier, HEIGHT * shadow_multiplier);
	//shadowBuffer = GenerateFBO(WIDTH * shadow_multiplier, HEIGHT * shadow_multiplier);
}

void DirectionalLight::updateShadows(){
	if(!this->shadows){
		return;
	}

	glViewport(0, 0, WIDTH * shadow_multiplier, HEIGHT * shadow_multiplier);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer.fbo);

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mat4x4 ortho = OrthographicProjection(shadow_x1, shadow_x2, shadow_y1, shadow_x2, shadow_near, shadow_far);

	Vec3f dir = this->getDirection();

	Vec3f pos = -1.0 * dir * 5.0;
	Vec3f up = Vec3f(0.0, 1.0, 0.0);

	Mat4x4 view = LookAt(pos, Vec3f(), up);
	view = view.inverse();


	renderer.setProj(ortho);
    renderer.setView(view);


    Mat4x4 lightSpace = ortho * view;
    renderer.setLightSpace(lightSpace);
	renderer.setShadowMap(shadowBuffer.texture);
}