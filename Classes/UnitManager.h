#ifndef UNIT_MANAGER_H_
#define UNIT_MANAGER_H_

#include <vector>
#include "Header.h"
#include "PlayerUnitManager.h"

class UnitManager {
private:
	typedef PlayerUnitManager::player_color player_color;
public:
	

public:
	UnitManager();
	~UnitManager();

	bool add_player();
	void create_unit(const unit_type _type, const player_color _color, const float _pos_x, const float _pos_y);

private:
	std::vector<PlayerUnitManager*> player_unit_manager_vector;

};

#endif // !UNIT_MANAGER_H_
