#ifndef UI_LAYER_H_
#define UI_LAYER_H_

#include "cocos2d.h"

class UiLayer : public cocos2d::Layer {
public:
	UiLayer();
	virtual ~UiLayer();
	virtual bool init();
	CREATE_FUNC(UiLayer);
};
#endif
