/*
Authors: Barrington Campbell & Kaloyana Mihova
Class: IGME.309.03
Proffesor: David Schwartz

File Name: Octree.h
Description: Octree management. This code isn't working how it's supposed to unfortunately. Didn't have
			 enough time to debug and submit on time.
*/

#pragma once
#include "Standard_Includes.h"
#include "GameObject.h"

//Octree node used within the octree
class OctreeNode
{
	vec3 position; //Node position
	float size; //Size of the node
	vector<OctreeNode> *subnodes; //Subdivied nodes
	vector<GameObject> value;	  //Values related to subnodes returned to be checked
public:
	OctreeNode();
	OctreeNode(vec3 pos, float size);
	~OctreeNode();

	void Subdivied() //Subdivide different node to be used in Octree
	{
		subnodes = new vector<OctreeNode>;
		for (int i = 0; i < subnodes->size(); i++)
		{
			vec3 newPos = position;

			if ((i & 2) == 4)
			{
				newPos.x += size * 0.25f;
			}
			else
			{
				newPos.x -= size * 0.25f;
			}

			if ((i & 4) == 4)
			{
				newPos.y += size * 0.25f;
			}
			else
			{
				newPos.y -= size * 0.25f;
			}

			if ((i & 1) == 4)
			{
				newPos.z += size * 0.25f;
			}
			else
			{
				newPos.z -= size * 0.25f;
			}
			(*subnodes)[i] = OctreeNode(newPos, size * 0.5f);
		}
	}

	bool isLeaf() //Check to see if there is a leafnode left
	{
		return subnodes == nullptr;
	}
};

OctreeNode::OctreeNode()
{

}
OctreeNode::OctreeNode(vec3 pos, float size)
{
	position = pos;
	this->size = size;
}
OctreeNode::~OctreeNode() {}


//Octree container
class Octree
{
public:
	enum OctreeIndex //Binary index used to lookup octree node positions
	{
		BottomLeftFront = 0,	//000
		BottomRightFront = 2,	//010
		BottomRightBack = 3,	//011
		BottomLeftBack = 1,		//001
		TopLeftFront = 4,		//100
		TopRightFront = 6,		//110
		TopRightBack = 7,		//111
		TopLeftBack = 5,		//101
	};
	Octree(vec3 position, float size, int depth);
	~Octree();
private:
	int depth; //Resolution of Octree
	OctreeNode node; //Root octreenode

	int GetIndexOfPosition(vec3 lookupPosition, vec3 nodePosition);
};

