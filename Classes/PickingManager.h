#ifndef PICKING_MANAGER_H_
#define PICKING_MANAGER_H_

// class 穿号識情
class Unit;
class InputInfo;
class MouseInfo;
class PlayerUnitManager;

// namespace class 穿号識情
namespace std {
	template < typename T, typename A> class vector;
}

namespace eun {
	class Point;
}

class PickingManager {
public:
	PickingManager();
	~PickingManager();

	void picking_unit(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _manager_vector);

private:
	void run_action_mouse_L_up(MouseInfo * const _info, const std::vector<PlayerUnitManager*>& _manager_vector);
	void run_action_mouse_L_drag(MouseInfo * const _info, const std::vector<PlayerUnitManager*>& _manager_vector);
	void run_action_mouse_R_down(MouseInfo * const _info, const std::vector<PlayerUnitManager*>& _manager_vector);
	void mouse_L_up_process(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector);
	void mouse_L_drag_process(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector);
	void mouse_R_down_process(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector, const std::vector<PlayerUnitManager*>& _manager_vector);
	
	void R_click_unit_process(Unit* _unit, const std::vector<Unit*>& _unit_vector);
	void R_click_not_unit_process(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector);

	void select_unit(Unit* const _unit, bool _b);
	void select_unit(const std::vector<Unit*>& _unit_vector, bool _b);
	Unit* find_click_unit(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector);
	std::vector<Unit*> find_drag_unit(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector);
	std::vector<Unit*> find_select_unit(const std::vector<Unit*>& _unit_vector);
	void attack_unit(Unit* const _unit, const std::vector<Unit*>& _unit_vector);
	void move_unit(eun::Point _point, const std::vector<Unit*>& _unit_vector);
	

	inline bool is_unit(Unit* _unit);
	inline bool is_unit(const std::vector<Unit*>& _unit_vector);
};

#endif
