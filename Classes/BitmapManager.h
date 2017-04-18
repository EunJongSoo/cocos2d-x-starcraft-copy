#ifndef BITMAP_MANAGER_H_
#define BITMAP_MANAGER_H_

#include <string>
#include "Header.h"

class Bitmap;
class VX4Info;
class VR4Info;
class WPEInfo;

class BitmapManager {
public:
	BitmapManager();
	~BitmapManager();

	Bitmap* load_bitmap(const std::string& _filename);
	Bitmap* create_mega_tile_bitmap(const int _mega_tile, const map_tile_set _tile_set);
private:
	void load_tile_set_info(const map_tile_set _tile_set);

	// 타일을 부르기 위해 필요한 정보
	VX4Info* vx4_info;
	VR4Info* vr4_info;
	WPEInfo* wpe_info;

};
#endif // !BITMAP_MANAGER_H_
