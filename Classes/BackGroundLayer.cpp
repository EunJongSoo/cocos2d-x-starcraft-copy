#include "BackGroundLayer.h"

#include "TemplateSingleton.h"
#include "ResourcesManager.h"

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

void BackGroundLayer::create_map()
{
	ResourcesManager* resources_manager = TemplateSingleton<ResourcesManager>::get_instance();
	Texture2D* texture = resources_manager->load_resources("(8)Orbital Death.chk");
	assert(texture);
	Sprite* map_sprite = cocos2d::Sprite::createWithTexture(texture);
	map_sprite->setPosition(0, 0);
	map_sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(map_sprite);
}
