#ifndef BITMAP_MANAGER_H_
#define BITMAP_MANAGER_H_

class BitmapManager {
public:
	BitmapManager();
	~BitmapManager();

	unsigned char* load_bitmap(char* filename);

private:
	//BITMAPFILEHEADER;		// 14����Ʈ
	//BITMAPINFOHEADER;		// 40����Ʈ

};
#endif // !BITMAP_MANAGER_H_
