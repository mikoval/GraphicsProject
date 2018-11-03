#ifndef PHONG_INSTANCE_SHADER_H
#define PHONG_INSTANCE_SHADER_H

static inline GLuint CreatePhongInstanceShader() {
	char log[1000];
	int length;

	string vertSrc = loadShader("3D/mvp_instance.vert");
	string fragSrc = loadShader("Phong/phong.frag");

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

	cout << __func__ << ": " << __LINE__ << ": " << glGetError() << endl;

	return program;
}

#endif