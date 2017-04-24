#include "UiLayer.h"

#include "TemplateSingleton.h"
#include "ResourcesManager.h"

using namespace cocos2d;

UiLayer::UiLayer()
{
}

UiLayer::~UiLayer()
{
}

bool UiLayer::init()
{
	if (!Layer::init())
		return false;

	ResourcesManager* resources_manager = TemplateSingleton<ResourcesManager>::get_instance();
	Texture2D* texture = resources_manager->load_resources("tconsole.png");
	Sprite* sprite = cocos2d::Sprite::createWithTexture(texture);
	sprite->setPosition(0, 0);
	sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite, 0);
	
	return true;
}
