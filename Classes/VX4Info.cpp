#include "VX4Info.h"
#include <iostream>

VX4Info::VX4Info():
	vx4_data(nullptr)
{
}

VX4Info::~VX4Info()
{
	SAFE_DELETE(vx4_data);
}

bool VX4Info::load_data(const map_tile_set _tile)
{
	char file_name[32];
	switch (_tile)
	{
	case badlands:			sprintf_s(file_name, "tile_set/badlands.vx4"); break;
	case space_platform:	sprintf_s(file_name, "tile_set/platform.vx4"); break;
	case installation:		sprintf_s(file_name, "tile_set/install.vx4"); break;
	case ash_world:			sprintf_s(file_name, "tile_set/ashworld.vx4"); break;
	case jungle_world:		sprintf_s(file_name, "tile_set/jungle.vx4"); break;
	case desert:			sprintf_s(file_name, "tile_set/desert.vx4"); break;
	case ice:				sprintf_s(file_name, "tile_set/ice.vx4"); break;
	case twilight:			sprintf_s(file_name, "tile_set/twilight.vx4"); break;
	}
	
	FILE* file;
	fopen_s(&file, file_name, "rb");

	// 파일이 열렸는지 확인
	if (file == nullptr) {
		fclose(file);
		return false;
	}
	// 데이터를 새로 불러오기 전에 안전해제 실시
	//SAFE_DELETE(vx4_data);
	// 복사를 위해서 동적할당
	vx4_data = new VX4;
	// 읽기전에 초기화 0을 16진수로 표현하면 0x00
	memset(vx4_data, 0x00, sizeof(VX4));
	// 버퍼, 버퍼크기, 읽는 크기, 읽는 횟수, 파일을 매개변수로 한다.
	fread_s(vx4_data, sizeof(VX4), sizeof(VX4), 1, file);

	fclose(file);
	return true;
}
