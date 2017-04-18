#ifndef VF4_INFO_H_
#define VF4_INFO_H_

#include "Header.h"

class VF4Info {
public:
	// unsigned short flags - mini_tile_flags
	// 0x0001 - Walkable
	// 0x0002 - Mid
	// 0x0004 - High(Mid and High unchecked = Low)
	// 0x0008 - Blocks View
	// 0x0010 - Ramp - Appears on the middle minitiles of most ramps/stairs.
	// Rest unknown/unused

	struct VF4 {
		unsigned short flags[16];
	} data[65536];
public:
	VF4Info();
	~VF4Info();

	bool load_data(char* _file_name);
	inline VF4* get_vx4_data() const { return vf4_data; }
private:
	VF4 * vf4_data;
};
#endif