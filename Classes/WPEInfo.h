#ifndef WPE_INFO_H_
#define WPE_INFO_H_

#include <iostream>
#include "Header.h"

class WPEInfo {
public:
	WPEInfo() :
		wpe_data(nullptr)
	{}
	~WPEInfo()
	{
		SAFE_DELETE(wpe_data);
	}

	// unsigned char Red
	// Red component

	// unsigned char Green
	// Green component

	// unsigned char Blue
	// Blue component

	// unsigned char Pad
	// Padding

	struct WPE {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char padding;		// 4byte ������ ���� ���ؼ� �ִ� ��
	} data[256];

	bool load_data(char* _file_name) {
		FILE* file;
		fopen_s(&file, _file_name, "rb");

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

	WPE* get_vr4_data() const {
		return wpe_data;
	}

private:
	WPE * wpe_data;

};

#endif