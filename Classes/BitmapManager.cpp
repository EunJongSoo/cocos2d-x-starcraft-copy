#include "BitmapManager.h"
#include "Bitmap.h"

#include "VX4Info.h"
#include "VR4Info.h"
#include "WPEInfo.h"

BitmapManager::BitmapManager() :
	vx4_info(nullptr),
	vr4_info(nullptr),
	wpe_info(nullptr)
{
}

BitmapManager::~BitmapManager()
{
}

// 8��Ʈ ������ �ҷ��� 24��Ʈ�� ��ȯ�Ͽ� ��ȯ
Bitmap * BitmapManager::load_bitmap(const std::string& _filename)
{
	Bitmap* bitmap = new Bitmap;
	return bitmap->load_bitmap(_filename);
}

// Ÿ�� ��Ʈ���� �����.
Bitmap * BitmapManager::create_mega_tile_bitmap(const int _mega_tile, const map_tile_set _tile_set)
{
	load_tile_set_info(_tile_set);
	Bitmap* bitmap = new Bitmap;
	return bitmap->create_mega_tile(_mega_tile, vx4_info->get_vx4_data(), vr4_info->get_vr4_data(), wpe_info->get_wpe_data());
}

void BitmapManager::load_tile_set_info(const map_tile_set _tile_set) {
	if (vx4_info == nullptr) {
		vx4_info = new VX4Info();
		vx4_info->load_data(_tile_set);
	}

	if (vr4_info == nullptr) {
		vr4_info = new VR4Info();
		vr4_info->load_data(_tile_set);
	}

	if (wpe_info == nullptr) {
		wpe_info = new WPEInfo();
		wpe_info->load_data(_tile_set);
	}
}
