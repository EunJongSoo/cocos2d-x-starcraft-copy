#ifndef MAP_MANAGER_H_
#define MAP_MANAGER_H_

#include "Header.h"

class MapFileInfo;
class CV5Info;

namespace cocos2d {
	class Sprite;
}

class MapManager {
public:
	MapManager(const char * _mapname);
	~MapManager();

	cocos2d::Sprite* get_map_sprite(const int x, const int y);

	inline int get_map_size_width() { return map_size_width; }
	inline int get_map_size_height() { return map_size_height; }

private:
	MapManager();

	int map_size_width;
	int map_size_height;
	map_tile_set tile_set;
	
	MapFileInfo* map_file_info;
	unsigned short* map_data;
	
	CV5Info* cv5_info;

};

#endif