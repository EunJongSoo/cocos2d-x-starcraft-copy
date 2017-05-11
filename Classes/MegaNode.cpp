#include "MegaNode.h"
#include "MiniNode.h"
#include <vector>

MegaNode::MegaNode()
{
}

MegaNode::~MegaNode()
{
}

void MegaNode::add_mini_node(MiniNode * _node, int _index)
{
	if (is_side_mini_tile(_index)) {
		mini_node_vector.push_back(_node);
	}
}

// MegaNode의 사방이 열려있는지 확인
void MegaNode::check_open_node()
{
	check_mini_node(0, 1, 2, 3, (char)MiniNode::node_dir_check::up);
	check_mini_node(0, 4, 6, 8, (char)MiniNode::node_dir_check::left);
	check_mini_node(3, 5, 7, 11, (char)MiniNode::node_dir_check::right);
	check_mini_node(8, 9, 10, 11, (char)MiniNode::node_dir_check::down);
}

// MegaNode의 한면을 이루는 4개의 MiniNode의 번호와 방향을 받아서 검사한다.
void MegaNode::check_mini_node(int _idx1, int _idx2, int _idx3, int _idx4, char _dir) {
	if (mini_node_vector[_idx1]->is_open_node(_dir)) {
		if (mini_node_vector[_idx2]->is_open_node(_dir)) {
			if (mini_node_vector[_idx3]->is_open_node(_dir)) {
				if (mini_node_vector[_idx4]->is_open_node(_dir)) {

					// 매개변수로 받은 방향의 MiniNode 4개가 모두 열려있으면 MegaNode도 열어준다.
					// 비트 연산, or 연산으로 값을 저장
					open_node |= _dir;
				}
			}
		}
	}
}

// 매개변수로 받은 번호의 MiniTile이 가장자리의 Tile인지 확인한다.
bool MegaNode::is_side_mini_tile(int _index) {
	return !(_index == 6 || _index == 7 || _index == 10 || _index == 11);
}

