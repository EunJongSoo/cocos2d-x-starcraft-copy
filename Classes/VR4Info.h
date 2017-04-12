#ifndef VR4_INFO_H_
#define VR4_INFO_H_

#include <iostream>
#include "Header.h"

class VR4Info {
public:
	VR4Info() :
		vr4_data(nullptr)
	{}
	~VR4Info()
	{
		SAFE_DELETE(vr4_data);
	}

	// unsigned short Bitmap
	// Each byte is an index of the WPE. Pixels are drawn left to right(unless flipped in VX4), top to bottom in an 8x8 square.
	// 각 바이트는 WPE의 인덱스입니다. 픽셀은 8x8 스퀘어에서 위에서 아래로, 왼쪽에서 오른쪽으로 그려집니다 (VX4에서 반전되지 않는 한).

	struct VR4 {
		unsigned char color[64];
	} image[32768];

	bool load_data(char* _file_name) {
		FILE* file;
		fopen_s(&file, _file_name, "rb");

		// 파일이 열렸는지 확인
		if (file == nullptr) {
			fclose(file);
			return false;
		}
		// 데이터를 새로 불러오기 전에 안전해제 실시
		SAFE_DELETE(vr4_data);
		// 복사를 위해서 동적할당
		vr4_data = new VR4;
		// 읽기전에 초기화 0을 16진수로 표현하면 0x00
		memset(vr4_data, 0x00, sizeof(VR4));
		// 버퍼, 버퍼크기, 읽는 크기, 읽는 횟수, 파일을 매개변수로 한다.
		fread_s(vr4_data, sizeof(VR4), sizeof(VR4), 1, file);

		fclose(file);
		return true;
	}

	VR4* get_vr4_data() const {
		return vr4_data;
	}

private:
	VR4 * vr4_data;

};

#endif