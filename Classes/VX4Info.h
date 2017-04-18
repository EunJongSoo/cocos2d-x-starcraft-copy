#ifndef VX4_INFO_H_
#define VX4_INFO_H_

#include "Header.h"

class VX4Info {
public:
	// unsigned short Imagges
	// The first bit (bit0) is the horizontal flip flag, the remaining 15 bits (bit 1-15) are the VR4 index
	// ù ��° ��Ʈ (bit0)�� ���� ���� �÷����̰�, ������ 15 ��Ʈ (1-15 ��Ʈ)�� VR4 �ε����Դϴ�

	struct VX4 {
		struct vx4_data {
			unsigned short VR4_index[16];
		} data[65536];
	};
public:
	VX4Info();
	~VX4Info();

	bool load_data(const map_tile_set _tile);
	inline VX4* get_vx4_data() const { return vx4_data; }
private:
	VX4 * vx4_data;
};
#endif