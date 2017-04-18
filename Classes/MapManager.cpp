#include "MapManager.h"
#include "cocos2d.h"
#include "TemplateSingleton.h"
#include "ResourcesManager.h"
#include "MapFileInfo.h"
#include "CV5Info.h"

//
//template <typename T>
//class array2d {
//public:
//	array2d(T* ptr, int pitch) : _ptr(ptr), _pitch(pitch) {}
//	T* operator[](int idx) { return _ptr + (_pitch*idx); }
//private:
//	T* const _ptr;
//	const int _pitch;
//};

MapManager::MapManager(const char * _mapname) :
	map_size_width(0),
	map_size_height(0),
	tile_set(map_tile_set::space_platform),
	map_data(nullptr),
	map_file_info(nullptr),
	cv5_info(nullptr)
{
	map_file_info = new MapFileInfo(_mapname);
	map_size_width = map_file_info->get_map_width();
	map_size_height = map_file_info->get_map_height();
	tile_set = map_file_info->get_tile_set();
	map_data = map_file_info->get_map_data();

	
	cv5_info = new CV5Info();
	cv5_info->load_data(tile_set);
}

MapManager::~MapManager()
{
}

cocos2d::Sprite * MapManager::get_map_sprite(const int _x, const int _y)
{
	cocos2d::Sprite* sprite = nullptr;

	//array2d<unsigned short> mxtm(map_data, 128);

	int data_index = map_size_width * _y + _x;
	int group = map_data[data_index] >> 4;
	int index = map_data[data_index] & 0xf;
	
	/*int group = mxtm[_y][_x] >> 4;
	int index = mxtm[_y][_x] & 0xf;*/


	// 메가타일 번호 확인
	int mega_tile = cv5_info->get_cv5_data()->group[group].mega_tile_index[index];

	ResourcesManager* resources_manager = TemplateSingleton<ResourcesManager>::get_instance();
	cocos2d::Texture2D* texture = resources_manager->load_resources(mega_tile, tile_set);
	assert(texture);

	sprite = cocos2d::Sprite::createWithTexture(texture);
	// 타일 위치 조정 필요
	// 타일 위치 조정 필요
	// 타일 위치 조정 필요
	// 타일 위치 조정 필요
	return sprite;
}