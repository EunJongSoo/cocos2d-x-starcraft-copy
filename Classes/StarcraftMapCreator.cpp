#include "StarcraftMapCreator.h"
#include "MapData.h"
#include "cocos2d.h"


StarCraftMapCreator::StarCraftMapCreator() :
	width(0),
	height(0),
	map_data(nullptr)
{
}

StarCraftMapCreator::~StarCraftMapCreator()
{
}

cocos2d::Sprite * StarCraftMapCreator::create_bitmap_mapdata(MapData * const _map_data)
{
	map_data = _map_data;
	width = map_data->get_width();
	height = map_data->get_height();

	int bitmap_w = mega_tile_w * width;
	int bitmap_h = mega_tile_h * height;
	int size_32bit = bitmap_w * bitmap_h * 4;
	
	// 맵을 그릴 변수
	char* bitmap_data = (char*)malloc(size_32bit);
	memset(bitmap_data, 0, size_32bit);
	
	// 메가 타일 그리기
	int mega_tile = 0;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			// 해당 좌표의 메가 타일 번호 찾기
			mega_tile = find_mega_tile_num(x, y);
			// 메가타일 번호로 좌표에 메가타일 그리기
			draw_mega_tile(bitmap_data, mega_tile, x, y);
		}
	}

	cocos2d::Texture2D* texture = new cocos2d::Texture2D;
	texture->initWithData(
		bitmap_data,
		size_32bit,
		cocos2d::Texture2D::PixelFormat::RGBA8888,
		bitmap_w,
		bitmap_h,
		cocos2d::Size(bitmap_w, bitmap_h));
	return cocos2d::Sprite::createWithTexture(texture);
}

void StarCraftMapCreator::draw_mega_tile(char* _data, int _mega_tile, int _x, int _y)
{
	int vr4_index = 0;
	int mini_tile_index = 0;
	bool flip = true;

	int offset_y = mini_tile_w * mini_tile_pixel_w * width * mini_tile_pixel_h;
	int tile_offset_x = _x * mini_tile_w * mini_tile_pixel_w;
	int tile_offset_y = _y * offset_y * mini_tile_h;
	// 메가 타일을 이루는 16개의 미니타일을 만든다.
	for (int mini_h = 0; mini_h < mini_tile_h; ++mini_h) {
		for (int mini_w = 0; mini_w < mini_tile_w; ++mini_w) {
			vr4_index = mini_h * mini_tile_w + mini_w;
			
			// 미니 타일 위치 확인한다.
			mini_tile_index = find_mini_tile_num(_mega_tile, vr4_index);
			
			// 미니타일이 반전 되었는지 확인한다.
			flip = is_flip_mini_tile(_mega_tile, vr4_index);
			
			// 메가 타일의 위치를 계산한다.
			int mega_offset_x = tile_offset_x + mini_w * mini_tile_pixel_w;
			int mega_offset_y = tile_offset_y + offset_y * mini_h;

			// 메가 타일 내의 미니타일을 그린다.
			draw_mini_tile(_data, mini_tile_index, flip, mega_offset_x, mega_offset_y);
		}
	}
}

void StarCraftMapCreator::draw_mini_tile(char* _data, int _index, bool _flip, int _offset_x, int _offset_y)
{
	int draw_x = 0, draw_y = 0;
	int draw_index = 0;
	int offset_y = mini_tile_w * mini_tile_pixel_w * width;
	// 미니타일을 한 픽셀씩 찍는다.
	for (int pixel_h = 0; pixel_h < mini_tile_pixel_h; ++pixel_h) {
		for (int pixel_w = 0; pixel_w < mini_tile_pixel_w; ++pixel_w) {
			// 픽셀을 찍을 데이터 위치 계산
			draw_x = _offset_x + (_flip ? 7 - pixel_w : pixel_w);
			draw_y = _offset_y + (pixel_h * offset_y);
			draw_index = (draw_y + draw_x) * 4;
			
			// 0 ~ 7
			// 32 ~ 39
			// 64 ~ 71
			// 96 ~ 103
			// 128 ~ 135
			// 160 ~ 167
			// 192 ~ 199
			// 224 ~ 231

			// 해당 좌표에 찍을 색상을 찾아서 입력한다.
			const MapData::WPE::wpe_data & wpedata = map_data->find_wpe_data(_index, pixel_w, pixel_h);
			_data[draw_index] = wpedata.r;
			_data[draw_index + 1] = wpedata.g;
			_data[draw_index + 2] = wpedata.b;
			_data[draw_index + 3] = 255;
		}
	}
}

// 메가 타일의 번호를 찾아온다.
int StarCraftMapCreator::find_mega_tile_num(int _x, int _y)
{
	return map_data->find_mega_tile_num(_x, _y);
}

// 미니 타일의 번호를 찾아온다.
int StarCraftMapCreator::find_mini_tile_num(int _mega_tile, int _index)
{
	return map_data->find_mini_tile_num(_mega_tile, _index);
}

// 미니타일이 반전 되었는지 확인한다.
bool StarCraftMapCreator::is_flip_mini_tile(int _mega_tile, int _index)
{
	return map_data->is_flip_mini_tile(_mega_tile, _index);
}