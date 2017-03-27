#ifndef UNIT_WEAPON_H_
#define UNIT_WEAPON_H_

#include "cocos2d.h"

class UnitWeapon : public cocos2d::Sprite {
public:
	UnitWeapon();
	virtual ~UnitWeapon();
	virtual bool init();
	CREATE_FUNC(UnitWeapon);
	void run_action_weapon_animation();
private:
	std::vector<cocos2d::SpriteFrame*> animation_vector;

	unsigned int _attack;
	int _frame;
	int _max_frame;
};

#endif