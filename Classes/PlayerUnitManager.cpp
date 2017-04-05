#include "PlayerUnitManager.h"
#include "Unit.h"

PlayerUnitManager::PlayerUnitManager() {}

PlayerUnitManager::PlayerUnitManager(player_color _color) : 
	_color(_color) 
{

}

PlayerUnitManager::~PlayerUnitManager()
{
}

Unit* PlayerUnitManager::create_unit(unit_type _type, const float _pos_x, const float _pos_y) {
	Unit* unit = Unit::create(_type, cocos2d::Vec2(_pos_x, _pos_y));
	unit_vector.push_back(unit);
	return unit;
}

