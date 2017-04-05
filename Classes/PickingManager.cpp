#include "PickingManager.h"
#include "InputInfo.h"
#include "MouseInfo.h"
#include "Unit.h"
#include "cocos2d.h"

PickingManager::PickingManager()
{

}

PickingManager::~PickingManager()
{
}

void PickingManager::picking_unit(InputInfo * const _input, const std::vector<Unit*>& _unit_array)
{
	if (_input->get_mouse_order()) {
		MouseInfo* info = _input->get_mouse_info();

		MouseInfo::mouse_state state = info->get_mouse_state();
		float x = info->get_start_pos_x();
		float y = info->get_start_pos_y();

		switch (state)
		{
		case MouseInfo::R_down: {

			run_action_mouse_R_down(x, y, _unit_array);
			break;
		}
		case MouseInfo::L_down: {
			
			run_action_mouse_L_down(x, y, _unit_array);
			break;
		}
		case MouseInfo::L_drag:		break;
		case MouseInfo::L_double:	break;
		case MouseInfo::L_up:		break;
		case MouseInfo::R_up:		break;
		}
		_input->init_input_info();
	}
}

void PickingManager::run_action_mouse_L_down(float _x, float _y, const std::vector<Unit*>& _unit_array)
{
	unselect_unit(_unit_array);
	Unit* unit = selected_unit(_x, _y, _unit_array);
	if (unit != nullptr) {
		unit->set_selete_unit(true);
	}
}

void PickingManager::run_action_mouse_R_down(float _x, float _y, const std::vector<Unit*>& _unit_array)
{
	Unit* unit = selected_unit(_x, _y, _unit_array);
	if (unit != nullptr) {
		Unit* selete_unit = get_selete_unit(_unit_array);
		selete_unit->attack_unit(unit);
	}
	else {
		Unit* selete_unit = get_selete_unit(_unit_array);
		if (selete_unit != nullptr) {
			selete_unit->move_unit(cocos2d::Vec2(_x, _y));
		}
	}
}

void PickingManager::unselect_unit(const std::vector<Unit*>& _unit_array)
{
	for (Unit* unit : _unit_array) {
		unit->set_selete_unit(false);
	}
}

Unit * PickingManager::get_selete_unit(const std::vector<Unit*>& _unit_array)
{
	for (Unit* unit : _unit_array) {
		if (unit->get_selete_unit()) {
			return unit;
		}
	}
	return nullptr;
}

Unit * PickingManager::selected_unit(float _x, float _y, const std::vector<Unit*>& _unit_array)
{
	for (Unit* unit : _unit_array) {
		cocos2d::Rect rect = unit->getBoundingBox();
		if (rect.containsPoint(cocos2d::Vec2(_x, _y))) {
			return unit;
		}
	}
	return nullptr;
}
