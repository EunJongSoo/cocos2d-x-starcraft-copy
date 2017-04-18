#ifndef BACK_GROUND_LAYER_H_
#define BACK_GROUND_LAYER_H_

#include "cocos2d.h"

class MapManager;

class BackGroundLayer : public cocos2d::Layer {
public:
	BackGroundLayer();
	virtual ~BackGroundLayer();
	virtual bool init();
	CREATE_FUNC(BackGroundLayer);

	void create_map();

private:
	MapManager* map_manager;

};
#endif // !BACK_GROUND_LAYER_H_
