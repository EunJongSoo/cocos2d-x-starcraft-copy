/****************************
������ : 2017-02-19
�ۼ��� : ������
���ϸ� : OrderManager.cpp
****************************/

#include <vector>
#include "OrderManager.h"

#include "PlayerUnitManager.h"
#include "Unit.h"
#include "InputInfo.h"

OrderManager::OrderManager()
{
}

OrderManager::~OrderManager()
{
}

void OrderManager::order_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _manager_vector, const std::vector<Unit*>& _select_unit_vector)
{
	// ���콺 ��� Ȯ��
	MouseInfo* info = _input->get_mouse_info();

	// �Էµ� ����� ������ ����� �����Ѵ�.
	if (info) {
		// ���콺 ��� ������ ���� �ش� �̺�Ʈ�� ����
		switch (info->get_mouse_state())
		{
		case MouseInfo::Mouse_state::R_down: {
			run_action_mouse_R_down(info->get_start_pos(), _manager_vector, _select_unit_vector);
			break;
		}
		}
	}
}

// ���콺 ����Ŭ�� �����Ҷ� �̺�Ʈ
void OrderManager::run_action_mouse_R_down(const cocos2d::Vec2& _vec2, const std::vector<PlayerUnitManager*>& _manager_vector, const std::vector<Unit*>& _select_unit_vector)
{
	// ���õ� ������ �ִ��� Ȯ���Ѵ�.
	if (_select_unit_vector.empty()) {
		// ������ ����������.
		return;
	}

	// ������ ������ ������ Ȯ���ؼ� �÷��̾� ���ָ� �����Ѵ�.
	// ���� �߰��Ǿ�� �ϴºκ�
	// ���� �߰��Ǿ�� �ϴºκ�
	// ���� �߰��Ǿ�� �ϴºκ�


	// Ŭ���� ������ ������ ã�´�.
	// ��ü ���� ��Ͽ��� ã�ƾ��Ѵ�.
	Unit* unit = nullptr;
	for (PlayerUnitManager* manager : _manager_vector) {
		std::vector<Unit*>& manager_unit_vector = manager->get_unit_vector();
		unit = find_click_unit(_vec2, manager_unit_vector);
		// ������ ã���� �˻��� �ߴ��Ѵ�.
		if (unit != nullptr) {
			// �������� ó���� �Ѵ�.
			R_click_unit_process(unit, _select_unit_vector);
			return;
		}
	}
	// �������� ó���� �Ѵ�.
	R_click_not_unit_process(_vec2, _select_unit_vector);
}

void OrderManager::R_click_unit_process(Unit* _unit, const std::vector<Unit*>& _select_unit_vector)
{
	// ������ �Ҽ����� ���� ����� �޶�������
	// ���� �ൿ�� �����ϴ� Ŭ������ ��������� �� ���� �ʿ�
	attack_unit(_unit, _select_unit_vector);
}

void OrderManager::R_click_not_unit_process(const cocos2d::Vec2& _end_vec2, const std::vector<Unit*>& _select_unit_vector)
{
	// ������ �̵��� �Ѵ�.
	// ���� ��ġ�� �̵� �������� �ʿ��ϴ�.
	
	// ���õ� ������ �߰��� ã��
	for (Unit* unit : _select_unit_vector) {

		unit->getPosition();

	}



	CCLOG("pos_x : %f, pos_y : %f", _end_vec2.x, _end_vec2.y);
	move_unit(_end_vec2, _select_unit_vector);
}

Unit * OrderManager::find_click_unit(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector)
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

// ������ �����Ѵ�.
// ���� �ൿ �Լ��� ���� ������ ����ɼ� �ִ�.
void OrderManager::attack_unit(Unit* const _unit, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		unit->attack_unit(_unit);
	}
}

// ������ �̵��Ѵ�.
// ���� �ൿ �Լ��� ���� ������ ����ɼ� �ִ�.
void OrderManager::move_unit(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		unit->move_unit(_vec2);
	}
}