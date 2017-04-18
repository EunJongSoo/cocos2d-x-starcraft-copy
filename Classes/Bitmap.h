#ifndef BITMAP_H_
#define BITMAP_H_

#include "Header.h"
#include <string>

#include "VX4Info.h"
#include "VR4Info.h"
#include "WPEInfo.h"

class Bitmap {
public:
	Bitmap();
	~Bitmap();
	Bitmap(Bitmap& _other);
	Bitmap(const Bitmap& _other);

	Bitmap* load_bitmap(const std::string& _filename);
	Bitmap* create_mega_tile(const int _mega_tile, VX4Info::VX4* const vx4, VR4Info::VR4* const vr4, WPEInfo::WPE* const wpe);
	void converter_color(player_color _color);
	

	inline int get_img_width() const { return img_width; }
	inline int get_img_height() const { return img_height; }
	inline int get_bitmap_width() const { return bitmap_width; }
	inline int get_bitmap_height() const { return bitmap_height; }
	inline int get_size() const { return size_32bit; }
	inline char* get_data() const { return data; }

private:
	void operator=(Bitmap& _other) {};
	void operator=(const Bitmap& _other) {};
	bool check_bg(unsigned char r, unsigned char g, unsigned char b) const;
	bool check_colorkey(unsigned char r, unsigned char g, unsigned char b) const;
	unsigned long get_player_color(player_color _color) const;

	// 저장된 이미지를 부르기 위해 필요한 정보
	int img_width;
	int img_height;
	int bitmap_width;
	int bitmap_height;
	int size_32bit;
	
	// 이미지 정보를 저장하는 변수
	char* data;
};

#endif
