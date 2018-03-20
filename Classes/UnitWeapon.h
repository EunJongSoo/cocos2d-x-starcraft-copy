/****************************
������ : 2018-03-20
�ۼ��� : ������
���ϸ� : UnitWeapon.h
****************************/

#ifndef UNIT_WEAPON_H_
#define UNIT_WEAPON_H_

#include "cocos2d.h"
#include "Header.h"

// class ���漱��
class Unit;
class UnitAnimation;

/*�ٵ� ª���� ���� Ŭ������ ������
ũ�� �����ϱ� ����� �κ��� ���� ������ Ŭ������
��� �̷��� �����Ѱ� ���� �̿ϼ��̶� �׷� �κ��� �ִ�.*/

class UnitWeapon : public cocos2d::Sprite {
public:
	UnitWeapon(Unit* const _target, const unit_type _unit_tpye);
	~UnitWeapon();
	/*���ֿ� �ִ� �Լ��� �����ϴ�.
	�����ϴ� �̻��ϵ鵵 �ִϸ��̼��� ������ �����ϰ� �ִ°Ŵ�
	*/
	void run_action_animation(const float _dt);
	/*Ÿ���� �����ϴ� �Լ���*/
	void set_target(Unit* const _target);
private:
	UnitWeapon() {};

	/*���ݷ°� Ÿ���� ������ ����, �׸��� ���ְ� �Ȱ��� �ִϸ��̼� ������*/
	unsigned int attack;
	Unit* target;
	UnitAnimation* weapon_animation;
};

#endif