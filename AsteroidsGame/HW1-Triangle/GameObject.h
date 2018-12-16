/*
Authors: Barrington Campbell & Kaloyana Mihova
Class: IGME.309.03
Proffesor: David Schwartz

File Name: GameObject.h
Description: GameObject header file. This is the aparent to every object type that will
			 be rendered in game. 
*/
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
	vector<Mesh> meshes;		//Meshes assoiciated to the loaded in obj file
	string directory;			//Location of the obj file
	bool gammaCorrection;		//Screen gamma correction

	/* Physics Data */
	vec3 position;				//Position of the model in "Model" space

	/*  Functions   */
	GameObject(string const &path);
	void Draw(Shader shader);	//Send information to GPU in order to be drawn
	Mesh* model()				//Model returned from loading the file
	{
		return &meshes[0];
	}
	vec3 direction;				//Forward direction of the object (Phsics)
	virtual vec3 getMinBox() { return position - 2.5f; } //Minimum vec3 positions for AABB
	virtual vec3 getMaxBox() { return position + 2.5f; } //Maximum vec3 positions for AABB
	~GameObject();

private:
	void loadModel(string const &path);	//Load the OBJ file from a given path
	void processNode(aiNode *node, const aiScene *scene); //Process nodes assocaited tot he mesh
	Mesh processMesh(aiMesh *mesh, const aiScene *scene); //Process the full mesh after being loaded in
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName); //Load textures
	void AveragePosition(); //Average positino of this object
};