#ifndef BITMAP_FILE_LOAD_MANAGER_H_
#define BITMAP_FILE_LOAD_MANAGER_H_

class Bitmap;

class BitmapFileLoadManager {
public:
	BitmapFileLoadManager();
	~BitmapFileLoadManager();

	Bitmap* load_bitmap_file(const char* _file_name);
private:
	bool check_background(unsigned char r, unsigned char g, unsigned char b) const;
};
#endif // !BIT_FILE_LOAD_MANAGER_H_
