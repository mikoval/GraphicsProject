#include <Materials/MaterialManager.h>

MaterialManager materials = MaterialManager();

MaterialManager::MaterialManager(){
	cout << "CONSTRUCITNG MATERIAL MANAGER" << endl;
}

Material* MaterialManager::LoadMaterial(string material) {
	if(material == "Emerald") {
		return &emerald;
	} else if(material == "CyanRubber") {
		return &cyan_rubber;
	} else if(material == "CyanPlastic") {
		return &cyan_rubber;
	} else if(material == "White") {
		return &white;
	}
	if(material == "Crate") {
		return &crate;
    }
	if(material == "Earth") {
		return &earth;
    }
    if(material == "Venus") {
		return &venus;
    }
	return 0;
}


Material* MaterialManager::LoadCubeMap(string path) {
	return loadCubeMap(path);
}
