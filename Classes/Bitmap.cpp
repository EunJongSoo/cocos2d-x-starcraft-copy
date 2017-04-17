#include "Bitmap.h"
#include <Windows.h>
#include <fstream>

Bitmap::Bitmap()
	:
	width(0),
	height(0),
	size(0),
	data(nullptr)
{
}

Bitmap::~Bitmap()
{
}

Bitmap::Bitmap(Bitmap & _other)
	:
	width(_other.width),
	height(_other.height),
	size(_other.size)
{
	// ���� ����
	data = (char*)malloc(size);
	memcpy(data, _other.data, size);
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
	if (file.is_open() == false) {
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

	// �̓G ũ�� ����
	width = bi.biWidth;
	height = bi.biHeight;
	
	// ��Ʈ�� ������ ������ ���� �Ҵ�
	char* read_bitmap_data = (char*)malloc(width * height);

	// ��Ʈ�� ������ �ҷ�����
	file.read(read_bitmap_data, width * height);
	file.close();

	// ������ ����, 24��Ʈ 3, 32��Ʈ 4
	size = width * height * 4;
	// ��ȯ�� ������ ���� ���� �Ҵ�
	data = (char*)malloc(size);
	memset(data, 0, size);
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
	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			// ���� �ε��� Ȯ��
			color_index = read_bitmap_data[image_BPS_8bit * h + w];
			// �̹��� �������� ���� ����
			putColor = color_palette[color_index];
			r = GetRValue(putColor);
			g = GetGValue(putColor);
			b = GetBValue(putColor);
			
			// ������� �˻�
			if (!check_bg(r, g, b)){
				// 32bit ���ۿ� RGB ���
				// �̹����� �������� ������ �ݴ��� ���� ������ �Է�
				index = (w + (height - 1 - h) * width) * 4;
				data[index] = r;
				data[index + 1] = g;
				data[index + 2] = b;
				data[index + 3] = a;
			}
		}
	}

	SAFE_FREE(read_bitmap_data);

	return this;
}

void Bitmap::converter_color(player_color _color)
{
	if (_color == none) return;

	COLORREF player_color = 0;			// �÷��̾� ����	
	BYTE tr = 0, tg = 0, tb = 0;		// ���÷� RGB
	BYTE pr = 0, pg = 0, pb = 0;		// �ȷ�Ʈ RGB
	BYTE r = 0, g = 0, b = 0, a = 0;			// ���� RGB
	
	
	int tmp = 0;					// ���� �ӽú���
	int index = 0;

	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			index = (h * width + w) * 4;
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