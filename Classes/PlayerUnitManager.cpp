#include <vector>
#include "PlayerUnitManager.h"
#include "Unit.h"
#include "Point.h"

// �Ŵ��� ������ ����� ��ǻ������ �������� �Ű������� �޴´�.
PlayerUnitManager::PlayerUnitManager(const player_color _color, const player_type _type) : 
	color(_color), 
	type(_type)
{}

PlayerUnitManager::PlayerUnitManager() {}
PlayerUnitManager::~PlayerUnitManager() {}

// ������ �����Ѵ�.
Unit* PlayerUnitManager::create_unit(const unit_type _type, const eun::Point& _point) {
	// ������ ������ ��ġ�� �޾Ƽ� �����Ѵ�.
	Unit* unit = Unit::create(_type, _point);
	// ���Ϳ� �����Ѵ�.
	unit_vector.push_back(unit);
	// ������ ������ �����͸� ��ȯ�Ѵ�.
	return unit;
}

inline player_color PlayerUnitManager::get_color() const
{
	// �Ŵ����� ����ϴ� �÷��̾� ������ ��ȯ�Ѵ�.
	 return color;
}

inline player_type PlayerUnitManager::get_player_type() const
{
	// �Ŵ����� ����ϴ� �÷��̾� Ÿ���� ��ȯ�Ѵ�.
	return type;
}

inline std::vector<Unit*>& PlayerUnitManager::get_unit_vector()
{
	// �÷��̾��� ���� ���͸� ��ȯ�Ѵ�.
	return unit_vector;
}

