#ifndef BASIC_COLOR_SHADER_H
#define BASIC_COLOR_SHADER_H

static inline GLuint CreateColorShader() {
    const char* vert =
		"#version 400\n"
		"layout (location = 0) in vec3 vp;"
		"layout (location = 1) in vec3 norm;"
		"layout (location = 2) in vec2 uv_i;"
		"out vec2 uv;"
		"uniform mat4 proj;"
		"uniform mat4 view;"
		"uniform mat4 model;"
		"uniform mat4 inverse;"
		"void main() {"
		"	uv = uv_i;"
		//"	uv.x = 1.0 - uv.x;"
		"	gl_Position = proj * view * model * vec4(vp, 1.0);"
		"}";
	const char* frag =
		"#version 400\n"
		"out vec4 frag_colour;"
		"in vec2 uv;"
		"uniform mat4 view;"
		"uniform vec3 light;"

		"struct Material {"
    		"vec3 ambient;"
    		"vec3 diffuse;"
    		"vec3 specular;"


   			"sampler2D ambientTexture;"
			"sampler2D diffuseTexture;"
			"sampler2D specularTexture;"

    		"float shininess;"
		"};"

		"uniform Material material;"

		"void main() {"
			"vec3 result = texture(material.diffuseTexture, uv).xyz ;"
			"if (result.x ==  0.0) { result = material.diffuse; }"
			"frag_colour = vec4(result, 1.0);"
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

	return program;
}

#endif