/****************************
수정일 : 2018-03-20
작성자 : 은종수
파일명 : UnitWeapon.h
****************************/

#ifndef UNIT_WEAPON_H_
#define UNIT_WEAPON_H_

#include "cocos2d.h"
#include "Header.h"

// class 전방선언
class Unit;
class UnitAnimation;

/*줄도 짧지만 유닛 클래스를 봤으면
크게 이해하기 어려운 부분이 없는 간단한 클래스다
사실 이렇게 간단한건 아직 미완성이라서 그런 부분이 있다.*/

class UnitWeapon : public cocos2d::Sprite {
public:
	UnitWeapon(Unit* const _target, const unit_type _unit_tpye);
	~UnitWeapon();
	/*유닛에 있던 함수와 동일하다.
	공격하는 미사일들도 애니메이션이 있으니 동일하게 있는거다
	*/
	void run_action_animation(const float _dt);
	/*타겟을 설정하는 함수다*/
	void set_target(Unit* const _target);
private:
	UnitWeapon() {};

	/*공격력과 타겟을 저장할 변수, 그리고 유닛과 똑같이 애니메이션 변수다*/
	unsigned int attack;
	Unit* target;
	UnitAnimation* weapon_animation;
};

#endif