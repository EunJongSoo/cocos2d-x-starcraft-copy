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

	// ������ ���ȴ��� Ȯ��
	if (file == nullptr) {
		fclose(file);
		return false;
	}
	// �����͸� ���� �ҷ����� ���� �������� �ǽ�
	// SAFE_DELETE(vf4_data);
	// ���縦 ���ؼ� �����Ҵ�
	vf4_data = new VF4();
	// �б����� �ʱ�ȭ 0�� 16������ ǥ���ϸ� 0x00
	memset(vf4_data, 0x00, sizeof(VF4));
	// ����, ����ũ��, �д� ũ��, �д� Ƚ��, ������ �Ű������� �Ѵ�.
	fread_s(vf4_data, sizeof(VF4), sizeof(VF4), 1, file);

	fclose(file);
	return true;
}