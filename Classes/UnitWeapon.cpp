#include "Unit.h"
#include "UnitWeapon.h"
#include "UnitAnimation.h"
#include "SimpleAudioEngine.h"

#include "TemplateSingleton.h"
#include "ResourcesManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

UnitWeapon::UnitWeapon(Unit* const _target, const unit_type _unit_tpye) {
	// Ÿ�� ����
	this->set_target(_target);

	// ���ݷ�
	attack = 10;
	
	// �ִϸ��̼� �ʱ�ȭ
	weapon_animation = new UnitAnimation(_unit_tpye, this);
	auto resources_manager = TemplateSingleton<ResourcesManager>::get_instance();

	// ������ �ʿ�
	// �ʱ� �̹��� ����
	char str[16];
	sprintf_s(str, sizeof(str), "tspark0000.bmp");
	this->initWithTexture(resources_manager->load_resources(player_color::none, str));
	SimpleAudioEngine::getInstance()->playEffect("sound/marine/tmafir00.wav");
}

// �����Ҵ� ��������
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