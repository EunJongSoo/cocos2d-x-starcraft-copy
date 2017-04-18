#include "VR4Info.h"
#include <iostream>

VR4Info::VR4Info() :
	vr4_data(nullptr)
{
}

VR4Info::~VR4Info()
{
	SAFE_DELETE(vr4_data);
}

bool VR4Info::load_data(const map_tile_set _tile) {
	char file_name[32];
	switch (_tile)
	{
	case badlands:			sprintf_s(file_name, "tile_set/badlands.vr4"); break;
	case space_platform:	sprintf_s(file_name, "tile_set/platform.vr4"); break;
	case installation:		sprintf_s(file_name, "tile_set/install.vr4"); break;
	case ash_world:			sprintf_s(file_name, "tile_set/ashworld.vr4"); break;
	case jungle_world:		sprintf_s(file_name, "tile_set/jungle.vr4"); break;
	case desert:			sprintf_s(file_name, "tile_set/desert.vr4"); break;
	case ice:				sprintf_s(file_name, "tile_set/ice.vr4"); break;
	case twilight:			sprintf_s(file_name, "tile_set/twilight.vr4"); break;
	}

	FILE* file;
	fopen_s(&file, file_name, "rb");

	// ������ ���ȴ��� Ȯ��
	if (file == nullptr) {
		fclose(file);
		return false;
	}
	// �����͸� ���� �ҷ����� ���� �������� �ǽ�
	SAFE_DELETE(vr4_data);
	// ���縦 ���ؼ� �����Ҵ�
	vr4_data = new VR4;
	// �б����� �ʱ�ȭ 0�� 16������ ǥ���ϸ� 0x00
	memset(vr4_data, 0x00, sizeof(VR4));
	// ����, ����ũ��, �д� ũ��, �д� Ƚ��, ������ �Ű������� �Ѵ�.
	fread(vr4_data, sizeof(VR4), 1, file);

	fclose(file);
	return true;
}