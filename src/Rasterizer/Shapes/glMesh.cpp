#include <Shapes/glMesh.h>
#include <Core/Base.h>



void glMesh::draw(){
	draw(Mat4x4());
}

void glMesh::draw(Mat4x4 transform){
    glBindVertexArray(VAO);

    if(material.enabled){
    	renderer.setMaterial(&material);
    	cout <<"SETTING MATERIAL DIFFUSE X : " <<  material.diffuse.x << endl;
    }
    
    

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void glMesh::drawInstanced(int count, Mat4x4 transform){
    glBindVertexArray(VAO);

    //renderer.setMaterial(&material);
    

    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, count);


    glBindVertexArray(0);
}


void glMesh::print(){  
  //  cout << "PRINTING glMesh" << endl;
}

void glMesh::getMinMax(float *minX_out, float *maxX_out, float *minY_out, float *maxY_out,  float *minZ_out, float *maxZ_out){
	float minX = INF;
	float minY = INF;
	float minZ = INF;
	float maxX = -INF;
	float maxY = -INF;
	float maxZ = -INF;



	for(int i = 0; i < vertices.size(); i++){
		Vec3f p = vertices[i].Position;

		minX = MIN(minX, p.x);
		maxX = MAX(maxX, p.x);
		minY = MIN(minY, p.y);
		maxY = MAX(maxY, p.y);
		minZ = MIN(minZ, p.z);
		maxZ = MAX(maxZ, p.z);

	}
	*minX_out = minX;
	*maxX_out = maxX;
	*minY_out = minY;
	*maxY_out = maxY;
	*minZ_out = minZ;
	*maxZ_out = maxZ;
}