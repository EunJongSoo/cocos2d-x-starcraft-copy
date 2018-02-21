/****************************
수정일 : 2017-02-21
작성자 : 은종수
파일명 : MegaNode.cpp
****************************/

#include <vector>
#include "MegaNode.h"
#include "MiniNode.h"

MegaNode::MegaNode() {}

MegaNode::MegaNode(int _index) : open_node(0), index(_index)
{}

MegaNode::~MegaNode()
{
}

void MegaNode::set_mini_node(MiniNode * _mini_node)
{
	mini_node_vector.push_back(_mini_node);
}

bool MegaNode::is_open_node(char _dir)
{
	return open_node & _dir;
}

void MegaNode::check_open_node()
{
	if (mini_node_vector[0]->is_open_node((char)MiniNode::node_dir_check::up) &&
		mini_node_vector[1]->is_open_node((char)MiniNode::node_dir_check::up) &&
		mini_node_vector[2]->is_open_node((char)MiniNode::node_dir_check::up) &&
		mini_node_vector[3]->is_open_node((char)MiniNode::node_dir_check::up)) {
		set_open_node((char)MiniNode::node_dir_check::up);
	}

	if (mini_node_vector[12]->is_open_node((char)MiniNode::node_dir_check::down) &&
		mini_node_vector[13]->is_open_node((char)MiniNode::node_dir_check::down) &&
		mini_node_vector[14]->is_open_node((char)MiniNode::node_dir_check::down) &&
		mini_node_vector[15]->is_open_node((char)MiniNode::node_dir_check::down)) {
		set_open_node((char)MiniNode::node_dir_check::down);
	}

	if (mini_node_vector[0]->is_open_node((char)MiniNode::node_dir_check::left) &&
		mini_node_vector[4]->is_open_node((char)MiniNode::node_dir_check::left) &&
		mini_node_vector[8]->is_open_node((char)MiniNode::node_dir_check::left) &&
		mini_node_vector[12]->is_open_node((char)MiniNode::node_dir_check::left)) {
		set_open_node((char)MiniNode::node_dir_check::left);
	}

	if (mini_node_vector[3]->is_open_node((char)MiniNode::node_dir_check::right) &&
		mini_node_vector[7]->is_open_node((char)MiniNode::node_dir_check::right) &&
		mini_node_vector[11]->is_open_node((char)MiniNode::node_dir_check::right) &&
		mini_node_vector[15]->is_open_node((char)MiniNode::node_dir_check::right)) {
		set_open_node((char)MiniNode::node_dir_check::right);
	}
}

void MegaNode::set_open_node(char _dir)
{
	open_node |= _dir;
}