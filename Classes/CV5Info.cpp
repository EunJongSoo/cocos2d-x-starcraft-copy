#include "CV5Info.h"
#include <iostream>

CV5Info::CV5Info() :
	cv5_data(nullptr)
{
}
CV5Info::~CV5Info()
{
	SAFE_DELETE(cv5_data);
}

bool CV5Info::load_data(const map_tile_set _tile) 
{
	char file_name[64];
	switch (_tile)
	{
	case badlands:			sprintf_s(file_name, sizeof(file_name), "tile_set/badlands.cv5"); break;
	case space_platform:	sprintf_s(file_name, sizeof(file_name), "tile_set/platform.cv5"); break;
	case installation:		sprintf_s(file_name, sizeof(file_name), "tile_set/install.cv5"); break;
	case ash_world:			sprintf_s(file_name, sizeof(file_name), "tile_set/ashworld.cv5"); break;
	case jungle_world:		sprintf_s(file_name, sizeof(file_name), "tile_set/jungle.cv5"); break;
	case desert:			sprintf_s(file_name, sizeof(file_name), "tile_set/desert.cv5"); break;
	case ice:				sprintf_s(file_name, sizeof(file_name), "tile_set/ice.cv5"); break;
	case twilight:			sprintf_s(file_name, sizeof(file_name), "tile_set/twilight.cv5"); break;
	}

	FILE* file;
	fopen_s(&file, file_name, "rb");

	// ������ ���ȴ��� Ȯ��
	if (file == nullptr) {
		fclose(file);
		return false;
	}
	// �����͸� ���� �ҷ����� ���� �������� �ǽ�
	SAFE_DELETE(cv5_data);
	// ���縦 ���ؼ� �����Ҵ�
	cv5_data = new CV5();
	// �б����� �ʱ�ȭ 0�� 16������ ǥ���ϸ� 0x00
	memset(cv5_data, 0x00, sizeof(CV5));
	// ����, ����ũ��, �д� ũ��, �д� Ƚ��, ������ �Ű������� �Ѵ�.
	fread_s(cv5_data, sizeof(CV5), sizeof(CV5), 1, file);

	fclose(file);
	return true;
}