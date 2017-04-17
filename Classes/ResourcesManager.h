#ifndef RESOURCES_MANAGER_H_
#define RESOURCES_MANAGER_H_

#include <map>
#include <string>
#include "Header.h"

class BitmapManager;
class Bitmap;

namespace cocos2d {
	class Texture2D;
}

namespace std {
	template < typename T, typename A > class vector;
}

class ResourcesManager {
public:
	ResourcesManager();
	~ResourcesManager();

	// 리소스를 불러오는 함수
	cocos2d::Texture2D* load_resources(player_color color, const std::string& _str);

private:
	std::map<std::string, Bitmap*>* find_bitmap_map(player_color _str);
	Bitmap* load_bitmap(const std::string& _str);
	cocos2d::Texture2D* create_texture(const Bitmap* const _bitmap);

	std::map<player_color, std::map<std::string, Bitmap*>*> color_bitmap_map;
	std::map<std::string, Bitmap*> base_bitmap_map;
	BitmapManager* bitmap_manager;
};
#endif