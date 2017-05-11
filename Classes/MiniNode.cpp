#include "MiniNode.h"

MiniNode::MiniNode():
	open_node(0)
{
}

MiniNode::~MiniNode()
{
}

bool MiniNode::is_open_node(char _dir)
{
	return open_node & _dir;
}

void MiniNode::set_mini_node(unsigned int _index, unsigned short _flag)
{
	index = _index;
	mini_tile_flags = _flag;
}

void MiniNode::check_open_node()
{


}
