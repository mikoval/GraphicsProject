#include <Core/SceneLoader.h>
#include <iostream>
#include <Shapes/glObjectsAll.h>
#include <Cameras/glCamerasAll.h>
#include <Core/Base.h>


static inline glAstroidRing* loadAstroidRing(FILE *file){
	char lineHeader[128];
	float radius;
	int count;

	fscanf(file, "%s %f %d\n", lineHeader, &radius, &count);
	glAstroidRing *a = new glAstroidRing(300, 5000);
	return a;
}
static inline PointLight* parsePointLight(FILE *file){
	PointLight *light = new PointLight();
	char lineHeader[128];
	int res;
	bool reading = true;

	while(reading){
		res = fscanf(file, "%s", lineHeader);
		if (res == EOF){
			return 0;
		}
		if ( strcmp( lineHeader, "Color" ) == 0 ){ 
			Vec3f color;
			fscanf(file, "%f %f %f\n", &color.x, &color.y, &color.z);
		} 
		if ( strcmp( lineHeader, "Position" ) == 0 ){ 
			Vec3f position;
			fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
			light->setPosition(position);
			//light->setPosition(Vec3f(4.0, 0.0, 0.0));

		} 
		if ( strcmp( lineHeader, "End" ) == 0 ){ 
			reading = false;
		} 
	}

	return light;
}

static inline DirectionalLight* parseDirectionalLight(FILE *file){
	DirectionalLight *light = new DirectionalLight();
	char lineHeader[128];
	int res;
	bool reading = true;

	while(reading){
		res = fscanf(file, "%s", lineHeader);
		if (res == EOF){
			return 0;
		}
		if ( strcmp( lineHeader, "Direction" ) == 0 ){ 
			Vec3f dir;
			fscanf(file, "%f %f %f\n", &dir.x, &dir.y, &dir.z);
			light->setDirection(dir);
		} 
		if ( strcmp( lineHeader, "Ambient" ) == 0 ){ 
			Vec3f color;
			fscanf(file, "%f %f %f\n", &color.x, &color.y, &color.z);
			light->setAmbient(color);
		} 
		if ( strcmp( lineHeader, "Diffuse" ) == 0 ){ 
			Vec3f color;
			fscanf(file, "%f %f %f\n", &color.x, &color.y, &color.z);
			light->setDiffuse(color);
		} 
		if ( strcmp( lineHeader, "Specular" ) == 0 ){ 
			Vec3f color;
			fscanf(file, "%f %f %f\n", &color.x, &color.y, &color.z);
			light->setSpecular(color);
		} 
		if ( strcmp( lineHeader, "Shadow" ) == 0 ){ 
			float mult;
			float x1, x2, y1, y2, near, far;
			
			fscanf(file, "%f %f %f %f %f %f %f \n", &mult, &x1, &x2, &y1, &y2, &near, &far);
			light->enableShadows(mult, x1, x2, y1, y2, near, far);
		} 

		if ( strcmp( lineHeader, "End" ) == 0 ){ 
			reading = false;
		} 
	}

	return light;
}

static inline Camera* parseCamera(FILE *file){
	Camera *camera = 0;
	char lineHeader[128];
	int res;
	bool reading = true;

	res = fscanf(file, "%s\n", lineHeader);

	if ( strcmp( lineHeader, "OrbitalCamera" ) == 0 ){ 
		camera = new OrbitalCamera();
	} else 	if ( strcmp( lineHeader, "FreeCamera" ) == 0 ){ 
		camera = new FreeCamera();
	} else {
		cout << "Camera type not recognized" << endl;
		return 0;
	}



	while(reading){
		res = fscanf(file, "%s", lineHeader);
		if (res == EOF){
			return 0;
		}
		if ( strcmp( lineHeader, "Position" ) == 0 ){ 
			Vec3f position;
			fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
			camera->setPosition(position);
		} 
		if ( strcmp( lineHeader, "End" ) == 0 ){ 
			reading = false;
		} 
	}

	return camera;
}

static inline glObject* parseObject(FILE *file){
	glObject *object = 0;
	char lineHeader[128];
	int res;
	bool reading = true;

	res = fscanf(file, "%s\n", lineHeader);

	if ( strcmp( lineHeader, "Cube" ) == 0 ){ 
		object = new glCube();
	} else 	if ( strcmp( lineHeader, "Sphere" ) == 0 ){ 
		object = new glSphere();
	} else 	if ( strcmp( lineHeader, "Axis" ) == 0 ){ 
		object = new glAxis();
	} else 	if ( strcmp( lineHeader, "Model" ) == 0 ){ 
		glMeshObject *m = new glMeshObject();
		object = m;
		res = fscanf(file, "%s", lineHeader);
		if (res == EOF){
			return 0;
		}
		if ( strcmp( lineHeader, "Path" ) == 0 ){ 
            fscanf(file, "%s", lineHeader);
            string modelStr = string(lineHeader);

            m->loadModel(modelStr);
		} else {
			cout << "PROBLEM WITH PATH" << endl;
			return 0;
		}
	} else 	if ( strcmp( lineHeader, "CubeMap" ) == 0 ){ 
		glCubeMap *m = new glCubeMap();
		object = m;
		res = fscanf(file, "%s", lineHeader);
		if (res == EOF){
			return 0;
		}
		if ( strcmp( lineHeader, "Path" ) == 0 ){ 
            fscanf(file, "%s", lineHeader);
            string cubeMapStr = string(lineHeader);
            Material *material = materials.LoadCubeMap(cubeMapStr);
            object->setMaterial(material);
		} else {
			cout << "PROBLEM WITH PATH" << endl;
			return 0;
		}
	} else 	if ( strcmp( lineHeader, "AstroidRing" ) == 0 ){ 
		glAstroidRing *m = loadAstroidRing(file);
		object = m;
	}
	else {
		cout << "Object type not recognized" << endl;
		return 0;
	}



	while(reading){
		res = fscanf(file, "%s", lineHeader);
		if (res == EOF){
			return 0;
		}
		if ( strcmp( lineHeader, "Material" ) == 0 ){ 
            fscanf(file, "%s", lineHeader);
			string materialStr= string(lineHeader);
            Material *material = materials.LoadMaterial(materialStr);
            object->setMaterial(material);
		} 
		if ( strcmp( lineHeader, "Position" ) == 0 ){ 
			Vec3f position;
			fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
			object->setPosition(position);
		} 
		if ( strcmp( lineHeader, "RotateX" ) == 0 ){ 
			float amt;
			fscanf(file, "%f\n", &amt);
			object->setOrientation(RotateX(radians(amt)));
		} 

		if ( strcmp( lineHeader, "Scale" ) == 0 ){ 
			Vec3f scale;
			fscanf(file, "%f %f %f\n", &scale.x, &scale.y, &scale.z);
			object->applyScale(scale);
		} 
		if ( strcmp( lineHeader, "Shader" ) == 0 ){ 
			fscanf(file, "%s", lineHeader);
			object->setProgram(shaders.LoadShader(lineHeader));
		} 
		if ( strcmp( lineHeader, "End" ) == 0 ){ 
			reading = false;
		} 
	}

	return object;
}

void glLoadScene(string path, glSimulation *simulation) {
	FILE * file = fopen(path.data(), "r");
	if( file == NULL ){
		printf("Unable to open the file\n");
		return;
	}

	while( 1 ){
		char lineHeader[128];
		int res;
		// read the first word of the line


		res = fscanf(file, "%s", lineHeader);
		if (res == EOF){
			break;
		}
		
		if ( strcmp( lineHeader, "Object" ) == 0 ){ 
			glObject *object = parseObject(file);
			if(object){
				simulation->addObject(object);
			} else {
				cout << "invalid object" << endl;
			}
		} else if ( strcmp( lineHeader, "PointLight" ) == 0 ){ 
			PointLight *light = parsePointLight(file);
			if(light){
				simulation->addLight(light);
			} else {
				cout << "invalid point light" << endl;
			}
		} else if ( strcmp( lineHeader, "DirectionalLight" ) == 0 ){
			DirectionalLight *light = parseDirectionalLight(file);
			if(light){
				simulation->addLight(light);
			} else {
				cout << "invalid directional light" << endl;
			}
		} else if ( strcmp( lineHeader, "Camera" ) == 0 ){
			Camera *cam = parseCamera(file);
			if(cam){
				simulation->setCamera(cam);
			} else {
				cout << "invalid light" << endl;
			}
		}
		else {
			//cout << "failed to find : " << lineHeader << endl;
		}

	}
}
