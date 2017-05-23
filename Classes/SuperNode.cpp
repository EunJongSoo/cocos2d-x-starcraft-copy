#include <vector>
#include "SuperNode.h"

SuperNode::SuperNode()
{
}

SuperNode::~SuperNode()
{
}

void SuperNode::set_mega_node(MegaNode * _mega_node)
{
	mega_node_vector.push_back(_mega_node);
}

void SuperNode::check_open_node()
{
}

bool SuperNode::is_open_node(char _dir)
{
	return open_node & _dir;
}

void SuperNode::set_open_node(char _dir)
{
	open_node |= _dir;
}
