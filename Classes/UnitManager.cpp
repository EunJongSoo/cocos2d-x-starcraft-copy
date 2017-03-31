#include "UnitManager.h"
#include "Unit.h"

UnitManager::UnitManager() {
}

UnitManager::~UnitManager() {
}

void UnitManager::create_unit(unit_type _type, const float _pos_x, const float _pos_y) {
	Unit* unit = Unit::create(unit_type::marine);
	unit_vector.push_back(unit);
}
