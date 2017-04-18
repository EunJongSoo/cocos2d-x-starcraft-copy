#include "Bitmap.h"
#include <Windows.h>
#include <fstream>



Bitmap::Bitmap()
	:
	bitmap_width(0),
	bitmap_height(0),
	size_32bit(0),
	data(nullptr)
{
}

Bitmap::~Bitmap()
{
}

Bitmap::Bitmap(Bitmap & _other)
	:
	bitmap_width(_other.bitmap_width),
	bitmap_height(_other.bitmap_height),
	size_32bit(_other.size_32bit)
{
	// 깊은 복사
	data = (char*)malloc(size_32bit);
	memcpy(data, _other.data, size_32bit);
}

Bitmap * Bitmap::load_bitmap(const std::string& _filename)
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	std::ifstream file(_filename, std::ios::binary | std::ios::in);

	// badbit가 스트림 상태로 설정되어 있는지 테스트합니다.
	// test if badbit is set in stream state
	if (file.bad()) {
		return nullptr;
	}

	// C 스트림이 열려 있는지 테스트합니다.
	// test if C stream has been opened
	if (!file.is_open()) {
		return nullptr;
	}

	// 헤더파일 읽어오기
	file.read((char*)&bf, sizeof(BITMAPFILEHEADER));
	file.read((char*)&bi, sizeof(BITMAPINFOHEADER));

	// 파일 형식 검사
	if (bf.bfType != 0x4d42)
	{
		//MessageBox(NULL,"비트맵 파일이 아닙니다","에러 보고", MB_OK);
		//MessageBox(NULL, "Cannot use except that BMP", "WARNING", MB_OK);
		return nullptr;
	}
	// 파일 포맷 검사
	if (bi.biBitCount != 8)
	{
		//MessageBox(NULL,"8비트 포맷만 지원합니다.","에러 보고", MB_OK);
		//MessageBox(NULL, "Cannot use except that 8bit color format", "WARNING", MB_OK);
		return nullptr;
	}

	// 위치지시자 이동
	// file.seekg(bf.bfSize + bi.biSize, std::ios::beg);

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
	COLORREF color_palette[256];
	// 파레트 크기만큼 불러오기
	file.read((char*)rgb, sizeof(RGBQUAD) * color_table_size);

	// 비트 연산
	// #define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
	for (int i = 0; i < color_table_size; ++i) {
		color_palette[i] = RGB(rgb[i].rgbRed, rgb[i].rgbGreen, rgb[i].rgbBlue);
	}

	// 비트 정보가 있는 곳으로 위치 지시자 이동
	// file.seekg(bf.bfOffBits, std::ios::beg);

	// 이미지 크기 저장
	bitmap_width = bi.biWidth;
	bitmap_height = bi.biHeight;
	
	int size_8bit = bitmap_width * bitmap_height;
	// 비트맵 데이터 저장할 공간 할당
	char* read_bitmap_data = (char*)malloc(size_8bit);

	// 비트맵 데이터 불러오기
	file.read(read_bitmap_data, size_8bit);
	file.close();

	// 사이즈 저장, 24비트 3, 32비트 4
	size_32bit = size_8bit * 4;
	// 변환할 데이터 저장 공간 할당
	data = (char*)malloc(size_32bit);
	memset(data, 0, size_32bit);
	// BPS 계산
	int image_BPS_8bit = (bitmap_width % 4) ? (bitmap_width + (4 - (bitmap_width % 4))) : bitmap_width;

	// BYTE == unsigned char
	// 8bit 이미지 컬러 인덱스
	BYTE color_index = 0;			

	// COLORREF == unsigned long
	// 실제 찍힐 색상
	COLORREF putColor = 0;			
	BYTE r = 0, g = 0, b = 0, a = 255;			// 최종 RGB
	int index = 0;
	int max_h = bitmap_height / 2;
	int min_h = bitmap_height / 2;
	int max_w = bitmap_width / 2;
	int min_w = bitmap_width / 2;

	for (int h = 0; h < bitmap_height; ++h) {
		for (int w = 0; w < bitmap_width; ++w) {
			// 색상 인덱스 확인
			color_index = read_bitmap_data[image_BPS_8bit * h + w];
			// 이미지 정보에서 색상값 추출
			putColor = color_palette[color_index];
			r = GetRValue(putColor);
			g = GetGValue(putColor);
			b = GetBValue(putColor);
			
			// 배경인지 검사
			if (!check_bg(r, g, b)){
				max_h = max(max_h, h);
				max_w = max(max_w, w);
				min_h = min(min_h, h);
				min_w = min(min_w, w);
				// 32bit 버퍼에 RGB 기록
				// 이미지가 뒤집히기 때문에 반대쪽 부터 색상을 입력
				index = (w + (bitmap_height - 1 - h) * bitmap_width) * 4;
				data[index] = r;
				data[index + 1] = g;
				data[index + 2] = b;
				data[index + 3] = a;
			}
		}
	}

	img_width = max_w - min_w;
	img_height = max_h - min_h;

	SAFE_FREE(read_bitmap_data);

	return this;
}

Bitmap * Bitmap::create_mega_tile(const int _mega_tile, VX4Info::VX4* const vx4, VR4Info::VR4* const vr4, WPEInfo::WPE* const wpe)
{
	// 타일 크기는 일정함
	bitmap_width = 32;
	bitmap_height = 32;
	size_32bit = bitmap_width * bitmap_height * 4;
	
	const int mini_tile_w = 4;
	const int mini_tile_h = 4;
	const int mini_tile_pixel_w = 8;
	const int mini_tile_pixel_h = 8;
	
	data = (char*)malloc(size_32bit);
	memset(data, 0, size_32bit);
	// 메가 타일을 이루는 16개의 미니타일을 만든다.
	for (int mini_h = 0; mini_h < mini_tile_h; ++mini_h) {
		for (int mini_w = 0; mini_w < mini_tile_w; ++mini_w) {
			int vr4_index = mini_h * mini_tile_w + mini_w;
			// 상위 15비트는 이미지
			int mini_tile_index = vx4->data[_mega_tile].VR4_index[vr4_index] >> 1;
			// 하위 1비트는 상하반전
			bool flip = vx4->data[_mega_tile].VR4_index[vr4_index] & 1;
	
			// 미니 타일의 그래픽 정보를 불러온다.
			const VR4Info::VR4::vr4_data & vr4data = vr4->image[mini_tile_index];
			const int draw_offset_x = mini_w * mini_tile_pixel_w;
			const int draw_offset_y = mini_h * mini_tile_w * mini_tile_pixel_h * mini_tile_pixel_w;
			
			// 미니타일을 한 픽셀씩 찍는다.
			for (int pixel_h = 0; pixel_h < mini_tile_pixel_h; ++pixel_h) {
				for (int pixel_w = 0; pixel_w < mini_tile_pixel_w; ++pixel_w) {
					int draw_x = draw_offset_x + (flip ? 7 - pixel_w : pixel_w);
					int draw_y = draw_offset_y + (pixel_h * mini_tile_w * mini_tile_pixel_w);
					int draw_index = (draw_y + draw_x) * 4;

					// 0 ~ 7
					// 32 ~ 39
					// 64 ~ 71
					// 96 ~ 103
					// 128 ~ 135
					// 160 ~ 167
					// 192 ~ 199
					// 224 ~ 231

					const WPEInfo::WPE::wpe_data & wpedata = wpe->data[vr4data.color[pixel_h * mini_tile_pixel_w + pixel_w]];
					data[draw_index] = wpedata.r;
					data[draw_index + 1] = wpedata.g;
					data[draw_index + 2] = wpedata.b;
					data[draw_index + 3] = 255;
				}
			}
		}
	}
	return this;
}

void Bitmap::converter_color(player_color _color)
{
	COLORREF player_color = 0;			// 플레이어 색상	
	BYTE tr = 0, tg = 0, tb = 0;		// 팀컬러 RGB
	BYTE pr = 0, pg = 0, pb = 0;		// 팔레트 RGB
	BYTE r = 0, g = 0, b = 0, a = 0;			// 최종 RGB
	
	
	int tmp = 0;					// 계산용 임시변수
	int index = 0;

	for (int h = 0; h < bitmap_height; ++h) {
		for (int w = 0; w < bitmap_width; ++w) {
			index = (h * bitmap_width + w) * 4;
			// 데이터에 순서대로 접근한다.
			// 비트맵에는 b, g, r순서로 저장되어 있다.

			r = data[index];
			g = data[index + 1];
			b = data[index + 2];
			
			//
			// 컬러키값인지 확인
			//
			if (check_colorkey(r, g, b))
			{
				// 팀컬러 가져오기
				player_color = get_player_color(_color);

				// !비트맵에 BGR 순서로 들어가 있기때문에 RGB였던 팀컬러는 B-R을 바꿔서 사용
				// 팀컬러 RGB
				tr = GetRValue(player_color);
				tg = GetGValue(player_color);
				tb = GetBValue(player_color);

				// 팔레트 RGB
				// !RGB(255, 0, 255)를 기준으로 값이 적어질수록 색이 어두워짐
				// 그렇기 때문에 팀컬러에서도 어두워진 값 만큼을 빼주면 명암완성
				pr = 255 - r;
				// G값은 0~16 사이의 값을 가지기 때문에 255에서 빼지 않음
				pg = g;
				pb = 255 - b;

				// 명암적용 (팀 컬러 - 명암)
				r = (tr - pr > 0) ? tr - pr : 0;
				
				// !G값은 색 보정을 안해주기 때문에 pg값이 0이면
				// 팀컬러값이 그대로 들어가게 되어서 어둡게 만들어주기 위해서 pr을 빼줌
				tmp = (pg == 0) ? tg - pr : tg - pg;
				g = (tmp > 0) ? tmp : 0;
				b = (tb - pb > 0) ? tb - pb : 0;

				data[index] = r;
				data[index + 1] = g;
				data[index + 2] = b;
			}
		}
	}
}

bool Bitmap::check_bg(unsigned char r, unsigned char g, unsigned char b) const {
	return (r == 0 && g == 0 && b == 0);
}

//
// R: 32 ~ 255
// G: 0 ~ 16
// B: 56 ~ 255
//
bool Bitmap::check_colorkey(unsigned char r, unsigned char g, unsigned char b) const {
	return (r > 32 && g < 16 && b > 56);
}

COLORREF Bitmap::get_player_color(player_color _color) const {
	switch (_color)
	{
	case kWhite:		return RGB(255, 255, 255);
	case kRed:			return RGB(180, 20, 30);
	case kBlue:			return RGB(0, 66, 255);
	case kTeal:			return RGB(28, 167, 234);
	case kPurple:		return RGB(051, 26, 200);
	case kYellow:		return RGB(235, 225, 41);
	case kOrange:		return RGB(254, 138, 14);
	case kGreen:		return RGB(22, 128, 0);
	case kLightPink:	return RGB(208, 166, 252);
	case kViolet:		return RGB(31, 1, 201);
	case kLightGrey:	return RGB(82, 84, 148);
	case kDarkGreen:	return RGB(16, 98, 70);
	case kBrown:		return RGB(78, 72, 4);
	case kLightGreen:	return RGB(150, 255, 145);
	case kDarkGrey:		return RGB(35, 35, 35);
	case kPink:			return RGB(227, 91, 176);
	default: return RGB(0, 0, 0);
	}
}