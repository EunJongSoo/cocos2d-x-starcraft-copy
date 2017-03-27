#include "UnitWeapon.h"

using namespace cocos2d;

UnitWeapon::UnitWeapon() {
}

UnitWeapon::~UnitWeapon()
{
}

bool UnitWeapon::init()
{
	assert(Sprite::init());

	_attack = 10;
	_frame = 0;
	_max_frame = 10;
	char str[16];

	auto sprite_cache = SpriteFrameCache::getInstance();
	for (int i = 0; i < 10; ++i) {
		sprintf_s(str, sizeof(str), "tspark%03d.bmp", i);
		animation_vector.push_back(sprite_cache->spriteFrameByName(str));
	}
	this->initWithSpriteFrame(animation_vector[0]);

	return true;
}


void UnitWeapon::run_action_weapon_animation() {
	this->setSpriteFrame(animation_vector[_frame++]);
	if (_frame >= _max_frame) {
		_frame = 0;
		this->setVisible(false);
	}
}