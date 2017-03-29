#ifndef UNIT_ANIMATION_H_
#define UNIT_ANIMATION_H_

#include "cocos2d.h"
#include "header.h"

class UnitAnimation {
public:
	struct clip {
		unsigned int max_frame;
		std::vector<cocos2d::SpriteFrame*> animation_vector;
	};
	UnitAnimation(const unit_type _type);
	~UnitAnimation();
	void run_action_aniamtion(const unit_state _state, cocos2d::Sprite* const _sprite, const float _dt, const int _dir = 0, const int _frame = 0);
	void init_frame();
private:
	UnitAnimation() {};
	unsigned int frame;
	float dt;

	clip move_clip;
	clip attack_clip;
	clip die_clip;

	void init_unit_animation(const unit_type _type);
	void init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base);
	void init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base, const int _ani_count);
	void init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num);
	void sprite_flipped_x(cocos2d::Sprite* const _sprite, const bool _is_left, const bool _is_flipped_x);
	void init_clip(clip& _clip, const char* _str, const int _max_frame, const int _base);
	void init_clip(clip& _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count);
	void init_clip(clip& _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num);
	void clip_aniamtion(const clip& _clip, cocos2d::Sprite* const _sprite, const float _dt, const int _dir, const int _frame);
};

#endif