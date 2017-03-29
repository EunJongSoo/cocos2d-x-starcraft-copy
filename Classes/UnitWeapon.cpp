#include "Unit.h"
#include "UnitWeapon.h"
#include "UnitAnimation.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

UnitWeapon::UnitWeapon(Unit* const _target) {
	// Ÿ�� ����
	this->set_target(_target);

	// ���ݷ�
	attack = 10;
	frame = 0;
	max_frame = 10;
	
	// �ִϸ��̼� �ʱ�ȭ
	weapon_animation = new UnitAnimation(marine_weapon);

	// �ʱ� �̹��� ����
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