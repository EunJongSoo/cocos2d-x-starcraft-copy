/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : Header.h
****************************/

#pragma once

// 안전해제
#define SAFE_DELETE(p)           do { if(p) { delete (p); (p) = nullptr; } } while(0)
#define SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
// UnitManager, MouseManager

// 임시로 무기도 추가
enum class UnitState {
	production,			// 생산중
	idle,				// 대기
	move,				// 이동
	attack,				// 공격
	patrol,				// 순찰
	hold,				// 고정
	die					// 사망
};

enum Direction {
	up,
	up_right1,
	up_right2,
	up_right3,
	right,
	down_right1,
	down_right2,
	down_right3,
	down,

	left_check = 10,
	up_left1,
	up_left2,
	up_left3,
	left,
	down_left1,
	down_left2,
	down_left3,
	
	center
};

typedef enum unit_type {
	marine, marine_weapon
} building_type;
// UnitLayer, UnitManager, PlayerUnitManager, Unit, UnitWeapon


// 플레이어 색상 지정 열거체
enum player_color {
	kWhite = 0,
	kRed,
	kBlue,
	kTeal,
	kPurple,
	kYellow,
	kOrange,
	kGreen,
	kLightPink,
	kViolet,
	kLightGrey,
	kDarkGreen,
	kBrown,
	kLightGreen,
	kDarkGrey,
	kPink,
	none
};
// PlayerUnitManager, UnitManager

enum map_tile_set {
	badlands,
	space_platform,
	installation,
	ash_world,
	jungle_world,
	desert,
	ice,
	twilight
};
// MapFileInfo, BitmapManager

// 플레이어 타입 지정 열거체
enum player_type {
	user, ai,
};
// PlayerUnitManager, UnitManager

struct CV5 {
	struct cv5_data {
		unsigned char something[20];
		unsigned short mega_tile_index[16];
	} group[4096];
};


//namespace std
//{
//	template < class T > struct less;
//	template < class T1, class T2 > struct pair;
//	template < class T > class allocator;
//	template < class T, class Allocator > class list;
//	template < class T, class Allocator > class vector;
//	template < class Key, class T, class Compare, class Allocator > class map;
//}

//struct MyCompare
//{
//	bool operator() (const int & p_lhs, const int & p_rhs)
//	{
//		if (p_lhs > p_rhs) { return true; }
//		if (p_lhs < p_rhs) { return false; }
//		return (p_lhs > p_rhs);
//	}
//};
//
//std::map<int, int, MyCompare, std::allocator < int >>* Test();

// 전방선언
//#define LIST_FWD(x_type)  std::list<x_type, std::allocator<x_type> >
//#define VECTOR_FWD(x_type)  std::vector<x_type, std::allocator<x_type> >
//#define MAP_FWD(x_key,x_value)  std::map<x_key, x_value, std::less<x_key>, std::allocator<std::pair<const x_key,x_value> > >