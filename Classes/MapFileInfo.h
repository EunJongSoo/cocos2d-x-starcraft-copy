#ifndef MAP_FILE_INFO_H_
#define MAP_FILE_INFO_H_

#include "Header.h"

class MapFileInfo {
public:
	MapFileInfo(const char* _file_name);
	~MapFileInfo();
	bool load_data(const char* _file_name);
	
	inline unsigned short* get_map_data() { return MXTM_data; }
	inline int get_map_width() { return map_width; }
	inline int get_map_height() { return map_height; }
	inline map_tile_set get_tile_set() { return (map_tile_set)era_tile_set; }

private:
	MapFileInfo();

	unsigned short* MXTM_data;
	unsigned short map_width;
	unsigned short map_height;
	unsigned short era_tile_set;
};

#endif