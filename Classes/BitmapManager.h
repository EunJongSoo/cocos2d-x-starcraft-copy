#ifndef BITMAP_MANAGER_H_
#define BITMAP_MANAGER_H_

class Bitmap;

class BitmapManager {
public:
	BitmapManager();
	~BitmapManager();

	Bitmap* load_bitmap(char* filename);

private:
	//BITMAPFILEHEADER;		// 14바이트
	//BITMAPINFOHEADER;		// 40바이트

};
#endif // !BITMAP_MANAGER_H_
