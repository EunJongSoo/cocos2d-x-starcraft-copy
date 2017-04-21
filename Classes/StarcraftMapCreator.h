#ifndef STARCRAFT_MAP_CREATOR_H_
#define STARCRAFT_MAP_CREATOR_H_

#include "MapData.h"

class Bitmap;

class StarCraftMapCreator {
public:
	StarCraftMapCreator();
	~StarCraftMapCreator();

	Bitmap* create_bitmap_mapdata(const char * _file_name);
private:
	void load_map_data(const char * _file_name);
	void draw_mega_tile(char* _data, int _mega_tile, int _x, int _y);
	void draw_mini_tile(char* _data, int _index, bool _flip, int _offset_x, int _offset_y);
	int find_mega_tile_num(int _x, int _y);
	int find_mini_tile_num(int _mega_tile, int _index);
	bool is_flip_mini_tile(int _mega_tile, int _index);
	const MapData::WPE::wpe_data& find_wpe_data(int _mini_tile_index, int _w, int _h);

	int width;
	int height;
	
	MapData* map_data;
	unsigned short* map_info_mapdata;

	// 타일 크기는 일정함
	const int mega_tile_w = 32;
	const int mega_tile_h = 32;

	const int mini_tile_w = 4;
	const int mini_tile_h = 4;

	const int mini_tile_pixel_w = 8;
	const int mini_tile_pixel_h = 8;
};

#endif // !

