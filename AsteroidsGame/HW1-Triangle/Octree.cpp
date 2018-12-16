/*
Authors: Barrington Campbell & Kaloyana Mihova
Class: IGME.309.03
Proffesor: David Schwartz

File Name: Octree.cpp
Description: Octree management. This code isn't working how it's supposed to unfortunately. Didn't have
enough time to debug and submit on time.
*/
#include "Octree.h"


Octree::Octree(vec3 position, float size, int depth)
{
	node = OctreeNode(position, size);
	node.Subdivied();
}


Octree::~Octree()
{
}

int Octree::GetIndexOfPosition(vec3 lookupPosition, vec3 nodePosition)
{
	int index = 0;

	//Bit manipulation to get index
	index |= lookupPosition.x > nodePosition.x ? 2 : 0;
	index |= lookupPosition.y > nodePosition.y ? 4 : 0;
	index |= lookupPosition.z > nodePosition.z ? 1 : 0;

	return index;
}