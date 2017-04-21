#ifndef MAP_DATA_H_
#define MAP_DATA_H_

#include "Header.h"

class MapFileInfo;

class MapData {
public:
	struct CV5 {
		struct cv5_data {
			unsigned char something[20];
			unsigned short mega_tile_index[16];
		} group[4096];
	};

	struct VF4 {
		struct vf4_data {
			unsigned short flags[16];
		} data[65536];
	};

	struct VR4
	{
		struct vr4_data {
			unsigned char color[64];
		} image[32768];
	};
	
	struct VX4 {
		struct vx4_data {
			unsigned short VR4_index[16];
		} data[65536];
	};

	struct WPE {
		struct wpe_data {
			unsigned char r;
			unsigned char g;
			unsigned char b;
			// 4byte 단위로 끊기 위해서 넣는 빈값
			unsigned char padding;
		} data[256];
	};

public:
	MapData(const char* _file_name); 
	~MapData(); 

	int find_mega_tile_num(int _x, int _y) const;
	int find_mini_tile_num(int _mega_tile, int _index) const;
	bool is_flip_mini_tile(int _mega_tile, int _index) const;
	WPE::wpe_data& MapData::find_wpe_data(int _mini_tile_index, int _w, int _h) const;

	inline int get_width() { return width; }
	inline int get_height() { return height; }

private:
	template<typename T>
	T* load_data(T* _type, const map_tile_set _tile, const char* _str);

	int width;
	int height;
	unsigned short* map_info_mapdata;

	MapFileInfo* mapfile_info;
	CV5* cv5;
	VX4* vx4;
	VR4* vr4;
	WPE* wpe;
	VF4* vf4;
};

#endif // !MAP_DATA_H_

// unsigned short index;
// Unknwon

// unsigned short flags;
// 0x0001 = Edge?
// 0x0004 = Cliff?
// 0x0040 = Creep
// 0x0080 = Unbuildable
// 0x0n00 = Deprecated ground height?
// 0x8000 = Buildable for Start Location and Beacons

// unsigned short Left Edge
// Not fully understood. Value matches Right Edge on connecting tiles.

// unsigned short Top Edge
// Not fully understood. Value matches Bottom Edge on connecting tiles.

// unsigned short Right Edge
// Not fully understood. Value matches Left Edge on connecting tiles.

// unsigned short Bottom Edge
// Not fully understood. Value matches Top Edge on connecting tiles.

// unsigned short Unknown/Unused
// Unknown/Unused

// unsigned short Edge Up
// Not fully understood. Edge piece has rows above it?
// 1 = Basic edge piece.
// 2 = Right edge piece.
// 3 = Left edge piece.

// unsigned short Unknown/Unused
// Unknown/Unused

// unsigned short Edge Down
// Not fully understood. Edge piece has rows below it?
// 1 = Basic edge piece.
// 2 = Right edge piece.
// 3 = Left edge piece.

// unsigned short MegaTile References
// 16 references to VF4 and VX4.

//struct CV5 {
//	struct cv5_data {
//		unsigned char something[20];
//		unsigned short mega_tile_index[16];
//	} group[4096];
//};



// unsigned short flags - mini_tile_flags
// 0x0001 - Walkable
// 0x0002 - Mid
// 0x0004 - High(Mid and High unchecked = Low)
// 0x0008 - Blocks View
// 0x0010 - Ramp - Appears on the middle minitiles of most ramps/stairs.
// Rest unknown/unused

//struct VF4 {
//	struct vf4_data {
//		unsigned short flags[16];
//	} data[65536];
//};



// unsigned short Bitmap
// Each byte is an index of the WPE. Pixels are drawn left to right(unless flipped in VX4), top to bottom in an 8x8 square.
// 각 바이트는 WPE의 인덱스입니다. 픽셀은 8x8 스퀘어에서 위에서 아래로, 왼쪽에서 오른쪽으로 그려집니다 (VX4에서 반전되지 않는 한).
//struct VR4
//{
//	struct vr4_data {
//		unsigned char color[64];
//	} image[32768];
//};


// unsigned short Imagges
// The first bit (bit0) is the horizontal flip flag, the remaining 15 bits (bit 1-15) are the VR4 index
// 첫 번째 비트 (bit0)는 수평 반전 플래그이고, 나머지 15 비트 (1-15 비트)는 VR4 인덱스입니다

//struct VX4 {
//	struct vx4_data {
//		unsigned short VR4_index[16];
//	} data[65536];
//};

// unsigned char Red
// Red component

// unsigned char Green
// Green component

// unsigned char Blue
// Blue component

// unsigned char Pad
// Padding

//struct WPE {
//	struct wpe_data {
//		unsigned char r;
//		unsigned char g;
//		unsigned char b;
//		unsigned char padding;		// 4byte 단위로 끊기 위해서 넣는 빈값
//	} data[256];
//};