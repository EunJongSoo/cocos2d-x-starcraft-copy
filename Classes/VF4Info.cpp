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


bool VF4Info::load_data(char * _file_name) {
	FILE* file;
	fopen_s(&file, _file_name, "rb");

	// ������ ���ȴ��� Ȯ��
	if (file == nullptr) {
		fclose(file);
		return false;
	}
	// �����͸� ���� �ҷ����� ���� �������� �ǽ�
	SAFE_DELETE(vf4_data);
	// ���縦 ���ؼ� �����Ҵ�
	vf4_data = new VF4;
	// �б����� �ʱ�ȭ 0�� 16������ ǥ���ϸ� 0x00
	memset(vf4_data, 0x00, sizeof(VF4));
	// ����, ����ũ��, �д� ũ��, �д� Ƚ��, ������ �Ű������� �Ѵ�.
	fread_s(vf4_data, sizeof(VF4), sizeof(VF4), 1, file);

	fclose(file);
	return true;
}