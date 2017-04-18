#include "BackGroundLayer.h"
#include "MapManager.h"
#include "Header.h"

using namespace cocos2d;

BackGroundLayer::BackGroundLayer()
{
}

BackGroundLayer::~BackGroundLayer()
{
	SAFE_DELETE(map_manager);
}

bool BackGroundLayer::init()
{
	if (!Layer::init())
		return false;

	map_manager = new MapManager("(8)Orbital Death.chk");


	return true;
}

void BackGroundLayer::create_map()
{
	int size_x = map_manager->get_map_size_width();
	int size_y = map_manager->get_map_size_height();
	float pos_y = 0.0f, pos_x = 0.0f;

	for (int y = 0; y < size_y; ++y) {
		for (int x = 0; x < size_x; ++x) {
			Sprite* sprite = map_manager->get_map_sprite(x, size_y - y);
			Size size = sprite->getContentSize();
			pos_y = y * size.height;
			pos_x = x * size.width;
			sprite->setPosition(pos_x, pos_y);
			sprite->setAnchorPoint(Vec2::ZERO);
			this->addChild(sprite);
		}
	}
}
