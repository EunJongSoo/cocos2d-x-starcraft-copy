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

	// ������ ���ȴ��� Ȯ��
	if (file == nullptr) {
		fclose(file);
		return false;
	}
	// �����͸� ���� �ҷ����� ���� �������� �ǽ�
	SAFE_DELETE(wpe_data);
	// ���縦 ���ؼ� �����Ҵ�
	wpe_data = new WPE;
	// �б����� �ʱ�ȭ 0�� 16������ ǥ���ϸ� 0x00
	memset(wpe_data, 0x00, sizeof(WPE));
	// ����, ����ũ��, �д� ũ��, �д� Ƚ��, ������ �Ű������� �Ѵ�.
	fread_s(wpe_data, sizeof(WPE), sizeof(WPE), 1, file);

	fclose(file);
	return true;
}