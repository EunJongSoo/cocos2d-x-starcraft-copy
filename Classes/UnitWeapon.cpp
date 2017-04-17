#include "Unit.h"
#include "UnitWeapon.h"
#include "UnitAnimation.h"
#include "SimpleAudioEngine.h"

#include "TemplateSingleton.h"
#include "ResourcesManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

UnitWeapon::UnitWeapon(Unit* const _target, const unit_type _unit_tpye) {
	// 타겟 설정
	this->set_target(_target);

	// 공격력
	attack = 10;
	
	// 애니메이션 초기화
	weapon_animation = new UnitAnimation(_unit_tpye, this);
	auto resources_manager = TemplateSingleton<ResourcesManager>::get_instance();

	// 데이터 필요
	// 초기 이미지 세팅
	char str[16];
	sprintf_s(str, sizeof(str), "tspark0000.bmp");
	this->initWithTexture(resources_manager->load_resources(player_color::none, str));
	SimpleAudioEngine::getInstance()->playEffect("sound/marine/tmafir00.wav");
}

// 동적할당 안전해제
UnitWeapon::~UnitWeapon() {
	SAFE_DELETE(weapon_animation);
}

void UnitWeapon::run_action_animation(const float _dt) {
	this->setPosition(target->getPosition());
	if (weapon_animation->run_action_aniamtion(unit_state::idle, this, _dt)) {
		this->setVisible(false);
	}
}

void UnitWeapon::set_target(Unit* const _target) {
	target = _target;
}