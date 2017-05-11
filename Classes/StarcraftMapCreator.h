#ifndef STARCRAFT_MAP_CREATOR_H_
#define STARCRAFT_MAP_CREATOR_H_

namespace cocos2d {
	class Sprite;
}

class MapData;

class StarCraftMapCreator {
public:
	StarCraftMapCreator();
	~StarCraftMapCreator();

	cocos2d::Sprite* create_bitmap_mapdata(MapData * const _map_data);
private:
	void draw_mega_tile(char* _data, int _mega_tile, int _x, int _y);
	void draw_mini_tile(char* _data, int _index, bool _flip, int _offset_x, int _offset_y);
	int find_mega_tile_num(int _x, int _y);
	int find_mini_tile_num(int _mega_tile, int _index);
	bool is_flip_mini_tile(int _mega_tile, int _index);

	int width;
	int height;
	
	MapData* map_data;

	// 타일 크기는 일정함
	const int mega_tile_w = 32;
	const int mega_tile_h = 32;

	const int mini_tile_w = 4;
	const int mini_tile_h = 4;

	const int mini_tile_pixel_w = 8;
	const int mini_tile_pixel_h = 8;
};

#endif // !

