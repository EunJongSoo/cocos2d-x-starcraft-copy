#ifndef UNIT_MANAGER_H_
#define UNIT_MANAGER_H_

#include <vector>
#include "Header.h"
#include "PlayerUnitManager.h"

class UnitManager {
private:
	typedef PlayerUnitManager::player_color player_color;
public:
	UnitManager();
	~UnitManager();

	bool add_player();
	Unit* create_unit(const unit_type _type, const player_color _color, const float _pos_x, const float _pos_y);
	std::vector<Unit*>& get_unit_array();

private:
	std::vector<Unit*> player_unit_vector;
	std::vector<PlayerUnitManager*> player_unit_manager_vector;

};

#endif // !UNIT_MANAGER_H_
