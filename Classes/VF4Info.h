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

		// 파일이 열렸는지 확인
		if (file == nullptr) {
			fclose(file);
			return false;
		}
		// 데이터를 새로 불러오기 전에 안전해제 실시
		SAFE_DELETE(vf4_data);
		// 복사를 위해서 동적할당
		vf4_data = new VF4;
		// 읽기전에 초기화 0을 16진수로 표현하면 0x00
		memset(vf4_data, 0x00, sizeof(VF4));
		// 버퍼, 버퍼크기, 읽는 크기, 읽는 횟수, 파일을 매개변수로 한다.
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