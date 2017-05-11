#include "BitmapManager.h"
#include "Bitmap.h"
#include "BitmapFileLoadManager.h"
#include "BitmapColorKeyConverter.h"

BitmapManager::BitmapManager()
{
	file_load_manager = new BitmapFileLoadManager();
	colorkey_converter = new BitmapColorKeyConverter();
}

BitmapManager::~BitmapManager()
{
	SAFE_DELETE(file_load_manager);
	SAFE_DELETE(colorkey_converter);
}

// 8비트 파일을 불러서 24비트로 변환하여 반환
Bitmap * BitmapManager::load_bitmap(const char* _file_name)
{
	return file_load_manager->load_bitmap_file(_file_name);
}

void BitmapManager::Converter_Bitmap_Color_Key(Bitmap * const _bitmap, const player_color _color)
{
	colorkey_converter->converter_colorkey(_bitmap, _color);
}
