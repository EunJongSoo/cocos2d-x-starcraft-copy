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

void BackGroundLayer::create_map_tree(MapData * const _map_data)
{
	


	
}
