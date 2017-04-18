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

	// 파일이 열렸는지 확인
	if (file == nullptr) {
		fclose(file);
		return false;
	}
	// 데이터를 새로 불러오기 전에 안전해제 실시
	SAFE_DELETE(vf4_data);
	// 복사를 위해서 동적할당
	vf4_data = new VF4;
	// 읽기전에 초기화 0을 16진수로 표현하면 0x00
	memset(vf4_data, 0x00, sizeof(VF4));
	// 버퍼, 버퍼크기, 읽는 크기, 읽는 횟수, 파일을 매개변수로 한다.
	fread_s(vf4_data, sizeof(VF4), sizeof(VF4), 1, file);

	fclose(file);
	return true;
}