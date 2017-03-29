#ifndef WEAPON_ANIMATION_H_
#define WEAPON_ANIMATION_H_

#include "cocos2d.h"
#include "header.h"

class WeaponAnimation {
public:
	struct clip {
		unsigned int max_frame;
		std::vector<cocos2d::SpriteFrame*> animation_vector;
	};
	WeaponAnimation(const unit_type _type);
	~WeaponAnimation();
	void run_action_aniamtion(cocos2d::Sprite* const _sprite,
								const float _dt, const int _dir = 0, const int _frame = 0);
	void init_frame();
private:
	WeaponAnimation() {};
	unsigned int frame;
	float dt;

	clip bullet_clip;

	void init_unit_animation(const unit_type _type);
	void init_animation(const char* _str, const int _max_frame, const int _base);
	void init_clip(clip& _clip, const char* _str, const int _max_frame, const int _base);
};

#endif