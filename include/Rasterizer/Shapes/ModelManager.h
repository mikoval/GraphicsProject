#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <map>
#include <Shapes/glModel.h>

class ModelManager {

public:
	ModelManager();
	glModel *LoadModel(const char *path);
	glModel *LoadNewModel(const char *path);

private:
	std::map<std::string, glModel*> m;
};

#endif