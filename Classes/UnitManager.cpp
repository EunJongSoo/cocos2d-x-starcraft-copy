#include "UnitManager.h"
#include "Unit.h"

UnitManager::UnitManager() {
}

UnitManager::~UnitManager() {
}

void UnitManager::create_unit(const unit_type _type, const player_color _color, const float _pos_x, const float _pos_y) {

	for (PlayerUnitManager* manager : player_unit_manager_vector) {
		if (manager->get_color() == _color) {
			manager->create_unit(_type, _pos_x, _pos_y);
			return;
		}
	}
	
}
