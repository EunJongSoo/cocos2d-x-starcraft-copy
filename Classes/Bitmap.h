#ifndef BITMAP_H_
#define BITMAP_H_

#include "Header.h"
#include <string>

class Bitmap {
public:
	Bitmap();
	Bitmap(int _width, int _height, int size, int _img_width, int _img_height, char* _data);
	~Bitmap();
	Bitmap(Bitmap& _other);
	Bitmap(const Bitmap& _other);

	inline int get_img_width() const { return img_width; }
	inline int get_img_height() const { return img_height; }
	inline int get_bitmap_width() const { return bitmap_width; }
	inline int get_bitmap_height() const { return bitmap_height; }
	inline int get_size() const { return size_32bit; }
	inline char* get_data() const { return data; }

private:
	void operator=(Bitmap& _other) {};
	void operator=(const Bitmap& _other) {};

	// ����� �̹����� �θ��� ���� �ʿ��� ����
	int img_width;
	int img_height;
	int bitmap_width;
	int bitmap_height;
	int size_32bit;
	
	// �̹��� ������ �����ϴ� ����
	char* data;
};

#endif
