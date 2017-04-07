#ifndef UNIT_MANAGER_H_
#define UNIT_MANAGER_H_

#include "Header.h"

// class ���� ����
class PlayerUnitManager;
class Unit;

// namespace class ���� ����
namespace std {
	template <typename T, typename A> class vector;
}

namespace cocos2d {
	class Vec2;
}

class UnitManager {
public:
	UnitManager();
	~UnitManager();

	bool add_player();
	Unit* create_unit(const unit_type _type, const player_color _color, const cocos2d::Vec2& _vec2);
	std::vector<PlayerUnitManager*>& get_unit_manager_vector();

private:
	std::vector<PlayerUnitManager*> player_unit_manager_vector;
	bool add_player_manager(const bool _b, const player_color color);

	// �ִ� �Ŵ��� ����
	const int max_player_manager = 8;
};

#endif // !UNIT_MANAGER_H_
