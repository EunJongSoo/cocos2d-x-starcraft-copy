/****************************
������ : 2017-02-21
�ۼ��� : ������
���ϸ� : BackGroundLayer.cpp
****************************/

#include <vector>
#include "BackGroundLayer.h"
#include "MapData.h"
#include "MapTree.h"
#include "StarcraftMapCreator.h"

#include "SuperNode.h"
#include "MegaNode.h"
#include "MiniNode.h"

using namespace cocos2d;

BackGroundLayer::BackGroundLayer()
{
}

BackGroundLayer::~BackGroundLayer()
{
}

bool BackGroundLayer::init()
{
	if (!Layer::init())
		return false;

	return true;
}

bool BackGroundLayer::create_map(MapData* const _map_data, MapTree* const _map_tree)
{
	_map_data->load_map_data("(8)Orbital Death.chk");
	
	create_map_sprite(_map_data);
	create_map_tree(_map_data, _map_tree);

	return true;
}

void BackGroundLayer::create_map_sprite(MapData * const _map_data)
{
	int start = 0, end = 0;
	start = clock();

	// �� ȭ�鿡 ������
	StarCraftMapCreator* map_creator = new StarCraftMapCreator;
	Sprite* map_sprite = map_creator->create_bitmap_mapdata(_map_data);
	assert(map_sprite);

	delete map_creator;

	// �� ��ġ ����
	// ������ â ������ �� ���� �Ʒ����� �������� y ���� ����
	map_sprite->setPosition(0, 96);
	map_sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(map_sprite, 0);
	end = clock();
	CCLOG("map loading time : %d", end - start);
}

void BackGroundLayer::create_map_tree(MapData * const _map_data, MapTree* const _map_tree)
{
	int mega_height = _map_data->get_height();
	int mega_width = _map_data->get_width();

	int mini_height = mega_height * 4;
	int mini_width = mega_width * 4;

	int mini_width4 = mini_width * 4;
	std::vector<MiniNode*> mini_node_vector;

	int start, end;
	start = clock();
	// �̴ϳ�带 ����� �ε����� �÷��׸� ����
	for (int h = 0; h < mini_height; ++h) {
		for (int w = 0; w < mini_width; ++w) {
			MiniNode* mini_node = new MiniNode;

			int mega_tile_x = w / 4;
			int mega_tile_y = h / mini_width4;
			int mega_tile_num = _map_data->find_mega_tile_num(mega_tile_x, mega_tile_y);

			// �ް�Ÿ�Ͽ����� ���� ũ�� Ȯ��
			// �ް�Ÿ�Ͽ����� ���� ũ�� Ȯ��
			// ���� ũ�Ⱑ Ŀ����ŭ 4�� ����(4�� �̴�Ÿ���� ���� ����)
			// �ް� Ÿ�ϳ����� ���° �̴�Ÿ������ Ȯ��
			int mini_tile_index = (w % 4) + ((h % 4) * 4);
			int flag = _map_data->find_mini_tile_flag(mega_tile_num, mini_tile_index);

			mini_node->set_idx_mini_node(w + h * mini_width, flag);
			mini_node_vector.push_back(mini_node);
		}
	}

	int i = 0;
	// ������ ��� ��ȣ
	int mini_height_width = mini_height * mini_width;
	// �ڿ��� �ι�°�� ������ ����ȣ
	int mini_height_width2 = mini_height_width - mini_width;

	int mini_width_plus = mini_width + 1;
	int mini_width_minus = mini_width - 1;

	// �̴ϳ�忡 �ֺ� ���డ�� ����
	for (int h = 0; h < mini_height; ++h) {
		for (int w = 0; w < mini_width; ++w) {
			// ����
			// ���� ù��°�� ������� Ȯ��
			// i�� ������ ���� ũ�ų� ������ ��° �� ���Ĵ�.
			if (i >= mini_width) {
				if (mini_node_vector[i - mini_width]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::up);
				}
			}
			// �Ʒ���
			// ���� �������� ������� Ȯ��
			if (i < mini_height_width2) {
				if (mini_node_vector[i + mini_width]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::down);
				}
			}
			// ����
			// ���� ù��° ������� Ȯ���ؼ� �����Ѵ�.
			if (i % mini_width != 0) {
				if (mini_node_vector[i - 1]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::left);
				}
			}
			
			// ������
			// ���� ������ ������� Ȯ���ؼ� �����Ѵ�.
			if (i % mini_width != mini_width_minus) {
				if (mini_node_vector[i + 1]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::right);
				}
			}
			
			// ���� ��
			// ���� ù��°�� ��尡 �ƴϸ鼭, ���� ù��°�� ��尡 �ƴҰ�
			if (i >= mini_width && i % mini_width != 0) {
				if (mini_node_vector[i - mini_width_plus]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::up_left);
				}
			}

			// ������ ��
			// ���� ù��°�� ��尡 �ƴϸ鼭, ���� �������� ��尡 �ƴҰ�
			if (i >= mini_width && i % mini_width != mini_width_minus) {
				if (mini_node_vector[i - mini_width_minus]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::up_left);
				}
			}

			// ���� �Ʒ�
			// ���� �������� ��尡 �ƴϸ鼭, ���� ù��°�� ��尡 �ƴҰ�
			if (i < mini_height_width2 && i % mini_width != 0) {
				if (mini_node_vector[i + mini_width_minus]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::down_left);
				}
			}

			// ������ �Ʒ�
			// ���� �������� ��尡 �ƴϸ鼭, ���� �������� ��尡 �ƴҰ�
			if (i < mini_height_width2 && i % mini_width != mini_width_minus) {
				if (mini_node_vector[i + mini_width_plus]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::down_right);
				}
			}

			++i;
		}
	}

	end = clock();
	CCLOG("mini node create time: %d", end - start);

	std::vector<MegaNode*> mega_node_vector;

	// �ð� üũ
	start = clock();
	// �� �ް���忡 �̴ϳ�带 �߰��Ѵ�.
	for (int h = 0; h < mega_height; ++h) {
		for (int w = 0; w < mega_width; ++w) {
		
			int h_correction = h * mini_width4;
			int line1 = w * 4 + h_correction;
			int line2 = line1 + mini_width;
			int line3 = line2 + mini_width;
			int line4 = line3 + mini_width;

			MegaNode* mega_node = new MegaNode(h * mega_width + w);

			mega_node->set_mini_node(mini_node_vector[line1]);
			mega_node->set_mini_node(mini_node_vector[line1 + 1]);
			mega_node->set_mini_node(mini_node_vector[line1 + 2]);
			mega_node->set_mini_node(mini_node_vector[line1 + 3]);

			mega_node->set_mini_node(mini_node_vector[line2]);
			mega_node->set_mini_node(mini_node_vector[line2 + 1]);
			mega_node->set_mini_node(mini_node_vector[line2 + 2]);
			mega_node->set_mini_node(mini_node_vector[line2 + 3]);

			mega_node->set_mini_node(mini_node_vector[line3]);
			mega_node->set_mini_node(mini_node_vector[line3 + 1]);
			mega_node->set_mini_node(mini_node_vector[line3 + 2]);
			mega_node->set_mini_node(mini_node_vector[line3 + 3]);

			mega_node->set_mini_node(mini_node_vector[line4]);
			mega_node->set_mini_node(mini_node_vector[line4 + 1]);
			mega_node->set_mini_node(mini_node_vector[line4 + 2]);
			mega_node->set_mini_node(mini_node_vector[line4 + 3]);

			mega_node->check_open_node();

			mega_node_vector.push_back(mega_node);
		}
	}
	end = clock();
	CCLOG("mega node create time: %d", end - start);

	int super_height = mega_height / 2;
	int super_width = mega_width / 2;

	// �� ���۳�忡 �ް���带 �߰��Ѵ�.
	for (int h = 0; h < super_height; ++h) {
		for (int w = 0; w < super_width; ++w) {

			int h_correction = h * mega_width * 2;
			int line1 = w * 2 + h_correction;
			int line2 = line1 + mega_width;

			SuperNode* super_node = new SuperNode(h * super_width + w);

			super_node->set_mega_node(mega_node_vector[line1]);
			super_node->set_mega_node(mega_node_vector[line1 + 1]);
			
			super_node->set_mega_node(mega_node_vector[line2]);
			super_node->set_mega_node(mega_node_vector[line2 + 1]);

			super_node->check_open_node();

			_map_tree->set_super_node(super_node);
		}
	}
}
