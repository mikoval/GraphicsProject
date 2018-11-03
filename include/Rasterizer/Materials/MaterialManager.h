#ifndef Material_MANAGER_H
#define Material_MANAGER_H

#include <Core/glContextUtil.h>
#include <Materials/Materials.h>

class MaterialManager {

public:
	MaterialManager();
	Material* LoadMaterial(string material);
	Material* LoadCubeMap(string material);
};

#endif
