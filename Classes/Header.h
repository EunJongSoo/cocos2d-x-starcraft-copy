#pragma once

// ���� ���� ��ó����
#define SAFE_DELETE(p)           do { if(p) { delete (p); (p) = nullptr; } } while(0)
#define SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define BREAK_IF(cond)           if(cond) break
// UnitManager;

// �ӽ÷� ���⵵ �߰�
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


// �÷��̾� ���� ���� ����ü
enum player_color {
	red, blue, max
};
// PlayerUnitManager, UnitManager


// �÷��̾� Ÿ�� ���� ����ü
enum player_type {
	user, ai,
};
// PlayerUnitManager, UnitManager