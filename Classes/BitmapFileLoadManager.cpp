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

	// 비트맵 헤더파일
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	// 비트맵 파일 헤더 부르기
	fread((char*)&bf, sizeof(BITMAPFILEHEADER), 1, file);

	// 파일 형식 검사
	if (bf.bfType != 0x4d42)
	{
		//MessageBox(NULL,"비트맵 파일이 아닙니다","에러 보고", MB_OK);
		//MessageBox(NULL, "Cannot use except that BMP", "WARNING", MB_OK);
		return nullptr;
	}

	// 비트맵 인포 헤더 부르기
	fread((char*)&bi, sizeof(BITMAPINFOHEADER), 1, file);


	// 파일 포맷 검사
	if (bi.biBitCount != 8)
	{
		return nullptr;
	}
	// 색상 파레트 크기 확인
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

	// 파레트 크기만큼 불러오기
	fread(rgb, sizeof(RGBQUAD), 256, file);

	// 비트 연산
	// #define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
	/*for (int i = 0; i < color_table_size; ++i) {
	color_palette[i] = RGB(rgb[i].rgbRed, rgb[i].rgbGreen, rgb[i].rgbBlue);
	}*/

	// 비트 정보가 있는 곳으로 위치 지시자 이동
	fseek(file, bf.bfOffBits, SEEK_SET);

	int width = bi.biWidth;
	int height = bi.biHeight;

	// 비트맵 데이터 저장할 공간 할당
	char* read_bitmap_data = (char*)malloc(width * height);

	// 비트맵 데이터 불러오기
	fread(read_bitmap_data, width * height, 1, file);

	// 파일 닫기
	fclose(file);

	int size_32bit = width * height * 4;
	// 변환할 데이터 저장 공간 할당
	char* bitmap_32bit_data = (char*)malloc(size_32bit);

	// BPS 계산
	int image_BPS_8bit = (width % 4) ? (width + (4 - (width % 4))) : width;

	// BYTE == unsigned char
	// 8bit 이미지 컬러 인덱스
	BYTE color_index = 0;

	// COLORREF == unsigned long
	// 실제 찍힐 색상
	COLORREF putColor = 0;
	BYTE r = 0, g = 0, b = 0, a = 255;			// 최종 RGB
	int index = 0;

	// 실제 색상이 찍히는 위치 저장용 변수
	int max_h = height / 2;
	int min_h = height / 2;
	int max_w = width / 2;
	int min_w = width / 2;

	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			// 색상 인덱스 확인
			color_index = read_bitmap_data[image_BPS_8bit * h + w];
			// 이미지 정보에서 색상값 추출
			//putColor = color_palette[color_index];

			r = rgb[color_index].rgbRed;
			g = rgb[color_index].rgbGreen;
			b = rgb[color_index].rgbBlue;

			/*r = GetRValue(putColor);
			g = GetGValue(putColor);
			b = GetBValue(putColor);*/

			// 배경인지 검사
			// 배경이 아니면 저장
			if (!check_background(r, g, b)) {
				// 실제 색상이 찍히는 위치 저장
				max_h = max(max_h, h);
				max_w = max(max_w, w);
				min_h = min(min_h, h);
				min_w = min(min_w, w);
				// 32bit 버퍼에 RGB 기록
				// 이미지가 뒤집히기 때문에 반대쪽 부터 색상을 입력
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

	// 반환할 비트맵 정보
	Bitmap* bitmap = new Bitmap(width, height, size_32bit, img_width, img_height, bitmap_32bit_data);
	return bitmap;
}

bool BitmapFileLoadManager::check_background(const unsigned char r, const unsigned char g, const unsigned char b) const {
	return (r == 0 && g == 0 && b == 0);
}