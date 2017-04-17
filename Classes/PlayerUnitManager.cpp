#include <vector>
#include "PlayerUnitManager.h"
#include "Unit.h"
#include "cocos2d.h"

// �Ŵ��� ������ ����� ��ǻ������ �������� �Ű������� �޴´�.
PlayerUnitManager::PlayerUnitManager(const player_color _color, const player_type _type) : 
	color(_color), 
	type(_type)
{}

PlayerUnitManager::PlayerUnitManager() {}
PlayerUnitManager::~PlayerUnitManager() {}

// ������ �����Ѵ�.
Unit* PlayerUnitManager::create_unit(const unit_type _type, const cocos2d::Vec2& _vec2) {
	// ������ ������ ��ġ�� �޾Ƽ� �����Ѵ�.
	Unit* unit = Unit::create(_type, _vec2, color);
	// ���Ϳ� �����Ѵ�.
	unit_vector.push_back(unit);
	// ������ ������ �����͸� ��ȯ�Ѵ�.
	return unit;
}