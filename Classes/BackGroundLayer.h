#ifndef BACK_GROUND_LAYER_H_
#define BACK_GROUND_LAYER_H_

#include "cocos2d.h"

class MapData;

class BackGroundLayer : public cocos2d::Layer {
public:
	BackGroundLayer();
	virtual ~BackGroundLayer();
	virtual bool init();
	CREATE_FUNC(BackGroundLayer);

	MapData* create_map();

private:
	void create_map_sprite(MapData* const _map_data);
	void create_map_tree(MapData* const _map_data);
};
#endif // !BACK_GROUND_LAYER_H_
