/*
Authors: Barrington Campbell & Kaloyana Mihova
Class: IGME.309.03
Proffesor: David Schwartz

File Name: Mesh.h
Description: Mesh class manages what mesh information is being imported and manipulated
*/
#pragma once
#include "Standard_Includes.h"
#include "Shader.h"
using namespace std;
using namespace glm;

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};
class Mesh
{
public:
	//Mesh Data
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	//Functions
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	void Draw(Shader shader);
	
private:
	//Render data
	unsigned int VAO, VBO, EBO;
	void setupMesh(); //Setup mesh data
};


