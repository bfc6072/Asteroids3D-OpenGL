#pragma once

#include "Standard_Includes.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"
#include "Mesh.h"
#include "Shader.h"
using namespace std;
class GameObject
{
public:
	/*  Model Data */
	vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	

	/* Physics Data */
	vec3 position;

	/*  Functions   */
	GameObject(string const &path);
	void Draw(Shader shader);
	Mesh* model()
	{
		return &meshes[0];
	}
	vec3 direction;
	virtual vec3 getMinBox() { return position - 2.5f; }
	virtual vec3 getMaxBox() { return position + 2.5f; }
	~GameObject();

private:
	

	void loadModel(string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	void AveragePosition();
};


//unsigned int TextureFromFile(const char *path, const string &directory, bool gamma);
