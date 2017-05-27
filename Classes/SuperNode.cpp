#include <vector>
#include "SuperNode.h"
#include "MegaNode.h"
#include "MiniNode.h"

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
	if (mega_node_vector[0]->is_open_node((char)MiniNode::node_dir_check::up) ||
		mega_node_vector[1]->is_open_node((char)MiniNode::node_dir_check::up)) {
		set_open_node((char)MiniNode::node_dir_check::up);
	}

	if (mega_node_vector[2]->is_open_node((char)MiniNode::node_dir_check::down) ||
		mega_node_vector[3]->is_open_node((char)MiniNode::node_dir_check::down)) {
		set_open_node((char)MiniNode::node_dir_check::down);
	}

	if (mega_node_vector[0]->is_open_node((char)MiniNode::node_dir_check::left) ||
		mega_node_vector[2]->is_open_node((char)MiniNode::node_dir_check::left)) {
		set_open_node((char)MiniNode::node_dir_check::left);
	}

	if (mega_node_vector[1]->is_open_node((char)MiniNode::node_dir_check::right) ||
		mega_node_vector[3]->is_open_node((char)MiniNode::node_dir_check::right)) {
		set_open_node((char)MiniNode::node_dir_check::right);
	}
}

bool SuperNode::is_open_node(char _dir)
{
	return open_node & _dir;
}

void SuperNode::set_open_node(char _dir)
{
	open_node |= _dir;
}
