#include <vector>
#include "MapTree.h"

MapTree::MapTree()
{
}

MapTree::~MapTree()
{
}

void MapTree::set_super_tree(SuperNode * _super_node)
{
	super_node_vector.push_back(_super_node);
}
