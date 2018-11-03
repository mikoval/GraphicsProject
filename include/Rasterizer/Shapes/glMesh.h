#ifndef GL_MESH_H
#define GL_MESH_H
#include <Math/MathTools.h>
#include <Rasterizer/Core/glContextUtil.h>
#include <vector>
#include <Materials/Materials.h>

struct Vertex {
    // position
    Vec3f Position;
    // normal
    Vec3f Normal;
    // texCoords
    Vec2f TexCoords;
};

class glMesh {
public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    Material material;
    unsigned int VAO;

    /*  Functions  */
    // constructor
    glMesh(vector<Vertex> &v, vector<unsigned int> &i, Material &m)
    {
        this->vertices = v;
        this->indices = i;
        this->material = m;
        
        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    void draw();
    void draw(Mat4x4 trans);
    void drawInstanced(int count, Mat4x4 trans);
    void print();
    void getMinMax(float *minX_out, float *maxX_out, float *minY_out, float *maxY_out,  float *minZ_out, float *maxZ_out);

private:
    /*  Render data  */
    unsigned int VBO, EBO;


    void setupMesh()
    {

   	GLuint vbo[3];
        // create buffers/arrays
      float *v = (float *)malloc(vertices.size() * 3 * sizeof(float));
      float *n = (float *)malloc(vertices.size() * 3 * sizeof(float));
      float *u = (float *)malloc(vertices.size() * 2 * sizeof(float));


       for(int i = 0; i < vertices.size(); i++){
               v[3 * i + 0] = vertices[i].Position.x;
               v[3 * i + 1] = vertices[i].Position.y;
               v[3 * i + 2] = vertices[i].Position.z;

               n[3 * i + 0] = vertices[i].Normal.x;
               n[3 * i + 1] = vertices[i].Normal.y;
               n[3 * i + 2] = vertices[i].Normal.z;

               u[2 * i + 0] = vertices[i].TexCoords.x;
               u[2 * i + 1] = vertices[i].TexCoords.y;
       }

       glGenVertexArrays(1, &VAO);
       glBindVertexArray(VAO);

       glGenBuffers(3, vbo);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
       glBufferData(GL_ARRAY_BUFFER, 3 * vertices.size() * sizeof(float), v, GL_STATIC_DRAW);
       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
       glEnableVertexAttribArray(0);


       glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
       glBufferData(GL_ARRAY_BUFFER, 3 * vertices.size() * sizeof(float), n, GL_STATIC_DRAW);
       glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
       glEnableVertexAttribArray(1);

       glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
       glBufferData(GL_ARRAY_BUFFER, 2 * vertices.size() * sizeof(float), u, GL_STATIC_DRAW);
       glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
       glEnableVertexAttribArray(2);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);


        glBindVertexArray(0);
    }
};

#endif
