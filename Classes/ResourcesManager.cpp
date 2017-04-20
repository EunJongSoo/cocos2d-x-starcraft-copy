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
	

	// ���� ���� �Ͽ� ���� �ؾߵ�
	// ���� ���� �Ͽ� ���� �ؾߵ�
	// ���� ���� �Ͽ� ���� �ؾߵ�
	// ���� ���� �Ͽ� ���� �ؾߵ�
	// ���� ���� �Ͽ� ���� �ؾߵ�
	color_bitmap_map;
}

// ���ҽ��� �ҷ��´�.
cocos2d::Texture2D * ResourcesManager::load_resources(const std::string& _file_name, const player_color _color)
{
	// ���ϴ� ������ map�� ã�´�.
	std::map<std::string, Bitmap*>* bitmap_map = find_bitmap_map(_color);
	assert(bitmap_map);

	// �̹����� ã�´�.
	Bitmap* bitmap = find_bitmap(_file_name, bitmap_map);
	if (bitmap == nullptr) {
		// ������ �⺻ �̹����� ã�Ƽ� �����Ѵ�.
		bitmap = new Bitmap(*load_bitmap(_file_name, _color));
		
		// ������ �ٲ۴�.
		converter_color(bitmap, _color);
		
		// ������ �ٲ� �̹��� �ּҸ� �����Ѵ�.
		bitmap_map->insert(std::pair<std::string, Bitmap*>(_file_name, bitmap));
	}

	assert(bitmap);
	return create_texture(bitmap);
}

// ���󺰷� �̹����� �����صд�.
std::map<std::string, Bitmap*> * ResourcesManager::find_bitmap_map(const player_color color)
{
	// �ӽú��� ����
	std::map<std::string, Bitmap*>* bitmap_map = nullptr;
	// ������ ã�´�.
	if (color_bitmap_map.find(color) != color_bitmap_map.end()) {
		// ������ ����
		bitmap_map = color_bitmap_map[color];
	}
	else {
		// ������ �ش� ������ map�� �����.
		std::map<std::string, Bitmap*>* tmp = new std::map<std::string, Bitmap*>;
		// ����
		color_bitmap_map[color] = tmp;
		bitmap_map = tmp;
	}
	// ��ȯ
	return bitmap_map;
}

Bitmap * ResourcesManager::load_bitmap(const std::string& _file_name, const player_color _color) {
	std::map<std::string, Bitmap*>* bitmap_map = find_bitmap_map(player_color::none);
	Bitmap* bitmap = nullptr;
	
	// ������ ������ �ѹ� ã�ƺñ� ������ �ٽ� ã�� �ʴ´�.
	if (_color != player_color::none) {
		// ������ ������ none���� ��ã�ұ� ������ �ٽ� ã�´�.
		bitmap = find_bitmap(_file_name, bitmap_map);
	}

	if(bitmap == nullptr) {
		// ������ ��Ʈ�� �Ŵ������� ���ҽ��� �ҷ��´�.
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
		// ������ ��ȯ
		bitmap = _map->at(_file_name);
	}
	return bitmap;
}

void ResourcesManager::converter_color(Bitmap* const _bitmap, const player_color _color)
{
	// ������ ������ �ٲ��� �ʴ´�.
	if (_color != player_color::none) {
		// ������ �ٲ۴�.
		bitmap_manager->Converter_Bitmap_Color_Key(_bitmap, _color);
	}
}

cocos2d::Texture2D * ResourcesManager::create_texture(const Bitmap* const _bitmap) {
	// ��Ʈ�� �̹����� �ؽ���2D�� ���� ��ȯ�Ѵ�.
	cocos2d::Texture2D* texture = nullptr;
	texture = new cocos2d::Texture2D;
	texture->initWithData(
		_bitmap->get_data(),
		_bitmap->get_size(),
		cocos2d::Texture2D::PixelFormat::RGBA8888,
		_bitmap->get_bitmap_width(),
		_bitmap->get_bitmap_height(),
		cocos2d::Size(_bitmap->get_img_width(), _bitmap->get_img_height()));
	// ��ȯ�Ѵ�.
	return texture;
}
