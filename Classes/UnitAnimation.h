#ifndef UNIT_ANIMATION_H_
#define UNIT_ANIMATION_H_

#include "cocos2d.h"

class UnitAnimation : public cocos2d::Sprite {
public:
	UnitAnimation();
	virtual ~UnitAnimation();
	virtual bool init();
	CREATE_FUNC(UnitAnimation);

	cocos2d::Texture2D* texture[10];

	void run_action_animation();

private:
	unsigned int _frame;		// �ִϸ��̼� �����Ӽ�
	unsigned int _max_frame;
	float animation_speed;      // �ִϸ��̼� ���ǵ�
};

#endif