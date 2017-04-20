#include "Bitmap.h"

Bitmap::Bitmap()
	:
	bitmap_width(0),
	bitmap_height(0),
	size_32bit(0),
	img_width(0),
	img_height(0),
	data(nullptr)
{
}

Bitmap::~Bitmap()
{
}

Bitmap::Bitmap(int _width, int _height, int size, int _img_width, int _img_height, char* _data)
	:
	bitmap_width(_width),
	bitmap_height(_height),
	size_32bit(size),
	img_width(_img_width),
	img_height(_img_height),
	data(_data)
{
}

Bitmap::Bitmap(Bitmap & _other)
	:
	bitmap_width(_other.bitmap_width),
	bitmap_height(_other.bitmap_height),
	size_32bit(_other.size_32bit)
{
	// ±Ì¿∫ ∫πªÁ
	data = (char*)malloc(size_32bit);
	memcpy(data, _other.data, size_32bit);
}