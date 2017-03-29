#ifndef UNIT_WEAPON_H_
#define UNIT_WEAPON_H_

#include "cocos2d.h"


class Unit;
class WeaponAnimation;
class UnitAnimation;

class UnitWeapon : public cocos2d::Sprite {
public:
	UnitWeapon(Unit* const _target);
	~UnitWeapon();
	void run_action_animation(const float _dt);
	void set_target(Unit* const _target);
private:
	UnitWeapon() {};


	unsigned int attack;
	int frame;
	int max_frame;
	Unit* target;
	UnitAnimation* weapon_animation;

};

#endif