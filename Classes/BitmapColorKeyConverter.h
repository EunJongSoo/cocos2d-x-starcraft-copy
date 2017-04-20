#ifndef BITMAP_COLORKEY_CONVERTER_H_
#define BITMAP_COLORKEY_CONVERTER_H_

#include "Header.h"

class Bitmap;

class BitmapColorKeyConverter {
public:
	BitmapColorKeyConverter();
	~BitmapColorKeyConverter();

	void converter_colorkey(Bitmap* _bitmap, player_color _color);

private:
	bool check_colorkey(unsigned char r, unsigned char g, unsigned char b) const;
	unsigned long get_player_color(player_color _color) const;
};


#endif // !BITMAP_COLORKEY_CONVERTER_H_
