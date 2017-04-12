#ifndef MAP_FILE_INFO_H_
#define MAP_FILE_INFO_H_

#include <iostream>
#include "Header.h"

class MapFileInfo {
public:
	MapFileInfo() :
		map_data(nullptr)
	{}
	~MapFileInfo()
	{
		SAFE_DELETE(map_data);
	}

	// unsigned char Red
	// Red component

	// unsigned char Green
	// Green component

	// unsigned char Blue
	// Blue component

	// unsigned char Pad
	// Padding

	struct Map {
		unsigned int type[2];
		unsigned int type;
		
		unsigned int ver[2];
		unsigned short ver;

		unsigned int iver[2];
		unsigned short iver;

		unsigned int ive2[2];
		unsigned short ive2;

		unsigned int vcod[2];
		unsigned int vcod[256];
		unsigned char vcod[16];

		unsigned int iown[2];
		unsigned char iown[12];

		unsigned int ownr[2];
		unsigned char ownr[12];

		unsigned int era[2];
		unsigned short era;

		unsigned int dim[2];
		unsigned short width;
		unsigned short height;

		unsigned int side[2];
		unsigned char side[12];

		unsigned int mtxm[2];
		unsigned short* mtxm;
	};

	bool load_data(char* _file_name) {
		FILE* file;
		fopen_s(&file, _file_name, "rb");

		// 파일이 열렸는지 확인
		if (file == nullptr) {
			fclose(file);
			return false;
		}
		// 데이터를 새로 불러오기 전에 안전해제 실시
		SAFE_DELETE(map_data);
		// 복사를 위해서 동적할당
		map_data = new Map;
		// 읽기전에 초기화 0을 16진수로 표현하면 0x00
		memset(map_data, 0x00, sizeof(Map));
		// 버퍼, 버퍼크기, 읽는 크기, 읽는 횟수, 파일을 매개변수로 한다.
		fread_s(map_data, sizeof(Map), sizeof(Map), 1, file);

		fclose(file);
		return true;
	}

	Map* get_vr4_data() const {
		return map_data;
	}

private:
	Map * map_data;

};

#endif