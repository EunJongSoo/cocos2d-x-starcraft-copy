#pragma once

// 안전 해제 전처리기
#define SAFE_DELETE(p)           do { if(p) { delete (p); (p) = nullptr; } } while(0)
#define SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define BREAK_IF(cond)           if(cond) break
// UnitManager;

// 임시로 무기도 추가
enum unit_state {
	production, idle, move, attack, patrol, hold, die
};

enum direction {
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
};

typedef enum unit_type {
	marine, marine_weapon
} building_type;


// 플레이어 색상 지정 열거체
enum player_color {
	red, blue, max
};
// PlayerUnitManager, UnitManager


// 플레이어 타입 지정 열거체
enum player_type {
	user, ai,
};
// PlayerUnitManager, UnitManager