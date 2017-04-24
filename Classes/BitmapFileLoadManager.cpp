#include "BitmapFileLoadManager.h"
#include <Windows.h>
#include <iostream>
#include "Bitmap.h"


BitmapFileLoadManager::BitmapFileLoadManager()
{
}

BitmapFileLoadManager::~BitmapFileLoadManager()
{
}

Bitmap * BitmapFileLoadManager::load_bitmap_file(const char * _file_name)
{
	FILE* file;
	fopen_s(&file, _file_name, "rb");

	// ��Ʈ�� �������
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	// ��Ʈ�� ���� ��� �θ���
	fread((char*)&bf, sizeof(BITMAPFILEHEADER), 1, file);

	// ���� ���� �˻�
	if (bf.bfType != 0x4d42)
	{
		//MessageBox(NULL,"��Ʈ�� ������ �ƴմϴ�","���� ����", MB_OK);
		//MessageBox(NULL, "Cannot use except that BMP", "WARNING", MB_OK);
		return nullptr;
	}

	// ��Ʈ�� ���� ��� �θ���
	fread((char*)&bi, sizeof(BITMAPINFOHEADER), 1, file);


	// ���� ���� �˻�
	if (bi.biBitCount != 8)
	{
		return nullptr;
	}
	// ���� �ķ�Ʈ ũ�� Ȯ��
	int color_table_size = 0;
	int bit_count = bi.biBitCount;
	if (bit_count == 1) {
		color_table_size = 2;
	}
	else if (bit_count == 4) {
		color_table_size = 16;
	}
	else if (bit_count == 8) {
		color_table_size = 256;
	}

	// BYTE == unsigned char
	/*typedef struct tagRGBQUAD {
	BYTE    rgbBlue;
	BYTE    rgbGreen;
	BYTE    rgbRed;
	BYTE    rgbReserved;
	} RGBQUAD;*/
	RGBQUAD rgb[256];

	// COLORREF == unsigned long
	//COLORREF color_palette[256];

	// �ķ�Ʈ ũ�⸸ŭ �ҷ�����
	fread(rgb, sizeof(RGBQUAD), 256, file);

	// ��Ʈ ����
	// #define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
	/*for (int i = 0; i < color_table_size; ++i) {
	color_palette[i] = RGB(rgb[i].rgbRed, rgb[i].rgbGreen, rgb[i].rgbBlue);
	}*/

	// ��Ʈ ������ �ִ� ������ ��ġ ������ �̵�
	fseek(file, bf.bfOffBits, SEEK_SET);

	int width = bi.biWidth;
	int height = bi.biHeight;

	// ��Ʈ�� ������ ������ ���� �Ҵ�
	char* read_bitmap_data = (char*)malloc(width * height);

	// ��Ʈ�� ������ �ҷ�����
	fread(read_bitmap_data, width * height, 1, file);

	// ���� �ݱ�
	fclose(file);

	int size_32bit = width * height * 4;
	// ��ȯ�� ������ ���� ���� �Ҵ�
	char* bitmap_32bit_data = (char*)malloc(size_32bit);

	// BPS ���
	int image_BPS_8bit = (width % 4) ? (width + (4 - (width % 4))) : width;

	// BYTE == unsigned char
	// 8bit �̹��� �÷� �ε���
	BYTE color_index = 0;

	// COLORREF == unsigned long
	// ���� ���� ����
	COLORREF putColor = 0;
	BYTE r = 0, g = 0, b = 0, a = 255;			// ���� RGB
	int index = 0;

	// ���� ������ ������ ��ġ ����� ����
	int max_h = height / 2;
	int min_h = height / 2;
	int max_w = width / 2;
	int min_w = width / 2;

	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			// ���� �ε��� Ȯ��
			color_index = read_bitmap_data[image_BPS_8bit * h + w];
			// �̹��� �������� ���� ����
			//putColor = color_palette[color_index];

			r = rgb[color_index].rgbRed;
			g = rgb[color_index].rgbGreen;
			b = rgb[color_index].rgbBlue;

			/*r = GetRValue(putColor);
			g = GetGValue(putColor);
			b = GetBValue(putColor);*/

			// ������� �˻�
			// ����� �ƴϸ� ����
			if (!check_background(r, g, b)) {
				// ���� ������ ������ ��ġ ����
				max_h = max(max_h, h);
				max_w = max(max_w, w);
				min_h = min(min_h, h);
				min_w = min(min_w, w);
				// 32bit ���ۿ� RGB ���
				// �̹����� �������� ������ �ݴ��� ���� ������ �Է�
				index = (w + (height - 1 - h) * width) * 4;
				bitmap_32bit_data[index] = r;
				bitmap_32bit_data[index + 1] = g;
				bitmap_32bit_data[index + 2] = b;
				bitmap_32bit_data[index + 3] = a;
			}
		}
	}

	int img_width = max_w - min_w;
	int img_height = max_h - min_h;

	SAFE_FREE(read_bitmap_data);

	// ��ȯ�� ��Ʈ�� ����
	Bitmap* bitmap = new Bitmap(width, height, size_32bit, img_width, img_height, bitmap_32bit_data);
	return bitmap;
}

bool BitmapFileLoadManager::check_background(const unsigned char r, const unsigned char g, const unsigned char b) const {
	return (r == 0 && g == 0 && b == 0);
}