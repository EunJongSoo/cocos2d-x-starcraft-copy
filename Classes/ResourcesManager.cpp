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
	base_bitmap_map;
}

// ���ҽ��� �ҷ��´�.
cocos2d::Texture2D* ResourcesManager::load_resources(player_color color, const std::string& _str)
{
	// ���ϴ� ������ map�� ã�´�.
	std::map<std::string, Bitmap*>* bitmap_map = find_bitmap_map(color);
	assert(bitmap_map);

	Bitmap* bitmap = nullptr;
	// �̹����� ã�´�.
	if (bitmap_map->find(_str) != bitmap_map->end()) {
		// ������ ��ȯ
		bitmap = bitmap_map->at(_str);
	}
	else {
		// ������ �⺻ �̹����� ã�Ƽ� �����Ѵ�.
		bitmap = new Bitmap(*load_bitmap(_str));

		// ������ �ٲ۴�.
		bitmap->converter_color(color);

		// ������ �ٲ� �̹��� �ּҸ� �����Ѵ�.
		bitmap_map->insert(std::pair<std::string, Bitmap*>(_str, bitmap));
	}

	assert(bitmap);
	
	// ��Ʈ�� �̹����� �ؽ���2D�� ���� ��ȯ�Ѵ�.
	cocos2d::Texture2D* texture = nullptr;
	texture = new cocos2d::Texture2D;
	texture->initWithData(
		bitmap->get_data(),
		bitmap->get_size(),
		cocos2d::Texture2D::PixelFormat::RGB888,
		bitmap->get_width(),
		bitmap->get_height(),
		cocos2d::Size(bitmap->get_width(), bitmap->get_height()));

	// ��ȯ�Ѵ�.
	return texture;
}

// ���󺰷� �̹����� �����صд�.
std::map<std::string, Bitmap*>* ResourcesManager::find_bitmap_map(player_color color)
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

Bitmap* ResourcesManager::load_bitmap(const std::string& _str) {
	Bitmap* bitmap = nullptr;
	if (base_bitmap_map.find(_str) != base_bitmap_map.end()) {
		// ������ �ش� ���ҽ��� ����
		bitmap = base_bitmap_map[_str];
	}
	else {
		// ������ ��Ʈ�� �Ŵ������� ���ҽ��� �ҷ��´�.
		bitmap = bitmap_manager->load_bitmap(_str);
		assert(bitmap);
		base_bitmap_map[_str] = bitmap;
		//bitmap_map.insert(std::pair<std::string, Bitmap*>(_str, bitmap));
	}
	return bitmap;
}