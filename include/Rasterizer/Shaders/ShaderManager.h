#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <Core/glContextUtil.h>

class ShaderManager {

public:
	ShaderManager();
	GLuint* LoadShader(string shader);
};

string loadShader(string shader);

#endif
