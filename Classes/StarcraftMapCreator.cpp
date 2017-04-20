#include "StarcraftMapCreator.h"
#include "Bitmap.h"


StarCraftMapCreator::StarCraftMapCreator() :
	width(0),
	height(0),
	map_info_mapdata(nullptr),
	cv5(nullptr),
	vx4(nullptr),
	vr4(nullptr),
	wpe(nullptr)
{
}

StarCraftMapCreator::~StarCraftMapCreator()
{
}

Bitmap * StarCraftMapCreator::create_bitmap_mapdata(MapData * _data)
{
	height = _data->mapfile_info->get_map_height();
	width = _data->mapfile_info->get_map_width();

	int bitmap_w = mega_tile_w * width;
	int bitmap_h = mega_tile_h * height;
	int size_32bit = bitmap_w * bitmap_h * 4;
	
	// 맵을 그릴 변수
	char* bitmap_data = (char*)malloc(size_32bit);
	memset(bitmap_data, 0, size_32bit);
	
	map_info_mapdata = _data->mapfile_info->get_map_data();
	cv5 = _data->cv5_info->get_cv5_data();
	vx4 = _data->vx4_info->get_vx4_data();
	vr4 = _data->vr4_info->get_vr4_data();
	wpe = _data->wpe_info->get_wpe_data();

	int mega_tile = 0;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			mega_tile = find_mega_tile_num(x, y);
			create_mega_tile(bitmap_data, mega_tile, x, y);
		}
	}

	Bitmap* map_bitmap = new Bitmap(bitmap_w, bitmap_h, size_32bit, bitmap_w, bitmap_h, bitmap_data);
	return map_bitmap;
}

void StarCraftMapCreator::create_mega_tile(char* _data, int _mega_tile, int _x, int _y)
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
			
			// 상위 15비트는 이미지
			mini_tile_index = find_mini_tile_num(_mega_tile, vr4_index);
			
			// 하위 1비트는 상하반전
			flip = is_flip_mini_tile(_mega_tile, vr4_index);
			
			// 미니 타일의 그래픽 정보를 불러온다.
			int mega_offset_x = tile_offset_x + mini_w * mini_tile_pixel_w;
			int mega_offset_y = tile_offset_y + offset_y * mini_h;

			create_mini_tile(_data, mini_tile_index, flip, mega_offset_x, mega_offset_y);
		}
	}
}

void StarCraftMapCreator::create_mini_tile(char* _data, int _index, bool _flip, int _offset_x, int _offset_y)
{
	int draw_x = 0, draw_y = 0;
	int draw_index = 0;
	int offset_y = mini_tile_w * mini_tile_pixel_w * width;
	const VR4Info::VR4::vr4_data& vr4data = vr4->image[_index];
	// 미니타일을 한 픽셀씩 찍는다.
	for (int pixel_h = 0; pixel_h < mini_tile_pixel_h; ++pixel_h) {
		for (int pixel_w = 0; pixel_w < mini_tile_pixel_w; ++pixel_w) {
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

			const WPEInfo::WPE::wpe_data & wpedata = find_wpe_data(vr4data, pixel_w, pixel_h);
			_data[draw_index] = wpedata.r;
			_data[draw_index + 1] = wpedata.g;
			_data[draw_index + 2] = wpedata.b;
			_data[draw_index + 3] = 255;
		}
	}
}

int StarCraftMapCreator::find_mega_tile_num(int _x, int _y)
{
	int data_index = width * _y + _x;
	int group = map_info_mapdata[data_index] >> 4;
	int index = map_info_mapdata[data_index] & 0xf;
	return cv5->group[group].mega_tile_index[index];
}

int StarCraftMapCreator::find_mini_tile_num(int _mega_tile, int _index)
{
	return vx4->data[_mega_tile].VR4_index[_index] >> 1;
}

bool StarCraftMapCreator::is_flip_mini_tile(int _mega_tile, int _index)
{
	return vx4->data[_mega_tile].VR4_index[_index] & 1;
}

const WPEInfo::WPE::wpe_data & StarCraftMapCreator::find_wpe_data(const VR4Info::VR4::vr4_data& _vr4data, int _w, int _h) {
	return wpe->data[_vr4data.color[_h * mini_tile_pixel_w + _w]];
}
