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

	UnitAnimation();
	~UnitAnimation();
	void run_action_aniamtion(unit_state _state, cocos2d::Sprite* _sprite, float _dt, int _dir = 0, int _frame = 0);
	
	/*void move_aniamtion(cocos2d::Sprite* _sprite, float _dt, int _dir, int _frame);
	void attack_aniamtion(cocos2d::Sprite* _sprite, float _dt, int _dir, int _frame);
	void die_aniamtion(cocos2d::Sprite* _sprite, float _dt, int _dir, int _frame);*/

	void init_animation(unit_state _state, char* _str, int _max_frame, int _base);
	void init_animation(unit_state _state, char* _str, int _max_frame, int _base, int _ani_count);
	void init_animation(unit_state _state, char* _str, int _max_frame, int _base, int _ani_count, int _loop, int _num);
	/*void init_animation(char* _str, int _max_frame, int _base, int _ani_count, int _loop, int _num,
		int _dir, bool _attack, int _ready_count, int _ready_base);*/
	void init_frame();
private:
	unsigned int frame;
	float dt;

	clip move_clip;
	clip attack_clip;
	clip die_clip;

	void sprite_flipped_x(cocos2d::Sprite* _sprite, bool _is_left, bool _is_flipped_x);
	void init_clip(clip& _clip, char* _str, int _max_frame, int _base);
	void init_clip(clip& _clip, char* _str, int _max_frame, int _base, int _ani_count);
	void init_clip(clip& _clip, char* _str, int _max_frame, int _base, int _ani_count, int _loop, int _num);
	void clip_aniamtion(const clip& _clip, cocos2d::Sprite* _sprite, float _dt, int _dir, int _frame);
	
};

#endif