#include "Unit.h"
#include "UnitWeapon.h"
#include "UnitAnimation.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

UnitWeapon::UnitWeapon(Unit* const _target) {
	// 타겟 설정
	this->set_target(_target);

	// 공격력
	attack = 10;
	frame = 0;
	max_frame = 10;
	
	// 애니메이션 초기화
	weapon_animation = new UnitAnimation(marine_weapon);

	// 초기 이미지 세팅
	char str[16];
	auto sprite_cache = SpriteFrameCache::getInstance();
	sprintf_s(str, sizeof(str), "tspark000.bmp");
	this->initWithSpriteFrame(sprite_cache->spriteFrameByName(str));
	SimpleAudioEngine::getInstance()->playEffect("sound/marine/tmafir00.wav");
}

UnitWeapon::~UnitWeapon() {

}

void UnitWeapon::run_action_animation(const float _dt) {
	this->setPosition(target->getPosition());
	if (weapon_animation->run_action_aniamtion(unit_state::weapon, this, _dt)) {
		this->setVisible(false);
	}
}

void UnitWeapon::set_target(Unit* const _target) {
	target = _target;
}