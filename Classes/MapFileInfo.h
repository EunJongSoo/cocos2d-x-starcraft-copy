#ifndef MAP_FILE_INFO_H_
#define MAP_FILE_INFO_H_

#include "Header.h"

class MapFileInfo {
public:
	MapFileInfo(const char* _map_file_name);
	~MapFileInfo();
	bool load_data(const char* _file_name);
	
	inline unsigned short* get_map_data() { return MXTM_data; }
	inline int get_map_width() { return map_width; }
	inline int get_map_height() { return map_height; }
	inline map_tile_set get_tile_set() { return era_tile_set; }
private:
	MapFileInfo();
	unsigned short* MXTM_data;
	int map_width;
	int map_height;
	map_tile_set era_tile_set;
};

#endif