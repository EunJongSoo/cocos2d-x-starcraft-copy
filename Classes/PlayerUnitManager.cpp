#include <vector>
#include "PlayerUnitManager.h"
#include "Unit.h"
#include "cocos2d.h"

// 매니저 생성시 색상과 컴퓨터인지 유저인지 매개변수를 받는다.
PlayerUnitManager::PlayerUnitManager(const player_color _color, const player_type _type) : 
	color(_color), 
	type(_type)
{}

PlayerUnitManager::PlayerUnitManager() {}
PlayerUnitManager::~PlayerUnitManager() {}

// 유닛을 생선한다.
Unit* PlayerUnitManager::create_unit(const unit_type _type, const cocos2d::Vec2& _vec2) {
	// 유닛의 종류와 위치를 받아서 생성한다.
	Unit* unit = Unit::create(_type, _vec2, color);
	// 벡터에 저장한다.
	unit_vector.push_back(unit);
	// 저장한 유닛의 포인터를 반환한다.
	return unit;
}