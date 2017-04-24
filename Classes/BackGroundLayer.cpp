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
	int start = 0, end = 0;
	start = clock();

	// 리소스 매니저에서 맵 텍스쳐 불러오기
	ResourcesManager* resources_manager = TemplateSingleton<ResourcesManager>::get_instance();
	Texture2D* texture = resources_manager->load_resources("(8)Orbital Death.chk");
	assert(texture);

	// 텍스쳐로 스프라이트 개체 만들기
	Sprite* map_sprite = cocos2d::Sprite::createWithTexture(texture);
	// 맵 위치 조정
	// 유아이 창 위쪽이 맵 가장 아래쪽이 나오도록 y 값을 변경
	map_sprite->setPosition(0, 96);
	map_sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(map_sprite, 0);
	end = clock();
	CCLOG("map loading time : %d", end - start);
}
