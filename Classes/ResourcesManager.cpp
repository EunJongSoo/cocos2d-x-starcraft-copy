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
}

// 리소스를 불러온다.
cocos2d::Texture2D * ResourcesManager::load_resources(const std::string& _file_name, const player_color _color)
{
	// 원하는 색상의 map을 찾는다.
	std::map<std::string, Bitmap*>* bitmap_map = find_bitmap_map(_color);
	assert(bitmap_map);

	// 이미지를 찾는다.
	Bitmap* bitmap = find_bitmap(_file_name, bitmap_map);
	if (bitmap == nullptr) {
		// 없으면 기본 이미지를 찾아서 복사한다.
		bitmap = new Bitmap(*load_bitmap(_file_name, _color));
		
		// 색상을 바꾼다.
		converter_color(bitmap, _color);
		
		// 색상을 바꾼 이미지 주소를 저장한다.
		bitmap_map->insert(std::pair<std::string, Bitmap*>(_file_name, bitmap));
	}

	assert(bitmap);
	return create_texture(bitmap);
}

// 색상별로 이미지를 저장해둔다.
std::map<std::string, Bitmap*> * ResourcesManager::find_bitmap_map(const player_color color)
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

Bitmap * ResourcesManager::load_bitmap(const std::string& _file_name, const player_color _color) {
	std::map<std::string, Bitmap*>* bitmap_map = find_bitmap_map(player_color::none);
	Bitmap* bitmap = nullptr;
	
	// 색상이 없으면 한번 찾아봤기 때문에 다시 찾지 않는다.
	if (_color != player_color::none) {
		// 색상이 있으면 none에서 안찾았기 때문에 다시 찾는다.
		bitmap = find_bitmap(_file_name, bitmap_map);
	}

	if(bitmap == nullptr) {
		// 없으면 비트맵 매니저에서 리소스를 불러온다.
		bitmap = bitmap_manager->load_bitmap(_file_name.c_str());
		assert(bitmap);
		if (_color != player_color::none) {
			bitmap_map->insert(std::pair<std::string, Bitmap*>(_file_name, bitmap));
		}
	}
	return bitmap;
}

Bitmap * ResourcesManager::find_bitmap(const std::string& _file_name, const std::map<std::string, Bitmap*>* const _map)
{
	Bitmap* bitmap = nullptr;
	if (_map->find(_file_name) != _map->end()) {
		// 있으면 반환
		bitmap = _map->at(_file_name);
	}
	return bitmap;
}

void ResourcesManager::converter_color(Bitmap* const _bitmap, const player_color _color)
{
	// 색상이 없으면 바꾸지 않는다.
	if (_color != player_color::none) {
		// 색상을 바꾼다.
		bitmap_manager->Converter_Bitmap_Color_Key(_bitmap, _color);
	}
}

cocos2d::Texture2D * ResourcesManager::create_texture(const Bitmap* const _bitmap) {
	// 비트맵 이미지로 텍스쳐2D를 만들어서 반환한다.
	cocos2d::Texture2D* texture = nullptr;
	texture = new cocos2d::Texture2D;
	texture->initWithData(
		_bitmap->get_data(),
		_bitmap->get_size(),
		cocos2d::Texture2D::PixelFormat::RGBA8888,
		_bitmap->get_bitmap_width(),
		_bitmap->get_bitmap_height(),
		cocos2d::Size(_bitmap->get_img_width(), _bitmap->get_img_height()));
	// 반환한다.
	return texture;
}
