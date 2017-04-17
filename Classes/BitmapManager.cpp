#include "BitmapManager.h"
#include "Bitmap.h"


BitmapManager::BitmapManager()
{
}

BitmapManager::~BitmapManager()
{
}

// 8비트 파일을 불러서 24비트로 변환하여 반환
Bitmap* BitmapManager::load_bitmap(const std::string& _filename)
{
	Bitmap* bit = new Bitmap;
	return bit->load_bitmap(_filename);
}