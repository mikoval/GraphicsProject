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
    if(material == "Brick") {
		return &brick;
    }
    if(material == "BlackTile") {
		return &black_tile;
    }
    if(material == "BlackTileSmall") {
		return &black_tile_small;
    }
    if(material == "Red") {
		return &red;
    }
    if(material == "Green") {
		return &green;
    }
    if(material == "Blue") {
		return &blue;
    }

    if(material == "RedPhong") {
		return &red_phong;
    }
    if(material == "GreenPhong") {
		return &green_phong;
    }
    if(material == "BluePhong") {
		return &blue_phong;
    }


	return 0;
}


Material* MaterialManager::LoadCubeMap(string path) {
	return loadCubeMap(path);
}
