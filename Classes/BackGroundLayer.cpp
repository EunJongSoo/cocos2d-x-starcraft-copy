/****************************
수정일 : 2017-02-21
작성자 : 은종수
파일명 : BackGroundLayer.cpp
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

	// 맵 화면에 띄위기
	StarCraftMapCreator* map_creator = new StarCraftMapCreator;
	Sprite* map_sprite = map_creator->create_bitmap_mapdata(_map_data);
	assert(map_sprite);

	delete map_creator;

	// 맵 위치 조정
	// 유아이 창 위쪽이 맵 가장 아래쪽이 나오도록 y 값을 변경
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
	// 미니노드를 만들고 인덱스와 플레그를 저장
	for (int h = 0; h < mini_height; ++h) {
		for (int w = 0; w < mini_width; ++w) {
			MiniNode* mini_node = new MiniNode;

			int mega_tile_x = w / 4;
			int mega_tile_y = h / mini_width4;
			int mega_tile_num = _map_data->find_mega_tile_num(mega_tile_x, mega_tile_y);

			// 메가타일에서의 가로 크기 확인
			// 메가타일에서의 세로 크기 확인
			// 세로 크기가 커진만큼 4를 곱함(4는 미니타일의 가로 개수)
			// 메가 타일내에서 몇번째 미니타일인지 확인
			int mini_tile_index = (w % 4) + ((h % 4) * 4);
			int flag = _map_data->find_mini_tile_flag(mega_tile_num, mini_tile_index);

			mini_node->set_idx_mini_node(w + h * mini_width, flag);
			mini_node_vector.push_back(mini_node);
		}
	}

	int i = 0;
	// 마지막 노드 번호
	int mini_height_width = mini_height * mini_width;
	// 뒤에서 두번째줄 마지막 노드번호
	int mini_height_width2 = mini_height_width - mini_width;

	int mini_width_plus = mini_width + 1;
	int mini_width_minus = mini_width - 1;

	// 미니노드에 주변 통행가능 저장
	for (int h = 0; h < mini_height; ++h) {
		for (int w = 0; w < mini_width; ++w) {
			// 위쪽
			// 세로 첫번째줄 노드인지 확인
			// i가 가로줄 보다 크거나 같으면 둘째 줄 이후다.
			if (i >= mini_width) {
				if (mini_node_vector[i - mini_width]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::up);
				}
			}
			// 아래쪽
			// 세로 마지막줄 노드인지 확인
			if (i < mini_height_width2) {
				if (mini_node_vector[i + mini_width]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::down);
				}
			}
			// 왼쪽
			// 가로 첫번째 노드인지 확인해서 제외한다.
			if (i % mini_width != 0) {
				if (mini_node_vector[i - 1]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::left);
				}
			}
			
			// 오른쪽
			// 가로 마지막 노드인지 확인해서 제외한다.
			if (i % mini_width != mini_width_minus) {
				if (mini_node_vector[i + 1]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::right);
				}
			}
			
			// 왼쪽 위
			// 세로 첫번째줄 노드가 아니면서, 가로 첫번째줄 노드가 아닐것
			if (i >= mini_width && i % mini_width != 0) {
				if (mini_node_vector[i - mini_width_plus]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::up_left);
				}
			}

			// 오른쪽 위
			// 세로 첫번째줄 노드가 아니면서, 가로 마지막줄 노드가 아닐것
			if (i >= mini_width && i % mini_width != mini_width_minus) {
				if (mini_node_vector[i - mini_width_minus]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::up_left);
				}
			}

			// 왼쪽 아래
			// 세로 마지막줄 노드가 아니면서, 가로 첫번째줄 노드가 아닐것
			if (i < mini_height_width2 && i % mini_width != 0) {
				if (mini_node_vector[i + mini_width_minus]->is_walkable()) {
					mini_node_vector[i]->set_open_node((char)MiniNode::node_dir_check::down_left);
				}
			}

			// 오른쪽 아래
			// 세로 마지막줄 노드가 아니면서, 가로 마지막줄 노드가 아닐것
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

	// 시간 체크
	start = clock();
	// 각 메가노드에 미니노드를 추가한다.
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

	// 각 슈퍼노드에 메가노드를 추가한다.
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
