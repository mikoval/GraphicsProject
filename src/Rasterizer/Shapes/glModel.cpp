#include <Shapes/glModel.h>
#include <Core/Base.h>

void glModel::draw(){
	draw(Mat4x4());
}

void glModel::draw(Mat4x4 transform){
//	cout << "DRAWING MODEL. SIZE: " << meshes.size() << endl;
	renderer.setModel(transform);

	for(int i = 0; i < meshes.size(); i++){
		meshes[i].draw(transform);
	}
}

void glModel::drawInstanced(int count, Mat4x4 transform){
	renderer.setModel(transform);

	for(int i = 0; i < meshes.size(); i++){
		meshes[i].drawInstanced(count, transform);
	}
}


void glModel::getMinMax(float *minX_out, float *maxX_out, float *minY_out, float *maxY_out, float *minZ_out, float *maxZ_out) {
	float minX = INF;
	float minY = INF;
	float minZ = INF;

	float maxX = -INF;
	float maxY = -INF;
	float maxZ = -INF;

	for(int i = 0; i < meshes.size(); i++){
		float minX2 = INF;
		float minY2 = INF;
		float minZ2 = INF;

		float maxX2 = -INF;
		float maxY2 = -INF;
		float maxZ2 = -INF;

		meshes[i].getMinMax(&minX2, &maxX2, &minY2, &maxY2, &minZ2, &maxZ2);

		minX = MIN(minX, minX2);
		minY = MIN(minY, minY2);
		minZ = MIN(minZ, minZ2);

		maxX = MAX(maxX, maxX2);
		maxY = MAX(maxY, maxY2);
		maxZ = MAX(maxZ, maxZ2);
	}
	*minX_out = minX;
	*maxX_out = maxX;
	*minY_out = minY;
	*maxY_out = maxY;
	*minZ_out = minZ;
	*maxZ_out = maxZ;
}


void glModel::print(){
    cout << "PRINTING glModel" << endl;
}


void glModel::setInstanceable(int count, Mat4x4* m){
	// vertex Buffer Object

	float *dataBuffer = (float *)malloc(16 * sizeof(float) * count);

	for(int i = 0; i < count; i++){
		float tmp[16 * sizeof(float)];
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				tmp[4 * j + k] = m[i].m[k][j];
			}
		}
		memcpy(&(dataBuffer[16 * i]), tmp, 16 * sizeof(float));
	}

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, count *  16 * sizeof(float), &dataBuffer[0], GL_STATIC_DRAW);
	 
	free(dataBuffer);
	for(unsigned int i = 0; i < meshes.size(); i++)
	{
	    unsigned int VAO = meshes[i].VAO;
	    glBindVertexArray(VAO);
	    // vertex Attributes
	    GLsizei vec4Size = 4 * sizeof(float);
	    glEnableVertexAttribArray(3); 
	    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
	    glEnableVertexAttribArray(4); 
	    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
	    glEnableVertexAttribArray(5); 
	    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
	    glEnableVertexAttribArray(6); 
	    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

	    glVertexAttribDivisor(3, 1);
	    glVertexAttribDivisor(4, 1);
	    glVertexAttribDivisor(5, 1);
	    glVertexAttribDivisor(6, 1);

	    glBindVertexArray(0);
	}  
}
