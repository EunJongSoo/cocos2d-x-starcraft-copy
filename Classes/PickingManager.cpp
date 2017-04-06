#include <vector>
#include "PickingManager.h"
#include "InputInfo.h"
#include "MouseInfo.h"
#include "Unit.h"
#include "cocos2d.h"

using namespace std;

PickingManager::PickingManager()
{
}

PickingManager::~PickingManager()
{
}

// input ������ Ȯ���Ͽ� ���� �̺�Ʈ�� ����
void PickingManager::picking_unit(InputInfo * const _input, const std::vector<Unit*>& _unit_vector)
{
	// ���콺 ��� Ȯ��
	if (_input->get_mouse_order()) {
		MouseInfo* info = _input->get_mouse_info();

		// ���콺 ��� ������ ���� �ش� �̺�Ʈ�� ����
		switch (info->get_mouse_state())
		{
		case MouseInfo::R_down: {
			run_action_mouse_R_down(info, _unit_vector);
			break;
		}
		case MouseInfo::L_down: {
			
			break;
		}
		case MouseInfo::L_dragging: {

			break;
		}
		case MouseInfo::L_drag: {
			run_action_mouse_L_drag(info, _unit_vector);
			break;
		}
		case MouseInfo::L_double:	break;
		case MouseInfo::L_up: {
			run_action_mouse_L_up(info, _unit_vector);
			break;
		}
		case MouseInfo::R_up:		break;
		}
		
		// Ȯ���� ��� �ʱ�ȭ
		_input->init_input_info();
	}
}

// ���콺 ��Ŭ�� ������ �̺�Ʈ
void PickingManager::run_action_mouse_L_up(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector)
{
	// ��� ���õ� ������ ����Ѵ�.
	select_unit(_unit_vector, false);
	
	// Ŭ���� ������ ã�´�.
	Unit* unit = find_click_unit(_info, _unit_vector);
	
	// ���õ� ������ �ִ��� Ȯ���Ѵ�.
	if (is_unit(unit)) {
		// ������ �����Ѵ�.
		select_unit(unit, true);
	}
}

// ���콺 ����Ŭ�� �����Ҷ� �̺�Ʈ
void PickingManager::run_action_mouse_R_down(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector)
{
	// Ŭ���� ������ ã�´�.
	Unit* unit = find_click_unit(_info, _unit_vector);
	if (is_unit(unit)) 
	{
		// ���� ���õ� ������ ã�´�.
		// ��ȯ�Ǵ� ���� �����ؼ� �ӽ÷� ���������� �����Ͽ� ���
		std::vector<Unit*> unit_vector = find_select_unit(_unit_vector);
		if (is_unit(unit_vector)) {
			// ���õ� ���ֿ��� ������ ����Ѵ�.
			
			// ������ �Ҽ����� ���� ����� �޶�������
			// ���� �ൿ�� �����ϴ� Ŭ������ ��������� �� ���� �ʿ�
			attack_unit(unit, unit_vector);
		}
	}
	else {
		std::vector<Unit*> unit_vector = find_select_unit(_unit_vector);
		if (is_unit(unit_vector)) {
			// ���õ� ���ֿ��� �̵��� ����Ѵ�.
			move_unit(_info->get_start_pos(), unit_vector);
		}
	}
}

// ���콺 ��Ŭ�� �巡�� ������ �̺�Ʈ
void PickingManager::run_action_mouse_L_drag(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector)
{
	// ������ ������ ����Ѵ�.
	select_unit(_unit_vector, false);
	// �巡���� ������ ã�´�.
	std::vector<Unit*> unit_vector = find_drag_unit(_info, _unit_vector);
	if (is_unit(unit_vector)) {
		select_unit(unit_vector, true);
	}
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
Unit * PickingManager::find_click_unit(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector)
{
	// ��ġ ���� �ӽ�����
	eun::Point point = _info->get_start_pos();
	for (Unit* unit : _unit_vector) {
		// ������ �ٿ�� �ڽ� ����
		cocos2d::Rect rect = unit->getBoundingBox();
		// �ٿ�� �ڽ��� ��ġ�� ��ġ���� Ȯ��
		if (rect.containsPoint(cocos2d::Vec2(point.x, point.y))) {
			// ��ģ ���� ��ȯ
			return unit;
		}
	}
	// ��ģ ������ ������ nullptr ��ȯ
	return nullptr;
}

// �巡���� ������ ã�´�.
std::vector<Unit*> PickingManager::find_drag_unit(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector)
{
	std::vector<Unit*> select_unit_vector;

	// ���콺 Ŭ���� ù ����Ʈ �ӽ� ����
	eun::Point start_point = _info->get_start_pos();
	// ���콺 Ŭ���� ������ ����Ʈ �ӽ� ����
	eun::Point end_point = _info->get_end_pos();
	
	// ���콺 Ŭ���� �� ������ ���� �簢���� ���� �Ʒ����� ã�´�.
	// cocos2d-x�� ��ǥ��� ���� �Ʒ��� 0, 0
	eun::Point min_point = start_point.min_point(end_point);
	
	// �巡���� ũ�⸦ ����Ѵ�.
	// ù ����Ʈ���� ������ ����Ʈ�� ���� ���밪���� ����
	float width = fabsf(start_point.x - end_point.x);
	float height = fabsf(start_point.y - end_point.y);

	// ���� �Ʒ� ������ ���� ���� ũ�⸦ ����ؼ� Rect ������ �����.
	cocos2d::Rect drag_rect = cocos2d::Rect(min_point.x, min_point.y, width, height);

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
void PickingManager::move_unit(eun::Point _point, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		unit->move_unit(_point);
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
