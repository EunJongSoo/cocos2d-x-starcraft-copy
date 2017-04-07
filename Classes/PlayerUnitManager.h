#ifndef PLAYER_UNIT_MANAGER_H_
#define PLAYER_UNIT_MANAGER_H_

#include "Header.h"

// class 전방선언
class Unit;

// namespace class 전방선언
namespace std {
	template < typename T, typename A> class vector;
}

namespace cocos2d {
	class Vec2;
}

class PlayerUnitManager {
public:
	PlayerUnitManager(const player_color _color, const player_type _type);
	~PlayerUnitManager();

	Unit* create_unit(const unit_type _type, const cocos2d::Vec2& _point);

	inline std::vector<Unit*>& PlayerUnitManager::get_unit_vector() { return unit_vector; }
	inline player_color get_color() const { return color; }
	inline player_type get_player_type() const { return type; }

private:
	PlayerUnitManager();
	std::vector<Unit*> unit_vector;
	
	// 플레이어 구분
	player_color color;
	player_type type;
};

#endif // !UNIT_MANAGER_H_
