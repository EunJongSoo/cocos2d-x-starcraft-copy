#include "ResourcesManager.h"
#include "Bitmap.h"
#include "BitmapManager.h"
#include "cocos2d.h"

ResourcesManager::ResourcesManager()
	:
	bitmap_manager(nullptr)
{
	bitmap_manager = new BitmapManager();
}

ResourcesManager::~ResourcesManager()
{
	SAFE_DELETE(bitmap_manager);
	

	// 순차 접근 하여 해제 해야됨
	// 순차 접근 하여 해제 해야됨
	// 순차 접근 하여 해제 해야됨
	// 순차 접근 하여 해제 해야됨
	// 순차 접근 하여 해제 해야됨

	color_bitmap_map;
	base_bitmap_map;
}

// 리소스를 불러온다.
cocos2d::Texture2D* ResourcesManager::load_resources(player_color color, const std::string& _str)
{
	// 원하는 색상의 map을 찾는다.
	std::map<std::string, Bitmap*>* bitmap_map = find_bitmap_map(color);
	assert(bitmap_map);

	Bitmap* bitmap = nullptr;
	// 이미지를 찾는다.
	if (bitmap_map->find(_str) != bitmap_map->end()) {
		// 있으면 반환
		bitmap = bitmap_map->at(_str);
	}
	else {
		// 없으면 기본 이미지를 찾아서 복사한다.
		bitmap = new Bitmap(*load_bitmap(_str));

		// 색상을 바꾼다.
		bitmap->converter_color(color);

		// 색상을 바꾼 이미지 주소를 저장한다.
		bitmap_map->insert(std::pair<std::string, Bitmap*>(_str, bitmap));
	}

	assert(bitmap);
	
	// 비트맵 이미지로 텍스쳐2D를 만들어서 반환한다.
	cocos2d::Texture2D* texture = nullptr;
	texture = new cocos2d::Texture2D;
	texture->initWithData(
		bitmap->get_data(),
		bitmap->get_size(),
		cocos2d::Texture2D::PixelFormat::RGB888,
		bitmap->get_width(),
		bitmap->get_height(),
		cocos2d::Size(bitmap->get_width(), bitmap->get_height()));

	// 반환한다.
	return texture;
}

// 색상별로 이미지를 저장해둔다.
std::map<std::string, Bitmap*>* ResourcesManager::find_bitmap_map(player_color color)
{
	// 임시변수 선언
	std::map<std::string, Bitmap*>* bitmap_map = nullptr;
	// 색상을 찾는다.
	if (color_bitmap_map.find(color) != color_bitmap_map.end()) {
		// 있으면 대입
		bitmap_map = color_bitmap_map[color];
	}
	else {
		// 없으면 해당 색상의 map을 만든다.
		std::map<std::string, Bitmap*>* tmp = new std::map<std::string, Bitmap*>;
		// 대입
		color_bitmap_map[color] = tmp;
		bitmap_map = tmp;
	}
	// 반환
	return bitmap_map;
}

Bitmap* ResourcesManager::load_bitmap(const std::string& _str) {
	Bitmap* bitmap = nullptr;
	if (base_bitmap_map.find(_str) != base_bitmap_map.end()) {
		// 있으면 해당 리소스를 대입
		bitmap = base_bitmap_map[_str];
	}
	else {
		// 없으면 비트맵 매니저에서 리소스를 불러온다.
		bitmap = bitmap_manager->load_bitmap(_str);
		assert(bitmap);
		base_bitmap_map[_str] = bitmap;
		//bitmap_map.insert(std::pair<std::string, Bitmap*>(_str, bitmap));
	}
	return bitmap;
}