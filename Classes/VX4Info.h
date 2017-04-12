#ifndef VX4_INFO_H_
#define VX4_INFO_H_

#include <iostream>
#include "Header.h"

class VX4Info {
public:
	VX4Info() :
		vx4_data(nullptr)
	{}
	~VX4Info()
	{
		SAFE_DELETE(vx4_data);
	}

	// unsigned short Imagges
	// The first bit (bit0) is the horizontal flip flag, the remaining 15 bits (bit 1-15) are the VR4 index
	// ù ��° ��Ʈ (bit0)�� ���� ���� �÷����̰�, ������ 15 ��Ʈ (1-15 ��Ʈ)�� VR4 �ε����Դϴ�

	struct VX4 {
		unsigned short VR4_index[16];
	} data[65536];

	bool load_data(char* _file_name) {
		FILE* file;
		fopen_s(&file, _file_name, "rb");

		// ������ ���ȴ��� Ȯ��
		if (file == nullptr) {
			fclose(file);
			return false;
		}
		// �����͸� ���� �ҷ����� ���� �������� �ǽ�
		SAFE_DELETE(vx4_data);
		// ���縦 ���ؼ� �����Ҵ�
		vx4_data = new VX4;
		// �б����� �ʱ�ȭ 0�� 16������ ǥ���ϸ� 0x00
		memset(vx4_data, 0x00, sizeof(VX4));
		// ����, ����ũ��, �д� ũ��, �д� Ƚ��, ������ �Ű������� �Ѵ�.
		fread_s(vx4_data, sizeof(VX4), sizeof(VX4), 1, file);

		fclose(file);
		return true;
	}

	VX4* get_vx4_data() const {
		return vx4_data;
	}

private:
	VX4 * vx4_data;

};

#endif