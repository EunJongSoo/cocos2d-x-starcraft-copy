#include "BitmapManager.h"
#include "Bitmap.h"


BitmapManager::BitmapManager()
{
}

BitmapManager::~BitmapManager()
{
}

// 8��Ʈ ������ �ҷ��� 24��Ʈ�� ��ȯ�Ͽ� ��ȯ
Bitmap* BitmapManager::load_bitmap(const std::string& _filename)
{
	Bitmap* bit = new Bitmap;
	return bit->load_bitmap(_filename);
}