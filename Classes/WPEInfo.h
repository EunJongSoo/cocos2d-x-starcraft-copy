#ifndef WPE_INFO_H_
#define WPE_INFO_H_

#include <iostream>
#include "Header.h"

class WPEInfo {
public:
	WPEInfo() :
		wpe_data(nullptr)
	{}
	~WPEInfo()
	{
		SAFE_DELETE(wpe_data);
	}

	// unsigned char Red
	// Red component

	// unsigned char Green
	// Green component

	// unsigned char Blue
	// Blue component

	// unsigned char Pad
	// Padding

	struct WPE {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char padding;		// 4byte 단위로 끊기 위해서 넣는 빈값
	} data[256];

	bool load_data(char* _file_name) {
		FILE* file;
		fopen_s(&file, _file_name, "rb");

		// 파일이 열렸는지 확인
		if (file == nullptr) {
			fclose(file);
			return false;
		}
		// 데이터를 새로 불러오기 전에 안전해제 실시
		SAFE_DELETE(wpe_data);
		// 복사를 위해서 동적할당
		wpe_data = new WPE;
		// 읽기전에 초기화 0을 16진수로 표현하면 0x00
		memset(wpe_data, 0x00, sizeof(WPE));
		// 버퍼, 버퍼크기, 읽는 크기, 읽는 횟수, 파일을 매개변수로 한다.
		fread_s(wpe_data, sizeof(WPE), sizeof(WPE), 1, file);

		fclose(file);
		return true;
	}

	WPE* get_vr4_data() const {
		return wpe_data;
	}

private:
	WPE * wpe_data;

};

#endif