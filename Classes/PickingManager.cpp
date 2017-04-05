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

		switch (info->get_mouse_state())
		{
		case MouseInfo::R_down: {
			run_action_mouse_R_down(info, _unit_array);
			break;
		}
		case MouseInfo::L_down: {
			
			break;
		}
		case MouseInfo::L_dragging: {

			break;
		}
		case MouseInfo::L_drag: {
			run_action_mouse_L_drag(info, _unit_array);
			break;
		}
		case MouseInfo::L_double:	break;
		case MouseInfo::L_up: {
			run_action_mouse_L_up(info, _unit_array);
			break;
		}
		case MouseInfo::R_up:		break;
		}
		_input->init_input_info();
	}
}

void PickingManager::run_action_mouse_L_up(MouseInfo * const _info, const std::vector<Unit*>& _unit_array)
{
	unselect_unit(_unit_array);
	Unit* unit = click_selected_unit(_info, _unit_array);
	if (unit != nullptr) {
		unit->set_selete_unit(true);
	}
}

void PickingManager::run_action_mouse_R_down(MouseInfo * const _info, const std::vector<Unit*>& _unit_array)
{
	Unit* unit = click_selected_unit(_info, _unit_array);
	if (unit != nullptr) {
		Unit* selete_unit = get_selete_unit(_unit_array);
		selete_unit->attack_unit(unit);
	}
	else {
		Unit* selete_unit = get_selete_unit(_unit_array);
		if (selete_unit != nullptr) {
			// ÇÔ¼öÈ­ °í¹Î
			// ÇÔ¼öÈ­ °í¹Î
			// ÇÔ¼öÈ­ °í¹Î
			float x = _info->get_start_pos_x();
			float y = _info->get_start_pos_y();
			selete_unit->move_unit(cocos2d::Vec2(x, y));
		}
	}
}

void PickingManager::run_action_mouse_L_drag(MouseInfo * const _info, const std::vector<Unit*>& _unit_array)
{
	unselect_unit(_unit_array);
	Unit* unit = drag_selected_unit(_info, _unit_array);
	if (unit != nullptr) {
		unit->set_selete_unit(true);
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

Unit * PickingManager::click_selected_unit(MouseInfo * const _info, const std::vector<Unit*>& _unit_array)
{
	float x = _info->get_start_pos_x();
	float y = _info->get_start_pos_y();
	for (Unit* unit : _unit_array) {
		cocos2d::Rect rect = unit->getBoundingBox();
		if (rect.containsPoint(cocos2d::Vec2(x, y))) {
			return unit;
		}
	}
	return nullptr;
}

Unit * PickingManager::drag_selected_unit(MouseInfo * const _info, const std::vector<Unit*>& _unit_array)
{
	float start_x = _info->get_start_pos_x();
	float start_y = _info->get_start_pos_y();
	
	float end_x = _info->get_end_pos_x();
	float end_y = _info->get_end_pos_y();
	
	float min_x = MIN(start_x, end_x);
	float min_y = MIN(start_y, end_y);
	
	float width = fabsf(start_x - end_x);
	float height = fabsf(start_y - end_y);

	cocos2d::Rect drag_rect = cocos2d::Rect(min_x, min_y, width, height);

	for (Unit* unit : _unit_array) {
		cocos2d::Rect rect = unit->getBoundingBox();
		if (rect.intersectsRect(drag_rect)) {
			return unit;
		}
	}
	return nullptr;
}
