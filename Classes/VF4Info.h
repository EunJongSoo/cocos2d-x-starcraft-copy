#ifndef VF4_INFO_H_
#define VF4_INFO_H_

#include <iostream>
#include "Header.h"

class VF4Info {
public:
	VF4Info() :
		vf4_data(nullptr)
	{}
	~VF4Info()
	{
		SAFE_DELETE(vf4_data);
	}

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

	bool load_data(char* _file_name) {
		FILE* file;
		fopen_s(&file, _file_name, "rb");

		// ������ ���ȴ��� Ȯ��
		if (file == nullptr) {
			fclose(file);
			return false;
		}
		// �����͸� ���� �ҷ����� ���� �������� �ǽ�
		SAFE_DELETE(vf4_data);
		// ���縦 ���ؼ� �����Ҵ�
		vf4_data = new VF4;
		// �б����� �ʱ�ȭ 0�� 16������ ǥ���ϸ� 0x00
		memset(vf4_data, 0x00, sizeof(VF4));
		// ����, ����ũ��, �д� ũ��, �д� Ƚ��, ������ �Ű������� �Ѵ�.
		fread_s(vf4_data, sizeof(VF4), sizeof(VF4), 1, file);

		fclose(file);
		return true;
	}

	VF4* get_vx4_data() const {
		return vf4_data;
	}

private:
	VF4 * vf4_data;

};

#endif