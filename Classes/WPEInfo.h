#ifndef WPE_INFO_H_
#define WPE_INFO_H_

#include "Header.h"

class WPEInfo {
public:
	// unsigned char Red
	// Red component

	// unsigned char Green
	// Green component

	// unsigned char Blue
	// Blue component

	// unsigned char Pad
	// Padding

	struct WPE {
		struct wpe_data {
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char padding;		// 4byte 단위로 끊기 위해서 넣는 빈값
		} data[256];
	};
public:
	WPEInfo();
	~WPEInfo();
	
	bool load_data(const map_tile_set _tile);
	inline WPE* get_wpe_data() const { return wpe_data; }
private:
	WPE * wpe_data;
};
#endif