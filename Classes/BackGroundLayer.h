#ifndef BACK_GROUND_LAYER_H_
#define BACK_GROUND_LAYER_H_

#include "cocos2d.h"

class MapData;
class MapTree;

class BackGroundLayer : public cocos2d::Layer {
public:
	BackGroundLayer();
	virtual ~BackGroundLayer();
	virtual bool init();
	CREATE_FUNC(BackGroundLayer);

	bool create_map(MapData* const _map_data, MapTree* const _map_tree);

private:
	void create_map_sprite(MapData* const _map_data);
	void create_map_tree(MapData* const _map_data, MapTree* const _map_tree);
};
#endif // !BACK_GROUND_LAYER_H_
