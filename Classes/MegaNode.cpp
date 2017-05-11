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

// MegaNode�� ����� �����ִ��� Ȯ��
void MegaNode::check_open_node()
{
	check_mini_node(0, 1, 2, 3, (char)MiniNode::node_dir_check::up);
	check_mini_node(0, 4, 6, 8, (char)MiniNode::node_dir_check::left);
	check_mini_node(3, 5, 7, 11, (char)MiniNode::node_dir_check::right);
	check_mini_node(8, 9, 10, 11, (char)MiniNode::node_dir_check::down);
}

// MegaNode�� �Ѹ��� �̷�� 4���� MiniNode�� ��ȣ�� ������ �޾Ƽ� �˻��Ѵ�.
void MegaNode::check_mini_node(int _idx1, int _idx2, int _idx3, int _idx4, char _dir) {
	if (mini_node_vector[_idx1]->is_open_node(_dir)) {
		if (mini_node_vector[_idx2]->is_open_node(_dir)) {
			if (mini_node_vector[_idx3]->is_open_node(_dir)) {
				if (mini_node_vector[_idx4]->is_open_node(_dir)) {

					// �Ű������� ���� ������ MiniNode 4���� ��� ���������� MegaNode�� �����ش�.
					// ��Ʈ ����, or �������� ���� ����
					open_node |= _dir;
				}
			}
		}
	}
}

// �Ű������� ���� ��ȣ�� MiniTile�� �����ڸ��� Tile���� Ȯ���Ѵ�.
bool MegaNode::is_side_mini_tile(int _index) {
	return !(_index == 6 || _index == 7 || _index == 10 || _index == 11);
}

