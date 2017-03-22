#include "UnitAnimation.h"
#include <string>

using namespace cocos2d;
using std::string;

UnitAnimation::UnitAnimation() : _max_frame(9), _frame(0) {
}

UnitAnimation::~UnitAnimation() {
}

bool UnitAnimation::init() {
	
	assert(Sprite::init());

	TextureCache* cache = Director::getInstance()->getTextureCache();
	

	auto sprite_cache = SpriteFrameCache::getInstance();
	sprite_cache->addSpriteFramesWithFile("unit/marine/down_right1/down_right1.plist","unit/marine/down_right1/down_right1.png");

	/*char str[64];
	for (int i = 0; i < _max_frame; ++i) {
		sprintf_s(str, sizeof(str), "unit/marine/down_right1/marine%d.png", i+4);
		texture[i] = cache->addImage(str);
	}
	this->initWithTexture(texture[0]);*/
	this->initWithSpriteFrame(sprite_cache->spriteFrameByName("marine1.bmp"));
	return true;
}

void UnitAnimation::run_action_animation() {
	auto sprite_cache = SpriteFrameCache::getInstance();
	char str[32];
	sprintf_s(str, sizeof(str), "marine%d.bmp", _frame++ + 4);
	this->setSpriteFrame(sprite_cache->spriteFrameByName(str));

	//this->setTexture(texture[_frame++]);
	if (_frame >= _max_frame) {
		_frame = 0;
	}
}
