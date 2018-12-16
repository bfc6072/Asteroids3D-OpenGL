#include "Octree.h"


Octree::Octree(vec3 position, float size, int depth)
{
	node = OctreeNode(position, size);
	node.Subdivied();
}


Octree::~Octree()
{
}
