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
	// ���� ����
	data = (char*)malloc(size_32bit);
	memcpy(data, _other.data, size_32bit);
}

Bitmap * Bitmap::load_bitmap(const std::string& _filename)
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	std::ifstream file(_filename, std::ios::binary | std::ios::in);

	// badbit�� ��Ʈ�� ���·� �����Ǿ� �ִ��� �׽�Ʈ�մϴ�.
	// test if badbit is set in stream state
	if (file.bad()) {
		return nullptr;
	}

	// C ��Ʈ���� ���� �ִ��� �׽�Ʈ�մϴ�.
	// test if C stream has been opened
	if (!file.is_open()) {
		return nullptr;
	}

	// ������� �о����
	file.read((char*)&bf, sizeof(BITMAPFILEHEADER));
	file.read((char*)&bi, sizeof(BITMAPINFOHEADER));

	// ���� ���� �˻�
	if (bf.bfType != 0x4d42)
	{
		//MessageBox(NULL,"��Ʈ�� ������ �ƴմϴ�","���� ����", MB_OK);
		//MessageBox(NULL, "Cannot use except that BMP", "WARNING", MB_OK);
		return nullptr;
	}
	// ���� ���� �˻�
	if (bi.biBitCount != 8)
	{
		//MessageBox(NULL,"8��Ʈ ���˸� �����մϴ�.","���� ����", MB_OK);
		//MessageBox(NULL, "Cannot use except that 8bit color format", "WARNING", MB_OK);
		return nullptr;
	}

	// ��ġ������ �̵�
	// file.seekg(bf.bfSize + bi.biSize, std::ios::beg);

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
	COLORREF color_palette[256];
	// �ķ�Ʈ ũ�⸸ŭ �ҷ�����
	file.read((char*)rgb, sizeof(RGBQUAD) * color_table_size);

	// ��Ʈ ����
	// #define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
	for (int i = 0; i < color_table_size; ++i) {
		color_palette[i] = RGB(rgb[i].rgbRed, rgb[i].rgbGreen, rgb[i].rgbBlue);
	}

	// ��Ʈ ������ �ִ� ������ ��ġ ������ �̵�
	// file.seekg(bf.bfOffBits, std::ios::beg);

	// �̹��� ũ�� ����
	bitmap_width = bi.biWidth;
	bitmap_height = bi.biHeight;
	
	int size_8bit = bitmap_width * bitmap_height;
	// ��Ʈ�� ������ ������ ���� �Ҵ�
	char* read_bitmap_data = (char*)malloc(size_8bit);

	// ��Ʈ�� ������ �ҷ�����
	file.read(read_bitmap_data, size_8bit);
	file.close();

	// ������ ����, 24��Ʈ 3, 32��Ʈ 4
	size_32bit = size_8bit * 4;
	// ��ȯ�� ������ ���� ���� �Ҵ�
	data = (char*)malloc(size_32bit);
	memset(data, 0, size_32bit);
	// BPS ���
	int image_BPS_8bit = (bitmap_width % 4) ? (bitmap_width + (4 - (bitmap_width % 4))) : bitmap_width;

	// BYTE == unsigned char
	// 8bit �̹��� �÷� �ε���
	BYTE color_index = 0;			

	// COLORREF == unsigned long
	// ���� ���� ����
	COLORREF putColor = 0;			
	BYTE r = 0, g = 0, b = 0, a = 255;			// ���� RGB
	int index = 0;
	int max_h = bitmap_height / 2;
	int min_h = bitmap_height / 2;
	int max_w = bitmap_width / 2;
	int min_w = bitmap_width / 2;

	for (int h = 0; h < bitmap_height; ++h) {
		for (int w = 0; w < bitmap_width; ++w) {
			// ���� �ε��� Ȯ��
			color_index = read_bitmap_data[image_BPS_8bit * h + w];
			// �̹��� �������� ���� ����
			putColor = color_palette[color_index];
			r = GetRValue(putColor);
			g = GetGValue(putColor);
			b = GetBValue(putColor);
			
			// ������� �˻�
			if (!check_bg(r, g, b)){
				max_h = max(max_h, h);
				max_w = max(max_w, w);
				min_h = min(min_h, h);
				min_w = min(min_w, w);
				// 32bit ���ۿ� RGB ���
				// �̹����� �������� ������ �ݴ��� ���� ������ �Է�
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
	// Ÿ�� ũ��� ������
	bitmap_width = 32;
	bitmap_height = 32;
	size_32bit = bitmap_width * bitmap_height * 4;
	
	const int mini_tile_w = 4;
	const int mini_tile_h = 4;
	const int mini_tile_pixel_w = 8;
	const int mini_tile_pixel_h = 8;
	
	data = (char*)malloc(size_32bit);
	memset(data, 0, size_32bit);
	// �ް� Ÿ���� �̷�� 16���� �̴�Ÿ���� �����.
	for (int mini_h = 0; mini_h < mini_tile_h; ++mini_h) {
		for (int mini_w = 0; mini_w < mini_tile_w; ++mini_w) {
			int vr4_index = mini_h * mini_tile_w + mini_w;
			// ���� 15��Ʈ�� �̹���
			int mini_tile_index = vx4->data[_mega_tile].VR4_index[vr4_index] >> 1;
			// ���� 1��Ʈ�� ���Ϲ���
			bool flip = vx4->data[_mega_tile].VR4_index[vr4_index] & 1;
	
			// �̴� Ÿ���� �׷��� ������ �ҷ��´�.
			const VR4Info::VR4::vr4_data & vr4data = vr4->image[mini_tile_index];
			const int draw_offset_x = mini_w * mini_tile_pixel_w;
			const int draw_offset_y = mini_h * mini_tile_w * mini_tile_pixel_h * mini_tile_pixel_w;
			
			// �̴�Ÿ���� �� �ȼ��� ��´�.
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
	COLORREF player_color = 0;			// �÷��̾� ����	
	BYTE tr = 0, tg = 0, tb = 0;		// ���÷� RGB
	BYTE pr = 0, pg = 0, pb = 0;		// �ȷ�Ʈ RGB
	BYTE r = 0, g = 0, b = 0, a = 0;			// ���� RGB
	
	
	int tmp = 0;					// ���� �ӽú���
	int index = 0;

	for (int h = 0; h < bitmap_height; ++h) {
		for (int w = 0; w < bitmap_width; ++w) {
			index = (h * bitmap_width + w) * 4;
			// �����Ϳ� ������� �����Ѵ�.
			// ��Ʈ�ʿ��� b, g, r������ ����Ǿ� �ִ�.

			r = data[index];
			g = data[index + 1];
			b = data[index + 2];
			
			//
			// �÷�Ű������ Ȯ��
			//
			if (check_colorkey(r, g, b))
			{
				// ���÷� ��������
				player_color = get_player_color(_color);

				// !��Ʈ�ʿ� BGR ������ �� �ֱ⶧���� RGB���� ���÷��� B-R�� �ٲ㼭 ���
				// ���÷� RGB
				tr = GetRValue(player_color);
				tg = GetGValue(player_color);
				tb = GetBValue(player_color);

				// �ȷ�Ʈ RGB
				// !RGB(255, 0, 255)�� �������� ���� ���������� ���� ��ο���
				// �׷��� ������ ���÷������� ��ο��� �� ��ŭ�� ���ָ� ��Ͽϼ�
				pr = 255 - r;
				// G���� 0~16 ������ ���� ������ ������ 255���� ���� ����
				pg = g;
				pb = 255 - b;

				// ������� (�� �÷� - ���)
				r = (tr - pr > 0) ? tr - pr : 0;
				
				// !G���� �� ������ �����ֱ� ������ pg���� 0�̸�
				// ���÷����� �״�� ���� �Ǿ ��Ӱ� ������ֱ� ���ؼ� pr�� ����
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