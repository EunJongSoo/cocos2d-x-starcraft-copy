#ifndef BACK_GROUND_LAYER_H_
#define BACK_GROUND_LAYER_H_

#include "cocos2d.h"

class BackGroundLayer : public cocos2d::Layer {
public:
	BackGroundLayer();
	virtual ~BackGroundLayer();
	virtual bool init();
	CREATE_FUNC(BackGroundLayer);

private:
	

};
#endif // !BACK_GROUND_LAYER_H_
