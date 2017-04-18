#include "WPEInfo.h"
#include <iostream>

WPEInfo::WPEInfo() :
	wpe_data(nullptr)
{
}

WPEInfo::~WPEInfo() 
{
	SAFE_DELETE(wpe_data);
}

bool WPEInfo::load_data(const map_tile_set _tile) {
	char file_name[32];
	switch (_tile)
	{
	case badlands:			sprintf_s(file_name, "tile_set/badlands.wpe"); break;
	case space_platform:	sprintf_s(file_name, "tile_set/platform.wpe"); break;
	case installation:		sprintf_s(file_name, "tile_set/install.wpe"); break;
	case ash_world:			sprintf_s(file_name, "tile_set/ashworld.wpe"); break;
	case jungle_world:		sprintf_s(file_name, "tile_set/jungle.wpe"); break;
	case desert:			sprintf_s(file_name, "tile_set/desert.wpe"); break;
	case ice:				sprintf_s(file_name, "tile_set/ice.wpe"); break;
	case twilight:			sprintf_s(file_name, "tile_set/twilight.wpe"); break;
	}

	FILE* file;
	fopen_s(&file, file_name, "rb");

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