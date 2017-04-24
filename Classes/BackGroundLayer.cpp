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

	// ���ҽ� �Ŵ������� �� �ؽ��� �ҷ�����
	ResourcesManager* resources_manager = TemplateSingleton<ResourcesManager>::get_instance();
	Texture2D* texture = resources_manager->load_resources("(8)Orbital Death.chk");
	assert(texture);

	// �ؽ��ķ� ��������Ʈ ��ü �����
	Sprite* map_sprite = cocos2d::Sprite::createWithTexture(texture);
	// �� ��ġ ����
	// ������ â ������ �� ���� �Ʒ����� �������� y ���� ����
	map_sprite->setPosition(0, 96);
	map_sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(map_sprite, 0);
	end = clock();
	CCLOG("map loading time : %d", end - start);
}
