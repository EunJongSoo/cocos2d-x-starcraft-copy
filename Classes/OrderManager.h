/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : OrderManager.h
****************************/

#ifndef ORDER_MANAGER_H_
#define ORDER_MANAGER_H_

namespace std {
	template < typename T, typename A > class vector;
}

namespace cocos2d {
	class Vec2;
}

class InputInfo;
class PlayerUnitManager;
class Unit;

class OrderManager {
public:
	OrderManager();
	~OrderManager();

	void order_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _manager_vector, const std::vector<Unit*>& select_unit_vector);

private:
	void run_action_mouse_R_down(const cocos2d::Vec2& _vec2, const std::vector<PlayerUnitManager*>& _manager_vector, const std::vector<Unit*>& _unit_vector);
	Unit * find_click_unit(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector);
	void R_click_unit_process(Unit* _unit, const std::vector<Unit*>& _unit_vector);
	void R_click_not_unit_process(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector);
	void attack_unit(Unit* const _unit, const std::vector<Unit*>& _unit_vector);
	void move_unit(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector);
};

#endif // !ORDER_MANAGER_H_
