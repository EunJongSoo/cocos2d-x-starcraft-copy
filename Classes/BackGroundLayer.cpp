#include "BackGroundLayer.h"
#include "MapData.h"
#include "StarcraftMapCreator.h"

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

	return map_data;
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
	


	
}
