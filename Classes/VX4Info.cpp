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

	// ������ ���ȴ��� Ȯ��
	if (file == nullptr) {
		fclose(file);
		return false;
	}
	// �����͸� ���� �ҷ����� ���� �������� �ǽ�
	//SAFE_DELETE(vx4_data);
	// ���縦 ���ؼ� �����Ҵ�
	vx4_data = new VX4;
	// �б����� �ʱ�ȭ 0�� 16������ ǥ���ϸ� 0x00
	memset(vx4_data, 0x00, sizeof(VX4));
	// ����, ����ũ��, �д� ũ��, �д� Ƚ��, ������ �Ű������� �Ѵ�.
	fread_s(vx4_data, sizeof(VX4), sizeof(VX4), 1, file);

	fclose(file);
	return true;
}
