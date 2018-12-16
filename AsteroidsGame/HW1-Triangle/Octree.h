#pragma once
#include "Standard_Includes.h"
#include "GameObject.h"
class OctreeNode
{
	vec3 position; //Node position
	float size; //Size of the node
	vector<OctreeNode> *subnodes;
	vector<GameObject> value;
public:
	OctreeNode();
	OctreeNode(vec3 pos, float size);
	~OctreeNode();
	void Subdivied()
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

	bool isLeaf()
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

class Octree
{
public:
	enum OctreeIndex
	{
		BottomLeftFront = 0, //000
		BottomRightFront = 2, //010
		BottomRightBack = 3, //011
		BottomLeftBack = 1, //001
		TopLeftFront = 4, //100
		TopRightFront = 6, //110
		TopRightBack = 7, //111
		TopLeftBack = 5, //101
	};
	Octree(vec3 position, float size, int depth);
	~Octree();
private:
	int depth; //Resolution of Octree
	
	OctreeNode node;

	int GetIndexOfPosition(vec3 lookupPosition, vec3 nodePosition)
	{
		int index = 0;

		//Bit manipulation to get index
		index |= lookupPosition.x > nodePosition.x ? 2 : 0 ;
		index |= lookupPosition.y > nodePosition.y ? 4 : 0 ;
		index |= lookupPosition.z > nodePosition.z ? 1 : 0 ;

		return index;
	}

	

	
};

