#ifndef UNIT_ANIMATION_H_
#define UNIT_ANIMATION_H_

#include "cocos2d.h"
#include "header.h"

class UnitAnimation : public cocos2d::Node {
public:
	UnitAnimation();
	~UnitAnimation();
	void run_action_aniamtion(float _dt, int _dir, int _frame = 0);
	void init_animation(char* _str, int _max_frame, int _base);
	void init_animation(char* _str, int _max_frame, int _base, int _ani_count);
	void init_animation(char* _str, int _max_frame, int _base, int _ani_count, int _loop, int _num);
	/*void init_animation(char* _str, int _max_frame, int _base, int _ani_count, int _loop, int _num,
		int _dir, bool _attack, int _ready_count, int _ready_base);*/
private:
	cocos2d::Sprite* _parent;
	unsigned int frame;
	unsigned int max_frame;
	float dt;
	std::vector<cocos2d::SpriteFrame*> animation_vector;
	
	bool sprite_flip_x(const bool _b);
};

#endif