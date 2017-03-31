#ifndef PLAYER_UNIT_MANAGER_H_
#define PLAYER_UNIT_MANAGER_H_

#include <vector>
#include "Header.h"

class Unit;
class PlayerUnitManager {
public:
	enum player_color {
		red, blue,
	};
	enum player_type {
		user, ai,
	};

public:
	PlayerUnitManager();
	~PlayerUnitManager();

	void create_unit(unit_type _type, const float _pos_x, const float _pos_y);
	
	inline player_color get_color() const { return _color; }

private:
	std::vector<Unit*> unit_vector;
	
	// 플레이어 구분
	player_color _color;

};

#endif // !UNIT_MANAGER_H_
