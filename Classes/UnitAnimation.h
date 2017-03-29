#ifndef UNIT_ANIMATION_H_
#define UNIT_ANIMATION_H_

#include "cocos2d.h"
#include "header.h"

class UnitAnimation {
public:
	struct clip {
		unit_state state;
		unsigned int max_frame;
		std::vector<cocos2d::SpriteFrame*> animation_vector;
	};
	UnitAnimation(const unit_type _type, Sprite* const _sprite);
	~UnitAnimation();
	bool run_action_aniamtion(const unit_state _state, cocos2d::Sprite* const _sprite, const float _dt, const int _dir = 0, const int _frame = 0);
	void init_frame();
private:
	UnitAnimation() {};
	unsigned int frame;
	float dt;

	std::vector<clip*> clip_vector;

	void init_unit_animation(const unit_type _type, cocos2d::Sprite* const _sprite);
	void init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base);
	void init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base, const int _ani_count);
	void init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num);
	void sprite_flipped_x(cocos2d::Sprite* const _sprite, const bool _is_left, const bool _is_flipped_x);
	void init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base);
	void init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count);
	void init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num);
	bool clip_aniamtion(const clip* const _clip, cocos2d::Sprite* const _sprite, const float _dt, const int _dir, const int _frame);
};

#endif