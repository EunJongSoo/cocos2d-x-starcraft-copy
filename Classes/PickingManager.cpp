#include <vector>
#include "PickingManager.h"
#include "Unit.h"
#include "PlayerUnitManager.h"
#include "cocos2d.h"
#include "Header.h"

#include "InputInfo.h"
#include "MouseInfo.h"

PickingManager::PickingManager():
	selete_unit_vector(nullptr)
{
	selete_unit_vector = new std::vector<Unit*>;
}
PickingManager::~PickingManager() {
	SAFE_DELETE(selete_unit_vector);
}

// input ������ Ȯ���Ͽ� ���� �̺�Ʈ�� ����
std::vector<Unit*>* PickingManager::picking_unit(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _manager_vector)
{
	// ���콺 ��� Ȯ��
	MouseInfo* info = _input->get_mouse_info();
	// ���콺 ��� ������ ���� �ش� �̺�Ʈ�� ����
	switch (info->get_mouse_state())
	{
	case MouseInfo::R_down: {
		run_action_mouse_R_down(info->get_start_pos(), _manager_vector);
		break;
	}
	case MouseInfo::L_down: {

		break;
	}
	case MouseInfo::L_dragging: {
		break;
	}
	case MouseInfo::L_drag: {
		run_action_mouse_L_drag(info->get_start_pos(), info->get_end_pos(), _manager_vector);
		break;
	}
	case MouseInfo::L_double:	break;
	case MouseInfo::L_up: {
		run_action_mouse_L_up(info->get_end_pos(), _manager_vector);
		break;
	}
	case MouseInfo::R_up:		break;
	}
	return selete_unit_vector;
}

// ���콺 ��Ŭ�� ������ �̺�Ʈ
void PickingManager::run_action_mouse_L_up(const cocos2d::Vec2& _vec2, const std::vector<PlayerUnitManager*>& _manager_vector)
{
	// ������ Ŭ�� �Ǿ������� ó���� �Ѵ�.
	for (PlayerUnitManager* manager : _manager_vector) {
		std::vector<Unit*>& unit_vector = manager->get_unit_vector();
		mouse_L_up_process(_vec2, unit_vector);
	}
}

// ���콺 ��Ŭ�� �巡�� ������ �̺�Ʈ
void PickingManager::run_action_mouse_L_drag(const cocos2d::Vec2& _str_vec2, const cocos2d::Vec2& _end_vec2, const std::vector<PlayerUnitManager*>& _manager_vector)
{
	// ��� ���õ� ������ ����Ѵ�.
	for (PlayerUnitManager* manager : _manager_vector) {
		std::vector<Unit*>& unit_vector = manager->get_unit_vector();
		mouse_L_drag_process(_str_vec2, _end_vec2, unit_vector);
	}
}

// ���콺 ����Ŭ�� �����Ҷ� �̺�Ʈ
void PickingManager::run_action_mouse_R_down(const cocos2d::Vec2& _vec2, const std::vector<PlayerUnitManager*>& _manager_vector)
{
	for (PlayerUnitManager* manager : _manager_vector) {
		std::vector<Unit*>& unit_vector = manager->get_unit_vector();
		mouse_R_down_process(_vec2, unit_vector, _manager_vector);
	}
}

void PickingManager::mouse_L_up_process(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector)
{
	// ������ ������ ����Ѵ�.
	select_unit(_unit_vector, false);

	// Ŭ���� ������ ã�´�.
	Unit* unit = find_click_unit(_vec2, _unit_vector);

	// ���õ� ������ �ִ��� Ȯ���Ѵ�.
	if (is_unit(unit)) {
		// ������ �����Ѵ�.
		select_unit(unit, true);
	}
}

void PickingManager::mouse_L_drag_process(const cocos2d::Vec2& _str_vec2, const cocos2d::Vec2& _end_vec2, const std::vector<Unit*>& _unit_vector)
{
	// ���� ������ ����Ѵ�.
	select_unit(_unit_vector, false);
	// �巡���� ������ ã�´�.
	std::vector<Unit*> unit_vector = find_drag_unit(_str_vec2, _end_vec2, _unit_vector);
	if (is_unit(unit_vector)) {
		select_unit(unit_vector, true);
	}
}

void PickingManager::mouse_R_down_process(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector, const std::vector<PlayerUnitManager*>& _manager_vector)
{
	// ���õ� ������ ã�´�.
	std::vector<Unit*> select_unit_vector = find_select_unit(_unit_vector);

	// ���õ� ������ �ִ��� Ȯ���Ѵ�.
	if (!is_unit(select_unit_vector)) {
		// ������ ����������.
		return;
	}

	// ������ ������ ������ Ȯ���Ѵ�.
	// ���� �߰��Ǿ�� �ϴºκ�
	// ���� �߰��Ǿ�� �ϴºκ�
	// ���� �߰��Ǿ�� �ϴºκ�


	// Ŭ���� ������ ������ ã�´�.
	// ��ü ���� ��Ͽ��� ã�ƾ��Ѵ�.
	Unit* unit = nullptr;
	std::vector<Unit*> manager_unit_vector;
	for (PlayerUnitManager* manager : _manager_vector) {
		manager_unit_vector = manager->get_unit_vector();
		unit = find_click_unit(_vec2, manager_unit_vector);
		// ������ ã���� �˻��� �ߴ��Ѵ�.
		if (unit != nullptr) {
			break;
		}
	}
	// ������ �ִ��� Ȯ���Ѵ�.
	if (is_unit(unit))
	{
		// �������� ó���� �Ѵ�.
		R_click_unit_process(unit, select_unit_vector);
	}
	else
	{
		// �������� ó���� �Ѵ�.
		R_click_not_unit_process(_vec2, select_unit_vector);
	}
}

void PickingManager::R_click_unit_process(Unit* _unit, const std::vector<Unit*>& _unit_vector)
{
	// ������ �Ҽ����� ���� ����� �޶�������
	// ���� �ൿ�� �����ϴ� Ŭ������ ��������� �� ���� �ʿ�
	attack_unit(_unit, _unit_vector);
}

void PickingManager::R_click_not_unit_process(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector)
{
	CCLOG("pos_x : %f, pos_y : %f", _vec2.x, _vec2.y);
	move_unit(_vec2, _unit_vector);
}

// ������ ������ bool ���°� ����
void PickingManager::select_unit(Unit* const _unit, bool _b)
{
	_unit->set_select_unit(_b);
}

// ������ ���ֵ��� bool ���°� ����
void PickingManager::select_unit(const std::vector<Unit*>& _unit_vector, bool _b)
{
	// ��ü ���ִ������ �˻�
	for (Unit* unit : _unit_vector) {
		// ������ bool �� ����
		unit->set_select_unit(_b);
	}
}

// Ŭ���� ������ ã�´�.
Unit * PickingManager::find_click_unit(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		// ������ �ٿ�� �ڽ� ����
		cocos2d::Rect rect = unit->getBoundingBox();
		// �ٿ�� �ڽ��� ��ġ�� ��ġ���� Ȯ��
		if (rect.containsPoint(_vec2)) {
			// ��ģ ���� ��ȯ
			return unit;
		}
	}
	// ��ģ ������ ������ nullptr ��ȯ
	return nullptr;
}

// �巡���� ������ ã�´�.
std::vector<Unit*> PickingManager::find_drag_unit(const cocos2d::Vec2& _str_vec2, const cocos2d::Vec2& _end_vec2, const std::vector<Unit*>& _unit_vector)
{
	std::vector<Unit*> select_unit_vector;
	
	// ���콺 Ŭ���� �� ������ ���� �簢���� ���� �Ʒ����� ã�´�.
	// cocos2d-x�� ��ǥ��� ���� �Ʒ��� 0, 0
	cocos2d::Vec2 min_pos(MIN(_str_vec2.x, _end_vec2.x), MIN(_str_vec2.y, _end_vec2.y));
	
	// �巡���� ũ�⸦ ����Ѵ�.
	// ù ����Ʈ���� ������ ����Ʈ�� ���� ���밪���� ����
	cocos2d::Size size(fabsf(_str_vec2.x - _end_vec2.x), fabsf(_str_vec2.y - _end_vec2.y));

	// ���� �Ʒ� ������ ���� ���� ũ�⸦ ����ؼ� Rect ������ �����.
	cocos2d::Rect drag_rect = cocos2d::Rect(min_pos, size);

	for (Unit* unit : _unit_vector) {
		cocos2d::Rect rect = unit->getBoundingBox();
		// ������ �ٿ�� �ڽ��� �巡�׷� ���� �ڽ��� ��ġ���� �˻�
		if (rect.intersectsRect(drag_rect)) {
			// ������ ������ 12���� �Ǹ� �˻��� �����Ѵ�.
			if (select_unit_vector.size() == 12) {
				break;
			}
			// ��ģ ������ vector�� ����
			select_unit_vector.push_back(unit);
		}
	}
	return select_unit_vector;
}

// ���� ���õ� ������ ã�´�.
std::vector<Unit*> PickingManager::find_select_unit(const std::vector<Unit*>& _unit_vector)
{
	// ���õ� ������ ������ ����
	std::vector<Unit*> select_unit_vector;
	for (Unit* unit : _unit_vector) {
		// ������ ���õǾ����� Ȯ��
		if (unit->is_select()) {
			// ���õ� ������ ����
			select_unit_vector.push_back(unit);
		}
	}
	// ��ȯ�� ����Ǿ� ��ȯ
	return select_unit_vector;
}

// ������ �����Ѵ�.
// ���� �ൿ �Լ��� ���� ������ ����ɼ� �ִ�.
void PickingManager::attack_unit(Unit* const _unit, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		unit->attack_unit(_unit);
	}
}

// ������ �̵��Ѵ�.
// ���� �ൿ �Լ��� ���� ������ ����ɼ� �ִ�.
void PickingManager::move_unit(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		unit->move_unit(_vec2);
	}
}

// ������ �ִ��� Ȯ���Ѵ�.
inline bool PickingManager::is_unit(Unit * _unit)
{
	return (_unit != nullptr); 
}

// ������ �ִ��� Ȯ���Ѵ�.
inline bool PickingManager::is_unit(const std::vector<Unit*>& _unit_vector)
{
	return (_unit_vector.size() > 0);
}
