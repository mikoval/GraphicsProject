#ifndef BLINN_PHONG_SHADER_H
#define BLINN_PHONG_SHADER_H

#include <Shaders/ShaderManager.h>
static inline GLuint CreateBlinnPhongShader() {
	char log[1000];
	int length;

	string vertSrc = loadShader("3D/mvp.vert");
	string fragSrc = loadShader("Phong/blinn_phong.frag");
	char *vert = (char *)vertSrc.data();
	char *frag = (char *)fragSrc.data();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vert, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &frag, NULL);
	glCompileShader(fs);

	GLuint program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
	glLinkProgram(program);


	glGetShaderInfoLog(vs, 1000, &length, log);
	if(strlen(log)){
		 	cout << "LOG: " <<  log << endl;
	}
 	glGetShaderInfoLog(fs, 1000, &length, log);
	if(strlen(log)){
		 	cout << "LOG: " <<  log << endl;
	}


	return program;
}

#endif