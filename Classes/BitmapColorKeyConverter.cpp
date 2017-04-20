#include "BitmapColorKeyConverter.h"
#include "Bitmap.h"
#include <Windows.h>

BitmapColorKeyConverter::BitmapColorKeyConverter()
{
}

BitmapColorKeyConverter::~BitmapColorKeyConverter()
{
}

void BitmapColorKeyConverter::converter_colorkey(Bitmap * _bitmap, player_color _color) {
	COLORREF player_color = 0;			// 플레이어 색상	
	BYTE tr = 0, tg = 0, tb = 0;		// 팀컬러 RGB
	BYTE pr = 0, pg = 0, pb = 0;		// 팔레트 RGB
	BYTE r = 0, g = 0, b = 0, a = 0;			// 최종 RGB

	int width = _bitmap->get_bitmap_width();
	int height = _bitmap->get_bitmap_height();
	char* data = _bitmap->get_data();

	int index = 0;

	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			index = (h * width + w) * 4;
			
			// 데이터에 순서대로 접근한다.
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
				int tmp = (pg == 0) ? tg - pr : tg - pg;
				g = (tmp > 0) ? tmp : 0;
				b = (tb - pb > 0) ? tb - pb : 0;

				data[index] = r;
				data[index + 1] = g;
				data[index + 2] = b;
			}
		}
	}
}



//
// R: 32 ~ 255
// G: 0 ~ 16
// B: 56 ~ 255
//
bool BitmapColorKeyConverter::check_colorkey(unsigned char r, unsigned char g, unsigned char b) const {
	return (r > 32 && g < 16 && b > 56);
}

COLORREF BitmapColorKeyConverter::get_player_color(player_color _color) const {
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