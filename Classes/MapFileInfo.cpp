#include "MapFileInfo.h"
#include <iostream>

MapFileInfo::MapFileInfo(const char * _file_name):
	MXTM_data(nullptr),
	map_width(0),
	map_height(0)
{
	load_data(_file_name);
}

MapFileInfo::~MapFileInfo()
{
	SAFE_DELETE(MXTM_data);
}

bool MapFileInfo::load_data(const char * _file_name)
{
	FILE* file;
	fopen_s(&file, _file_name, "rb");

	fseek(file, 0, SEEK_END);
	int file_size = ftell(file);
	rewind(file);

	char data_type[4];
	int data_size = 0;

	while (true) {
		fread(data_type, sizeof(data_type), 1, file);
		fread(&data_size, sizeof(int), 1, file);
		// 맵 데이터 추출
		if (!memcmp(data_type, "MTXM", sizeof(data_type))) {
			MXTM_data = (unsigned short*)malloc(data_size);
			fread(MXTM_data, data_size, 1, file);
			break;
		}
		// 맵 크기 추출
		else if (!memcmp(data_type, "DIM ", sizeof(data_type))) {
			fread(&map_width, sizeof(unsigned short), 1, file);
			fread(&map_height, sizeof(unsigned short), 1, file);
		}
		// 타일 종류 추출
		else if (!memcmp(data_type, "ERA ", sizeof(data_type))) {
			fread(&era_tile_set, data_size, 1, file);
		}
		else {
			// 데이터 크기 만큼 위치 지시자 이동
			fseek(file, data_size, SEEK_CUR);
		}
	}

	fclose(file);
	return true;
}

	//FILE* file;
	//fopen_s(&file, _file_name, "rb");

	//// 파일이 열렸는지 확인
	//if (file == nullptr) {
	//	fclose(file);
	//	return false;
	//}

	//// 위치 지시자를 마지막으로 이동
	//fseek(file, 0, SEEK_END);

	//// 전체 파일 사이즈 확인
	//const int fsize = ftell(file);
	//
	//// 위치 지시자 되감기
	//rewind(file);
	//
	//// 맵 출력을 위한 데이터 추출하기
	//// 맵 데이터, 맵 크기, 타일셋 종류
	//char type[4];
	//int size = 0;
	//while (1) {
	//	if (ftell(file) + 8 > fsize) {
	//		break;
	//	}
	//	fread(type, 1, 4, file);
	//	fread(&size, 4, 1, file);
	//	if (!memcmp(type, "MTXM", sizeof(type))) {
	//		MXTM_data = (unsigned char*)malloc(size);
	//		fread(MXTM_data, size, 1, file);
	//		break;
	//	}
	//	else if (!memcmp(type, "DIM ", sizeof(type))) {
	//		fread(&map_width, 2, 1, file);
	//		fread(&map_height, 2, 1, file);
	//	}
	//	else if (!memcmp(type, "ERA ", sizeof(type))) {
	//		fread(&era_tile_set, 2, 1, file);
	//	}
	//	else {
	//		fseek(file, size, SEEK_CUR);
	//	}
	//}
	//fclose(file);