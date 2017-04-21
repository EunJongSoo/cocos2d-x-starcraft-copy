#ifndef BITMAP_MANAGER_H_
#define BITMAP_MANAGER_H_

#include "Header.h"

class Bitmap;
class BitmapFileLoadManager;
class BitmapColorKeyConverter;
class StarCraftMapCreator;

class BitmapManager {
public:
	BitmapManager();
	~BitmapManager();

	Bitmap* load_bitmap(const char* _file_name);
	void Converter_Bitmap_Color_Key(Bitmap* const _bitmap, const player_color _color);
private:
	Bitmap* load_bitmap_file(const char* _filename);
	Bitmap* create_bitmap_mapdata(const char* _file_name);

	BitmapFileLoadManager* file_load_manager;
	BitmapColorKeyConverter* colorkey_converter;
	StarCraftMapCreator* map_creator;
};
#endif // !BITMAP_MANAGER_H_
