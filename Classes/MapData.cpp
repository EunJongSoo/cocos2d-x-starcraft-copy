#include "MapData.h"
#include "MapFileInfo.h"
#include <iostream>

MapData::MapData() :
	width(0),
	height(0),
	map_info_mapdata(nullptr),
	mapfile_info(nullptr),
	cv5(nullptr),
	vx4(nullptr),
	vr4(nullptr),
	wpe(nullptr),
	vf4(nullptr)
{
}

MapData::~MapData() {
	SAFE_DELETE(cv5);
	SAFE_DELETE(vx4);
	SAFE_DELETE(vr4);
	SAFE_DELETE(wpe);
	SAFE_DELETE(vf4);
}

void MapData::load_map_data(const char * _file_name)
{
	// 맵을 부르기 위해 필요한 정보
	mapfile_info = new MapFileInfo(_file_name);
	map_tile_set tile_set = mapfile_info->get_tile_set();

	// 데이터 부르기
	cv5 = load_data(cv5, tile_set, ".cv5");
	vx4 = load_data(vx4, tile_set, ".vx4");
	vr4 = load_data(vr4, tile_set, ".vr4");
	wpe = load_data(wpe, tile_set, ".wpe");
	vf4 = load_data(vf4, tile_set, ".vf4");

	width = mapfile_info->get_map_width();
	height = mapfile_info->get_map_height();
	map_info_mapdata = mapfile_info->get_map_data();
}

int MapData::find_mega_tile_num(int _x, int _y) const
{
	int data_index = width * _y + _x;
	int group = map_info_mapdata[data_index] >> 4;
	int index = map_info_mapdata[data_index] & 0xf;
	return cv5->group[group].mega_tile_index[index];
}

unsigned short MapData::find_mini_tile_flag(int _mega_tile, int _index) const
{
	return vf4->data[_mega_tile].flags[_index];
}

int MapData::find_mini_tile_num(int _mega_tile, int _index) const
{
	// 상위 15비트는 이미지
	return vx4->data[_mega_tile].VR4_index[_index] >> 1;
}

bool MapData::is_flip_mini_tile(int _mega_tile, int _index) const
{
	// 하위 1비트는 상하반전
	return vx4->data[_mega_tile].VR4_index[_index] & 1;
}

MapData::WPE::wpe_data & MapData::find_wpe_data(int _mini_tile_index, int _w, int _h) const
{
	static const int mini_tile_pixel = 8;
	unsigned char color_index = vr4->image[_mini_tile_index].color[_h * mini_tile_pixel + _w];
	return wpe->data[color_index];
}

template<typename T>
T* MapData::load_data(T * _type, const map_tile_set _tile, const char* _str)
{
	if (_type != nullptr) {
		return nullptr;
	}

	char file_name[64];
	switch (_tile)
	{
	case badlands:			sprintf_s(file_name, sizeof(file_name), "tile_set/badlands"); break;
	case space_platform:	sprintf_s(file_name, sizeof(file_name), "tile_set/platform"); break;
	case installation:		sprintf_s(file_name, sizeof(file_name), "tile_set/install"); break;
	case ash_world:			sprintf_s(file_name, sizeof(file_name), "tile_set/ashworld"); break;
	case jungle_world:		sprintf_s(file_name, sizeof(file_name), "tile_set/jungle"); break;
	case desert:			sprintf_s(file_name, sizeof(file_name), "tile_set/desert"); break;
	case ice:				sprintf_s(file_name, sizeof(file_name), "tile_set/ice"); break;
	case twilight:			sprintf_s(file_name, sizeof(file_name), "tile_set/twilight"); break;
	}

	strcat(file_name, _str);

	FILE* file;
	fopen_s(&file, file_name, "rb");

	// 파일이 열렸는지 확인
	if (file == nullptr) {
		fclose(file);
		return false;
	}
	// 복사를 위해서 동적할당
	_type = new T();
	// 읽기전에 초기화 0을 16진수로 표현하면 0x00
	memset(_type, 0x00, sizeof(T));
	// 버퍼, 버퍼크기, 읽는 크기, 읽는 횟수, 파일을 매개변수로 한다.
	fread_s(_type, sizeof(T), sizeof(T), 1, file);

	fclose(file);
	return _type;
}
