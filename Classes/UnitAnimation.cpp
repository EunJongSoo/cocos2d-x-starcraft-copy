#include "UnitAnimation.h"
#include <string>

using namespace cocos2d;
using std::string;

UnitAnimation::UnitAnimation() : _max_frame(9) {
}

UnitAnimation::~UnitAnimation() {
}

bool UnitAnimation::init() {
	
	assert(Sprite::init());

	TextureCache* cache = Director::getInstance()->getTextureCache();
	char str[16];
	for (int i = 0; i < _max_frame; ++i) {
		sprintf_s(str, sizeof(str), "unit/marine/down/marine%d.bmp", i+3);
		texture[i] = cache->addImage(str);
	}
	return true;
}

void UnitAnimation::run_action_animation() {
	this->setTexture(texture[_frame++]);
	if (_frame >= _max_frame) {
		_frame = 0;
	}
}
