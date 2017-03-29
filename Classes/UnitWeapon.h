#ifndef UNIT_WEAPON_H_
#define UNIT_WEAPON_H_

#include "cocos2d.h"


class Unit;
class WeaponAnimation;

class UnitWeapon : public cocos2d::Sprite {
public:
	UnitWeapon();
	virtual ~UnitWeapon();
	void run_action_animation(const float _dt);
	void set_target(Unit* _target);
private:
	std::vector<cocos2d::SpriteFrame*> animation_vector;

	unsigned int attack;
	int frame;
	int max_frame;
	Unit* target;
	WeaponAnimation* weapon_animation;

};

#endif