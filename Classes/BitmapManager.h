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
	//BITMAPFILEHEADER;		// 14바이트
	//BITMAPINFOHEADER;		// 40바이트

};


#endif // !BITMAP_MANAGER_H_
