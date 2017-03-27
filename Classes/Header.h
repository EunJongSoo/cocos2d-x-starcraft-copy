#pragma once

enum unit_state {
	production, idle, move, attack, petrol, hold, die
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