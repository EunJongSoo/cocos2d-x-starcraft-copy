/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : MapTree.cpp
****************************/

#include <cmath>
#include <vector>
#include "MapTree.h"
#include "SuperNode.h"
#include "MegaNode.h"

MapTree::MapTree()
{
}

MapTree::~MapTree()
{
}

void MapTree::set_super_node(SuperNode * _super_node)
{
	super_node_vector.push_back(_super_node);
}

//bool MapTree::is_open_node(const float x, const float y, const char _dir, const int _node_size)
//{
//	
//	// _node_size로 슈퍼, 메가, 미니 노드를 구분
//	switch (_node_size)
//	{
//	case (int)NodeSize::mini_node: {
//		return true;
//	} break;
//	case (int)NodeSize::mega_node: {
//		int super_x = floor(x / 2 + 0.5);
//		int super_y = floor(y / 2 + 0.5);
//		SuperNode* super_node = super_node_vector.at(super_y * width + super_x);
//		return super_node->get_mega_node(1)->is_open_node(_dir);
//	} break;
//	case (int)NodeSize::super_node: {
//		return super_node_vector.at(y * width + x)->is_open_node(_dir);
//	} break;
//	}
//	return false;
//}