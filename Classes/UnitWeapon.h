#ifndef UNIT_WEAPON_H_
#define UNIT_WEAPON_H_

#include "cocos2d.h"

class Unit;

class UnitWeapon : public cocos2d::Sprite {
public:
	UnitWeapon();
	virtual ~UnitWeapon();
	void run_action_weapon_animation();
	void set_target(Unit* _target);
private:
	std::vector<cocos2d::SpriteFrame*> animation_vector;

	unsigned int attack;
	int frame;
	int max_frame;
	Unit* target;
};

#endif