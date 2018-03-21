/****************************
수정일 : 2018-03-20
작성자 : 은종수
파일명 : UnitWeapon.cpp
****************************/

#include "Unit.h"
#include "UnitWeapon.h"
#include "UnitAnimation.h"
#include "SimpleAudioEngine.h"

#include "TemplateSingleton.h"
#include "ResourcesManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

/*
유닛 클래스의 run_action_animation 함수에서 생성되는 클래스이다.
타겟을 공격할때마다 공격 하는 이팩트 애니메이션을 만들어내면서
데미지를 전달하도록 만들고자 했다.

그런데 당장 만든 유닛이 마린뿐이고 마린의 공격 이팩트는
적 유닛 바로 위에 생기기 때문에 바로 상대 유닛 위에 만들어 지고 있다.

유닛에게 공격력을 전달받아서 상대를 공격해야 되는데 공격력 자체를 전달받지 않고 있으며
타겟에게 딱히 데미지를 주고 있지도 않다.

어쩌다가 손을 놨는지도 모르겠지만 만들다만 클래스다.
그런데도 굳이 포스팅을 한 이유는 뭘 만들다 말았는지 확인하기 위해서다.

1. 유닛에게서 공격력을 받지 않음
2. 유닛 웨폰이 스스로 어떤 종류인지를 구분하지 않고 있음
3. 종류를 구분했을때 발사되는 방법이 달라짐
4. 데미지를 전달하는 방식이 없음
5. 초기 세팅 부분 데이터 불러오는 시스템 구축

나름 처음 사운드를 사용한 부분이 나왔는데
사실은 구색맞추기로 대충 코딩한게 사실이다.
*/
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
	this->initWithTexture(resources_manager->load_texture2d(str));
	SimpleAudioEngine::getInstance()->playEffect("sound/marine/tmafir00.wav");
}

// 동적할당 안전해제
UnitWeapon::~UnitWeapon() {
	SAFE_DELETE(weapon_animation);
}

void UnitWeapon::run_action_animation(const float _dt) {
	this->setPosition(target->getPosition());
	if (weapon_animation->run_action_aniamtion(UnitState::idle, _dt)) {
		this->setVisible(false);
	}
}

void UnitWeapon::set_target(Unit* const _target) {
	target = _target;
}