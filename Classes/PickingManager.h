#ifndef PICKING_MANAGER_H_
#define PICKING_MANAGER_H_

#include <vector>

class Unit;
class InputInfo;
class MouseInfo;

class PickingManager {
public:
	PickingManager();
	~PickingManager();

	void picking_unit(InputInfo * const _input, const std::vector<Unit*>& _unit_array);

private:
	void run_action_mouse_L_up(MouseInfo * const _info, const std::vector<Unit*>& _unit_array);
	void run_action_mouse_R_down(MouseInfo * const _info, const std::vector<Unit*>& _unit_array);
	void run_action_mouse_L_drag(MouseInfo * const _info, const std::vector<Unit*>& _unit_array);
	void unselect_unit(const std::vector<Unit*>& _unit_array);
	Unit* get_selete_unit(const std::vector<Unit*>& _unit_array);
	Unit* click_selected_unit(MouseInfo * const _info, const std::vector<Unit*>& _unit_array);
	Unit* drag_selected_unit(MouseInfo * const _info, const std::vector<Unit*>& _unit_array);

};

#endif
