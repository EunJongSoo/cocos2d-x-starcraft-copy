/****************************
수정일 : 2017-02-21
작성자 : 은종수
파일명 : MiniNode.cpp
****************************/

#include "MiniNode.h"

MiniNode::MiniNode():
	open_node(0)
{
}

MiniNode::~MiniNode()
{
}

bool MiniNode::is_walkable()
{
	return mini_tile_flags & 0x0001;
}

bool MiniNode::is_open_node(const char _dir)
{
	return open_node & _dir;
}

void MiniNode::set_open_node(const char _dir)
{
	open_node |= _dir;
}

void MiniNode::set_idx_mini_node(const int _index, const unsigned short _flag)
{
	index = _index;
	mini_tile_flags = _flag;
}