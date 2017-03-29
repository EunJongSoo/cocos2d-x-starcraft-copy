#ifndef UNIT_WEAPON_H_
#define UNIT_WEAPON_H_

#include "cocos2d.h"

class Unit;
class UnitAnimation;

class UnitWeapon : public cocos2d::Sprite {
public:
	UnitWeapon(Unit* const _target, const unit_type _unit_tpye);
	~UnitWeapon();
	void run_action_animation(const float _dt);
	void set_target(Unit* const _target);
private:
	UnitWeapon() {};
	
	unsigned int attack;
	Unit* target;
	UnitAnimation* weapon_animation;
};

#endif