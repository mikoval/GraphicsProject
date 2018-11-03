#ifndef CUBEMAP_SHADER_H
#define CUBEMAP_SHADER_H

static inline GLuint CreateCubeMapShader() {
    const char* vert =
		"#version 400\n"
		"in vec3 vp;"
		"in vec3 norm;"
		"in vec2 uv_i;"
		"out vec3 TexCoords;"

		"uniform mat4 proj;"
		"uniform mat4 view;"
		"uniform mat4 model;"
		"uniform mat4 inverse;"
		"void main() {"
		"	TexCoords = vp;"
		"	gl_Position = proj * view * model * vec4(vp, 1.0);"
		"}";
	const char* frag =
		"#version 400\n"
		"#define NUM_POINT_LIGHTS 4\n"

		"out vec4 frag_colour;"
		"in vec3 TexCoords;"

		"uniform mat4 view;"
		"uniform samplerCube skybox;"

		"void main() {"
			"frag_colour = texture(skybox, TexCoords);"
		"}";

	char log[1000];
	int length;
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