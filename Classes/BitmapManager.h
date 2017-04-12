#ifndef BITMAP_MANAGER_H_
#define BITMAP_MANAGER_H_

#include <iostream>
#include <Windows.h>

class BitmapManager {
public:
	BitmapManager();
	~BitmapManager();

	unsigned char* load_bitmap(char* filename);

private:
	//BITMAP;
	//BITMAPFILEHEADER;		// 14����Ʈ
	//BITMAPINFOHEADER;		// 40����Ʈ

};


#endif // !BITMAP_MANAGER_H_
