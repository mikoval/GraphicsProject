#include <Shapes/ModelManager.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Shapes/glMesh.h>
#include <Shapes/glModel.h>



ModelManager models = ModelManager();

static void processNode(glModel *model, aiNode *node, const aiScene *scene);
static glModel* loadModel(string path);
static GLuint loadMaterialTexture(const aiScene *scene, aiMaterial *mat, aiTextureType type);
static GLuint loadMaterial(const aiScene *scene, aiMaterial *mat, aiTextureType type);

static glMesh processMesh(aiMesh *mesh, const aiScene *scene);

static string DIR;

ModelManager::ModelManager(){

}

glModel* ModelManager::LoadModel(const char *path){
	if(m[path]){
		return m[path];
	} else {
		glModel *model = loadModel(path);
		m[path] = model;
		return model;
	}
}

glModel* ModelManager::LoadNewModel(const char *path){
    
    glModel *model = loadModel(path);
    return model;
    
}


static void processNode(glModel *model, aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        model->meshes.push_back(processMesh(mesh, scene));			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(model, node->mChildren[i], scene);
    }
}  

static glModel* loadModel(string path)
{
	DIR = path.substr(0, path.find_last_of('/'));


    Assimp::Importer import;

    glModel *model = new glModel();

    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return 0;
    }
    //directory = path.substr(0, path.find_last_of('/'));

    processNode(model, scene->mRootNode, scene);

    return model;
} 

static glMesh processMesh(aiMesh *mesh, const aiScene *scene)
    {
        // data to fill
        vector<Vertex> vertices;
        vector<unsigned int> indices;

        // Walk through each of the mesh's vertices
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            Vec3f vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // normals
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
            // texture coordinates
            if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                Vec2f vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x; 
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector

            for(unsigned int j = 0; j < face.mNumIndices; j++){
                indices.push_back(face.mIndices[j]);
            }
        }
        
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        Material m;
        cout << "==================enabling " << endl;
        m.enabled = true;


        aiColor4D c;

        if(aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT,  &c) != aiReturn_SUCCESS || Vec3f(c.r, c.g, c.b) == Vec3f(0.0, 0.0, 0.0))
        {
            m.enabled = false;
            cout << "==================no textures " << endl;

            return glMesh(vertices, indices, m);
        } else { 
            cout << "==================textures " << endl;

        }

        m.diffuseTexture = loadMaterialTexture(scene, material, aiTextureType_DIFFUSE);
		m.specularTexture = loadMaterialTexture(scene, material, aiTextureType_SPECULAR);
	    m.ambientTexture = loadMaterialTexture(scene, material, aiTextureType_AMBIENT);



        if(aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT,  &c) == aiReturn_SUCCESS){
            m.ambient = Vec3f(c.r, c.g, c.b);
        }
        if(aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE,  &c) == aiReturn_SUCCESS){
            m.diffuse = Vec3f(c.r, c.g, c.b);
        }
        if(aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR,  &c) == aiReturn_SUCCESS){
            m.specular = Vec3f(c.r, c.g, c.b);
        }

        return glMesh(vertices, indices, m);
    }

static GLuint loadMaterialTexture(const aiScene *scene, aiMaterial *mat, aiTextureType type)
    {
        if(mat->GetTextureCount(type) <= 0)
        {
        	return 0;
        }
        aiString Path;

     	if (mat->GetTexture(type, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                string s = string(Path.data);
                string path = DIR + "/" + s;
                cout << "PRINTING MATERIAL PATH: " << path << endl;
                GLuint texture = loadTexture(path.data());
                return texture;

            } else {
            	cout << "FAILED TO LOAD TEXTURE" << endl;
            	return 0;
            }
                
            
    
        return 0;
    }


   
    
