#ifndef UNIT_ANIMATION_H_
#define UNIT_ANIMATION_H_

#include "cocos2d.h"
#include "header.h"
#include <vector>

class UnitAnimation : public cocos2d::Sprite {
public:
	UnitAnimation();
	virtual ~UnitAnimation();
	virtual bool init();
	CREATE_FUNC(UnitAnimation);
	virtual void run_action_animation(const float _dt) {};

protected:
	bool sprite_flip_x(const bool _b);
	
	unsigned int _frame;		// �ִϸ��̼� �����Ӽ�
	unsigned int _max_frame;
	float _animation_time;      // �ִϸ��̼� ���ǵ�
	float _dt;
	float _dt2;

	std::vector<cocos2d::SpriteFrame*> sprite_vector;
};

#endif