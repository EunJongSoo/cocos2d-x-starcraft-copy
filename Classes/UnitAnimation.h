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
	unsigned int _frame;		// 애니메이션 프레임수
	unsigned int _max_frame;
	float animation_speed;      // 애니메이션 스피드
};

#endif