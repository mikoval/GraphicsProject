#ifndef CORE_UTILS_H
#define CORE_UTILS_H

#include <iostream>
#include <vector>

#include <Math/MathTools.h>

static inline void computeNormals(float *vertices, unsigned int *indices, float *normals, int size) {
	
	for(int i = 0; i < size; i+= 9){
		Vec3f a = Vec3f(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
		Vec3f b = Vec3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
		Vec3f c = Vec3f(vertices[i + 6], vertices[i + 7], vertices[i + 8]);

		Vec3f v1 = (b - a).norm();
		Vec3f v2 = (c - b).norm();

		Vec3f n = cross(v1, v2).norm();
		normals[i + 0] = n.x; normals[i + 1] = n.y; normals[i + 2] = n.z;
		normals[i + 3] = n.x; normals[i + 4] = n.y; normals[i + 5] = n.z;
		normals[i + 6] = n.x; normals[i + 7] = n.y; normals[i + 8] = n.z;
	}

}

static inline bool loadOBJ(
	const char * path, 
	std::vector<Vec3f> & out_vertices,
	std::vector<Vec2f> & out_uvs,
	std::vector<Vec3f> & out_normals
){
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vec3f> temp_vertices; 
	std::vector<Vec2f> temp_uvs;
	std::vector<Vec3f> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			Vec3f vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			Vec2f uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			Vec3f normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("matches: %d \n", matches);
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[2]);
			vertexIndices.push_back(vertexIndex[1]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[2]);
			uvIndices    .push_back(uvIndex[1]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[2]);
			normalIndices.push_back(normalIndex[1]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		Vec3f vertex = temp_vertices[ vertexIndex-1 ];
		Vec2f uv = temp_uvs[ uvIndex-1 ];
		Vec3f normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);
	
	}
	fclose(file);
	return true;
}


#endif
