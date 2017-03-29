#include "Unit.h"
#include "UnitWeapon.h"
#include "WeaponAnimation.h"

using namespace cocos2d;

UnitWeapon::UnitWeapon() {
	attack = 10;
	frame = 0;
	max_frame = 10;
	char str[16];

	auto sprite_cache = SpriteFrameCache::getInstance();
	for (int i = 0; i < 10; ++i) {
		sprintf_s(str, sizeof(str), "tspark%03d.bmp", i);
		animation_vector.push_back(sprite_cache->spriteFrameByName(str));
	}
	this->initWithSpriteFrame(animation_vector[0]);
}

UnitWeapon::~UnitWeapon() {
}

void UnitWeapon::run_action_animation(const float _dt) {
	this->setPosition(target->getPosition());
	
	
	weapon_animation->run_action_aniamtion(this, _dt);

	this->setSpriteFrame(animation_vector[frame++]);
	if (frame >= max_frame) {
		this->setVisible(false);
	}
}

void UnitWeapon::set_target(Unit * _target) {
	target = _target;
}