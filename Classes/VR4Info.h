#ifndef VR4_INFO_H_
#define VR4_INFO_H_

#include <iostream>
#include "Header.h"

class VR4Info {
public:
	VR4Info() :
		vr4_data(nullptr)
	{}
	~VR4Info()
	{
		SAFE_DELETE(vr4_data);
	}

	// unsigned short Bitmap
	// Each byte is an index of the WPE. Pixels are drawn left to right(unless flipped in VX4), top to bottom in an 8x8 square.
	// �� ����Ʈ�� WPE�� �ε����Դϴ�. �ȼ��� 8x8 ������� ������ �Ʒ���, ���ʿ��� ���������� �׷����ϴ� (VX4���� �������� �ʴ� ��).

	struct VR4 {
		unsigned char color[64];
	} image[32768];

	bool load_data(char* _file_name) {
		FILE* file;
		fopen_s(&file, _file_name, "rb");

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
		fread_s(vr4_data, sizeof(VR4), sizeof(VR4), 1, file);

		fclose(file);
		return true;
	}

	VR4* get_vr4_data() const {
		return vr4_data;
	}

private:
	VR4 * vr4_data;

};

#endif