#ifndef PICKING_MANAGER_H_
#define PICKING_MANAGER_H_

// class 穿号識情
class Unit;
class PlayerUnitManager;

class InputInfo;

// namespace class 穿号識情
namespace std {
	template < typename T, typename A> class vector;
}

namespace cocos2d {
	class Vec2;
	class Rect;
}

class PickingManager {
public:
	PickingManager();
	~PickingManager();

	const std::vector<Unit*>& picking_unit(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _manager_vector);

private:
	void run_action_mouse_L_up(const cocos2d::Vec2& _vec2, const std::vector<PlayerUnitManager*>& _manager_vector);
	void run_action_mouse_L_drag(const cocos2d::Vec2& _str_vec2, const cocos2d::Vec2& _end_vec2, const std::vector<PlayerUnitManager*>& _manager_vector);
	//void run_action_mouse_R_down(const cocos2d::Vec2& _vec2, const std::vector<PlayerUnitManager*>& _manager_vector);
	bool mouse_L_up_process(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector);
	//void mouse_L_drag_process(const cocos2d::Rect& _drag_rect, const std::vector<Unit*>& _unit_vector);
	//void mouse_R_down_process(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector, const std::vector<PlayerUnitManager*>& _manager_vector);
	
	//void R_click_unit_process(Unit* _unit, const std::vector<Unit*>& _unit_vector);
	//void R_click_not_unit_process(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector);

	//void select_unit(Unit* const _unit, bool _b);
	//void select_unit(const std::vector<Unit*>& _unit_vector, bool _b);
	Unit* find_click_unit(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector);
	bool find_drag_unit(const cocos2d::Rect& _drag_rect, const std::vector<Unit*>& _unit_vector, std::vector<Unit*>& tmp_select_unit_vector);
	//std::vector<Unit*> find_select_unit(const std::vector<Unit*>& _unit_vector);
	//void attack_unit(Unit* const _unit, const std::vector<Unit*>& _unit_vector);
	//void move_unit(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector);
	
	inline bool is_unit(Unit* _unit);

	std::vector<Unit*> select_unit_vector;
};

#endif
