#include "VF4Info.h"
#include <iostream>

VF4Info::VF4Info() :
	vf4_data(nullptr)
{
}

VF4Info::~VF4Info()
{
	SAFE_DELETE(vf4_data);
}

bool VF4Info::load_data(const map_tile_set _tile) 
{
	char file_name[64];
	switch (_tile)
	{
	case badlands:			sprintf_s(file_name, "tile_set/badlands.vf4"); break;
	case space_platform:	sprintf_s(file_name, "tile_set/platform.vf4"); break;
	case installation:		sprintf_s(file_name, "tile_set/install.vf4"); break;
	case ash_world:			sprintf_s(file_name, "tile_set/ashworld.vf4"); break;
	case jungle_world:		sprintf_s(file_name, "tile_set/jungle.vf4"); break;
	case desert:			sprintf_s(file_name, "tile_set/desert.vf4"); break;
	case ice:				sprintf_s(file_name, "tile_set/ice.vf4"); break;
	case twilight:			sprintf_s(file_name, "tile_set/twilight.vf4"); break;
	}

	FILE* file;
	fopen_s(&file, file_name, "rb");

	// 파일이 열렸는지 확인
	if (file == nullptr) {
		fclose(file);
		return false;
	}
	// 데이터를 새로 불러오기 전에 안전해제 실시
	// SAFE_DELETE(vf4_data);
	// 복사를 위해서 동적할당
	vf4_data = new VF4();
	// 읽기전에 초기화 0을 16진수로 표현하면 0x00
	memset(vf4_data, 0x00, sizeof(VF4));
	// 버퍼, 버퍼크기, 읽는 크기, 읽는 횟수, 파일을 매개변수로 한다.
	fread_s(vf4_data, sizeof(VF4), sizeof(VF4), 1, file);

	fclose(file);
	return true;
}