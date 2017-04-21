#ifndef BITMAP_COLORKEY_CONVERTER_H_
#define BITMAP_COLORKEY_CONVERTER_H_

#include "Header.h"

class Bitmap;

class BitmapColorKeyConverter {
public:
	BitmapColorKeyConverter();
	~BitmapColorKeyConverter();

	void converter_colorkey(Bitmap* const _bitmap, const player_color _color);

private:
	bool check_colorkey(const unsigned char r, const unsigned char g, const unsigned char b) const;
	unsigned long get_player_color(const player_color _color) const;
};


#endif // !BITMAP_COLORKEY_CONVERTER_H_
