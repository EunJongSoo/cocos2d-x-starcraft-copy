#ifndef VX4_INFO_H_
#define VX4_INFO_H_

#include <iostream>
#include "Header.h"

class VX4Info {
public:
	VX4Info() :
		vx4_data(nullptr)
	{}
	~VX4Info()
	{
		SAFE_DELETE(vx4_data);
	}

	// unsigned short Imagges
	// The first bit (bit0) is the horizontal flip flag, the remaining 15 bits (bit 1-15) are the VR4 index
	// 첫 번째 비트 (bit0)는 수평 반전 플래그이고, 나머지 15 비트 (1-15 비트)는 VR4 인덱스입니다

	struct VX4 {
		unsigned short VR4_index[16];
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
		SAFE_DELETE(vx4_data);
		// 복사를 위해서 동적할당
		vx4_data = new VX4;
		// 읽기전에 초기화 0을 16진수로 표현하면 0x00
		memset(vx4_data, 0x00, sizeof(VX4));
		// 버퍼, 버퍼크기, 읽는 크기, 읽는 횟수, 파일을 매개변수로 한다.
		fread_s(vx4_data, sizeof(VX4), sizeof(VX4), 1, file);

		fclose(file);
		return true;
	}

	VX4* get_vx4_data() const {
		return vx4_data;
	}

private:
	VX4 * vx4_data;

};

#endif