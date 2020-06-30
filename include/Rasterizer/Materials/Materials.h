#ifndef MATERIALS_H
#define MATERIALS_H

#include <Math/MathTools.h>
#include <Rasterizer/Core/glContextUtil.h>

struct Material {
	Vec3f ambient;
    Vec3f diffuse;
    Vec3f specular;
    float shininess;

    string ambientPath;
	string diffusePath;
    string specularPath;
    GLuint ambientTexture;
    GLuint diffuseTexture;
    GLuint specularTexture;

    bool enabled;
};

extern Material emerald;
extern Material cyan_rubber;
extern Material cyan_plastic;

extern Material red;
extern Material green;
extern Material blue;

extern Material red_phong;
extern Material green_phong;
extern Material blue_phong;

extern Material white;


extern Material crate;
extern Material earth;
extern Material venus;
extern Material brick;
extern Material black_tile;
extern Material black_tile_small;

int initMaterials();

GLuint loadTexture(string path);
Material *loadCubeMap(string path);



#endif