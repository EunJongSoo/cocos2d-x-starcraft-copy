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

		// ������ ���ȴ��� Ȯ��
		if (file == nullptr) {
			fclose(file);
			return false;
		}
		// �����͸� ���� �ҷ����� ���� �������� �ǽ�
		SAFE_DELETE(map_data);
		// ���縦 ���ؼ� �����Ҵ�
		map_data = new Map;
		// �б����� �ʱ�ȭ 0�� 16������ ǥ���ϸ� 0x00
		memset(map_data, 0x00, sizeof(Map));
		// ����, ����ũ��, �д� ũ��, �д� Ƚ��, ������ �Ű������� �Ѵ�.
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