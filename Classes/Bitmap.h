#ifndef BITMAP_H_
#define BITMAP_H_

#include "Header.h"
#include <string>

class Bitmap {
public:
	Bitmap();
	~Bitmap();
	Bitmap(Bitmap& _other);
	Bitmap(const Bitmap& _other);

	Bitmap* load_bitmap(const std::string& _filename);
	void converter_color(player_color _color);

	inline int get_width() const { return width; }
	inline int get_height() const { return height; }
	inline int get_size() const { return size; }
	inline char* get_data() const { return data; }

private:
	void operator=(Bitmap& _other) {};
	void operator=(const Bitmap& _other) {};
	bool check_bg(unsigned char r, unsigned char g, unsigned char b) const;
	bool check_colorkey(unsigned char r, unsigned char g, unsigned char b) const;
	unsigned long get_player_color(player_color _color) const;

	int width;
	int height;
	int size;
	char* data;
};

#endif
