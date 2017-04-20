#include "BitmapManager.h"
#include "Bitmap.h"
#include "BitmapFileLoadManager.h"
#include "BitmapColorKeyConverter.h"
#include "StarcraftMapCreator.h"
#include "MapData.h"

BitmapManager::BitmapManager()
{
	file_load_manager = new BitmapFileLoadManager();
	colorkey_converter = new BitmapColorKeyConverter();
	map_creator = new StarCraftMapCreator();
}

BitmapManager::~BitmapManager()
{
	SAFE_DELETE(file_load_manager);
	SAFE_DELETE(colorkey_converter);
}

// 8��Ʈ ������ �ҷ��� 24��Ʈ�� ��ȯ�Ͽ� ��ȯ
Bitmap * BitmapManager::load_bitmap(const char* _file_name)
{
	const char* extension = strchr(_file_name, '.');
	Bitmap* bitmap = new Bitmap;

	// bmp �����̴�.
	if (!strcmp(extension, ".bmp")) {
		bitmap = load_bitmap_file(_file_name);
	}
	// �� �����̴�.
	else if (!strcmp(extension, ".chk")) {
		bitmap = create_bitmap_mapdata(_file_name);
	}
	return bitmap;
}

void BitmapManager::Converter_Bitmap_Color_Key(Bitmap * const _bitmap, player_color _color)
{
	colorkey_converter->converter_colorkey(_bitmap, _color);
}

Bitmap * BitmapManager::load_bitmap_file(const char * _file_name)
{
	return file_load_manager->load_bitmap_file(_file_name);
}

Bitmap * BitmapManager::create_bitmap_mapdata(const char * _file_name)
{
	MapData* data = new MapData(_file_name);
	return map_creator->create_bitmap_mapdata(data);
}