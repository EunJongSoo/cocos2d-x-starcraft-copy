#ifndef CV5_INFO_H_
#define CV5_INFO_H_

#include <iostream>
#include "Header.h"

class CV5Info {
public:
	CV5Info() :
		cv5_data(nullptr)
	{}
	~CV5Info() 
	{
		SAFE_DELETE(cv5_data);
	}

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

	struct CV5 {
		unsigned char something[20];
		unsigned short mega_tile_index[16];
	} group[4096];
	
	bool load_data(char* _file_name) {
		FILE* file;
		fopen_s(&file, _file_name, "rb");

		// 파일이 열렸는지 확인
		if (file == nullptr) {
			fclose(file);
			return false;
		}
		// 데이터를 새로 불러오기 전에 안전해제 실시
		SAFE_DELETE(cv5_data);
		// 복사를 위해서 동적할당
		cv5_data = new CV5;
		// 읽기전에 초기화 0을 16진수로 표현하면 0x00
		memset(cv5_data, 0x00, sizeof(CV5));
		// 버퍼, 버퍼크기, 읽는 크기, 읽는 횟수, 파일을 매개변수로 한다.
		fread_s(cv5_data, sizeof(CV5), sizeof(CV5), 1, file);

		fclose(file);
		return true;
	}

	CV5* get_cv5_data() const {
		return cv5_data;
	}

private:
	CV5 * cv5_data;

};

#endif