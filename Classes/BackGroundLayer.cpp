#include "BackGroundLayer.h"
#include "MapData.h"
#include "StarcraftMapCreator.h"

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

MapData * BackGroundLayer::create_map()
{
	MapData* map_data = new MapData;
	map_data->load_map_data("(8)Orbital Death.chk");
	
	create_map_sprite(map_data);
	create_map_tree(map_data);
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

void BackGroundLayer::create_map_tree(MapData * const _map_data)
{
	int width = _map_data->get_width();
	int height = _map_data->get_height();

	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			int mega_tile_num = _map_data->find_mega_tile_num(w, h);

			MegaNode mega_node;

			for (int mini_h = 0; mini_h < 4; ++mini_h) {
				for (int mini_w = 0; mini_w < 4; ++mini_w) {
					int index = mini_h * 4 + mini_w;
					// 미니 노드를 만든다.
					MiniNode* mini_node = new MiniNode;
					
					// 미니타일 플레그를 미니노드에 넣어야한다.
					_map_data->find_mini_tile_flag(mega_tile_num, index);


					mega_node.add_mini_node(mini_node, index);
				}
			}
			mega_node;
		}
	}
}
