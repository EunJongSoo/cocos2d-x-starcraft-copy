#ifndef BITMAP_MANAGER_H_
#define BITMAP_MANAGER_H_

#include <string>

class Bitmap;

class BitmapManager {
public:
	BitmapManager();
	~BitmapManager();

	Bitmap* load_bitmap(const std::string& _filename);
private:


};
#endif // !BITMAP_MANAGER_H_
