#include <Materials/Materials.h>
#include <Materials/stb_image.h>
#include <vector>


#define STD_AMB	Vec3f(0.3, 0.3, 0.3)
#define STD_DIF	Vec3f(0.6, 0.6, 0.6)
#define STD_SPEC Vec3f(1.0, 1.0, 1.0)
#define STD_SHIN 1.0

#define EMPTY_TEXTURE_INTS 0, 0, 0

static inline void loadMaterial(Material);
static inline void loadImage(GLuint *, const char *);

string crateDiffuse = "assets/Textures/Crate/diffuse.png";
string crateSpecular = "assets/Textures/Crate/specular.png";

string brickDiffuse = "assets/Textures/Brick/Diffuse.jpg";
string brickSpecular = "assets/Textures/Brick/Gloss.jpg";

string blackTileDiffuse = "assets/Textures/BlackTile/diffuse.jpg";
string blackTileSpecular = "assets/Textures/BlackTile/gloss.jpg";

string blackTileSmallDiffuse = "assets/Textures/BlackTileSmall/diffuse.png";
string blackTileSmallSpecular = "assets/Textures/BlackTileSmall/gloss.png";

string testDiffuse = "assets/Textures/Test/diffuse.png";
string testSpecular = "assets/Textures/Test/specular.png";

string earthDiffuse = "assets/Textures/Earth/diffuse.png";
string earthSpecular = "assets/Textures/Earth/diffuse.png";

string venusDiffuse = "assets/Textures/Venus/venus.jpg";
string venusSpecular = "assets/Textures/Venus/venus.jpg";



Material emerald = {
	Vec3f(0.0215, 0.1745, 0.0215),
	Vec3f(0.07568, 0.61424, 0.07568), 
	Vec3f(0.633, 0.727811, 0.633),
	0.6,

	"", "", "", 
	0, 0, 0,
	false
};

			

Material cyan_rubber = {
	Vec3f(0.0, 0.05, 0.05),
	Vec3f(0.4, 0.5, 0.5), 
	Vec3f(0.04, 0.7, 0.7),
	.078125,

	"", "", "", 
	0, 0, 0,
	false
};

Material cyan_plastic = {
	Vec3f(0.0,0.1,0.06),
	Vec3f(0.0,0.50980392,0.50980392), 
	Vec3f(0.50196078,0.50196078,0.50196078),
	.25,

	"", "", "", 
	0, 0, 0,
	false
};

Material red = {
	Vec3f(1.0, 0.0, 0.0),
	Vec3f(1.0, 0.0, 0.0),
	Vec3f(1.0, 0.0, 0.0),
	0.0,

	"", "", "", 
	0, 0, 0,
	false
};
Material green = {
	Vec3f(0.0, 1.0, 0.0),
	Vec3f(0.0, 1.0, 0.0),
	Vec3f(0.0, 1.0, 0.0),
	0.0,

	"", "", "", 
	0, 0, 0,
	false
};
Material blue = {
	Vec3f(0.0, 0.0, 1.0),
	Vec3f(0.0, 0.0, 1.0),
	Vec3f(0.0, 0.0, 1.0),
	0.0,

	"", "", "", 
	0, 0, 0,
	false
};
Material red_phong = {
	Vec3f(0.3, 0.0, 0.0),
	Vec3f(1.0, 0.0, 0.0),
	Vec3f(1.0, 1.0, 1.0),
	0.0,

	"", "", "", 
	0, 0, 0,
	false
};
Material green_phong = {
	Vec3f(0.0, 0.3, 0.0),
	Vec3f(0.0, 1.0, 0.0),
	Vec3f(1.0, 1.0, 1.0),
	0.0,

	"", "", "", 
	0, 0, 0,
	false
};
Material blue_phong = {
	Vec3f(0.0, 0.0, 0.3),
	Vec3f(0.0, 0.0, 1.0),
	Vec3f(1.0, 1.0, 1.0),
	0.0,

	"", "", "", 
	0, 0, 0,
	false
};


Material white = {
	Vec3f(0.3, 0.3, 0.3),
	Vec3f(0.7, 0.7, 0.7),
	Vec3f(1.0, 1.0, 1.0),
	1.0,

	"", "", "", 
	0, 0, 0,
	false
};

Material crate = {
	STD_AMB, STD_DIF, STD_SPEC, STD_SHIN, 
	crateDiffuse, crateDiffuse, crateSpecular,
	EMPTY_TEXTURE_INTS,
	false
};

Material brick = {
	STD_AMB, STD_DIF, STD_SPEC, STD_SHIN, 
	brickDiffuse, brickDiffuse, brickSpecular,
	EMPTY_TEXTURE_INTS,
	false
};

Material black_tile = {
	STD_AMB, STD_DIF, STD_SPEC, STD_SHIN, 
	blackTileDiffuse, blackTileDiffuse, blackTileSpecular,
	EMPTY_TEXTURE_INTS,
	false
};

Material black_tile_small = {
	STD_AMB, STD_DIF, STD_SPEC, STD_SHIN,
	blackTileSmallDiffuse, blackTileSmallDiffuse, blackTileSmallSpecular,
	EMPTY_TEXTURE_INTS,
	false
};


Material earth = {
	STD_AMB, STD_DIF, STD_SPEC, STD_SHIN,
	earthDiffuse, earthDiffuse, earthSpecular,
	EMPTY_TEXTURE_INTS,
	false
};

Material venus = {
	STD_AMB, STD_DIF, STD_SPEC, STD_SHIN,
	venusDiffuse, venusDiffuse, venusSpecular,
	EMPTY_TEXTURE_INTS,
	false
};





static inline void loadMaterial(Material *m){
	loadImage(&m->ambientTexture, m->ambientPath.data());
	loadImage(&m->diffuseTexture, m->diffusePath.data());
	loadImage(&m->specularTexture, m->specularPath.data());
}


static inline void loadImage(GLuint *texture, const char *path){
	std::cout << "LOADING IMAGE AT PATH: " << path << std::endl;

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	std::cout << "CHECKING SINGLE CHANNEL" << " NUMBER OF PATHS: " << nrChannels << std::endl;

	if(nrChannels == 1){ 
		nrChannels = 3;
		unsigned char * data2 =(unsigned char *) malloc(width * height * 3);
		for(int i = 0 ; i < width ; i++) {
			for(int j = 0; j < height; j++){
				data2[(j * width + i) * 3] = data[(j * width + i)];
				data2[(j * width + i) * 3 + 1] = data[(j * width + i)];
				data2[(j * width + i) * 3 + 2] = data[(j * width + i)];
			}
		}
        stbi_image_free(data);
		data = data2;

	}

		std::cout << "SETTING TYPE" << std::endl;

	GLuint type;
	if(nrChannels == 3){
		type = GL_RGB;
	} else if (nrChannels == 4){
		type = GL_RGBA;
	}
	std::cout << "CREATING TEX IMAGE" << std::endl;

	if (data)
	{
	    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
	    glGenerateMipmap(GL_TEXTURE_2D);
	     std::cout << "succeeded to load texture: " << path << std::endl;
	}
	else
	{
	    std::cout << "Failed to load texture: " << path << std::endl;
	}
	free(data);
	std::cout << "DONE WITH IMAGE" << std::endl;
}

static inline unsigned int loadCubemap(string dir, vector<string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
    	string path = dir + "/" + faces[i];
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}  





int initMaterials(){
	loadMaterial(&crate);
	loadMaterial(&brick);
	loadMaterial(&earth);
	loadMaterial(&venus);
	loadMaterial(&black_tile);
	loadMaterial(&black_tile_small);
	printf("DONE LOADING MATERIALS \n ");
	return 0;
}

GLuint loadTexture(string path){
	GLuint texture;
	loadImage(&texture, path.data());
	return texture;
}

Material *loadCubeMap(string path){
	Material *m = new Material();
	vector<std::string> faces
	{
	    "right.png",
	    "left.png",
	    "top.png",
	    "bottom.png",
	    "front.png",
	    "back.png"
	};
	m->diffuseTexture = loadCubemap(path, faces);
	return m;
}


			
