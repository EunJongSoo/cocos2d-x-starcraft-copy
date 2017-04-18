#ifndef VR4_INFO_H_
#define VR4_INFO_H_

#include "Header.h"

class VR4Info {
public:
	// unsigned short Bitmap
	// Each byte is an index of the WPE. Pixels are drawn left to right(unless flipped in VX4), top to bottom in an 8x8 square.
	// �� ����Ʈ�� WPE�� �ε����Դϴ�. �ȼ��� 8x8 ������� ������ �Ʒ���, ���ʿ��� ���������� �׷����ϴ� (VX4���� �������� �ʴ� ��).
	struct VR4
	{
		struct vr4_data {
			unsigned char color[64];
		} image[32768];
	};
public:
	VR4Info(); 
	~VR4Info();
	
	bool load_data(const map_tile_set _tile);
	inline VR4* get_vr4_data() const { return vr4_data; }
private:
	VR4 * vr4_data;
};

#endif