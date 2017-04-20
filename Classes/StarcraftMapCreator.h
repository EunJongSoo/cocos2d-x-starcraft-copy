#ifndef STARCRAFT_MAP_CREATOR_H_
#define STARCRAFT_MAP_CREATOR_H_

#include "MapData.h"

class Bitmap;

class StarCraftMapCreator {
public:
	StarCraftMapCreator();
	~StarCraftMapCreator();

	Bitmap* create_bitmap_mapdata(MapData* _data);
private:
	void create_mega_tile(char* _data, int _mega_tile, int _x, int _y);
	void create_mini_tile(char* _data, int _index, bool _flip, int _offset_x, int _offset_y);
	
	int find_mega_tile_num(int _x, int _y);
	int find_mini_tile_num(int _mega_tile, int _index);
	bool is_flip_mini_tile(int _mega_tile, int _index);
	const WPEInfo::WPE::wpe_data& find_wpe_data(const VR4Info::VR4::vr4_data& _vr4data, int _w, int _h);

	int width;
	int height;
	
	unsigned short* map_info_mapdata;
	CV5Info::CV5* cv5;
	VX4Info::VX4* vx4;
	VR4Info::VR4* vr4;
	WPEInfo::WPE* wpe;

	// 타일 크기는 일정함
	const int mega_tile_w = 32;
	const int mega_tile_h = 32;

	const int mini_tile_w = 4;
	const int mini_tile_h = 4;

	const int mini_tile_pixel_w = 8;
	const int mini_tile_pixel_h = 8;
};

#endif // !

