#ifndef UNIT_MANAGER_H_
#define UNIT_MANAGER_H_

#include "Header.h"

// class 穿号 識情
class PlayerUnitManager;
class Unit;

// namespace class 穿号 識情
namespace std {
	template <typename T, typename A> class vector;
}

namespace eun {
	class Point;
}

class UnitManager {
public:
	UnitManager();
	~UnitManager();

	bool add_player();
	Unit* create_unit(const unit_type _type, const player_color _color, const eun::Point& _point);
	std::vector<PlayerUnitManager*>& get_unit_vector();

private:
	std::vector<PlayerUnitManager*> player_unit_manager_vector;

};

#endif // !UNIT_MANAGER_H_
