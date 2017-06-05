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

void OrderManager::order_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _manager_vector, const std::vector<Unit*>& select_unit_vector)
{
	// 마우스 명령 확인
	MouseInfo* info = _input->get_mouse_info();
	if (info) {
		// 마우스 명령 종류에 따라 해당 이벤트를 동작
		switch (info->get_mouse_state())
		{
		case MouseInfo::R_down: {
			run_action_mouse_R_down(info->get_start_pos(), _manager_vector, select_unit_vector);
			break;
		}
		}
	}
}

// 마우스 오른클릭 시작할때 이벤트
void OrderManager::run_action_mouse_R_down(const cocos2d::Vec2& _vec2, const std::vector<PlayerUnitManager*>& _manager_vector, const std::vector<Unit*>& _unit_vector)
{
	// 선택된 유닛이 있는지 확인한다.
	if (_unit_vector.empty()) {
		// 없으면 빠져나간다.
		return;
	}

	// 선택한 유닛의 색상의 확인한다.
	// 이후 추가되어야 하는부분
	// 이후 추가되어야 하는부분
	// 이후 추가되어야 하는부분


	// 클릭한 지점의 유닛을 찾는다.
	// 전체 유닛 목록에서 찾아야한다.
	Unit* unit = nullptr;
	for (PlayerUnitManager* manager : _manager_vector) {
		std::vector<Unit*>& manager_unit_vector = manager->get_unit_vector();
		unit = find_click_unit(_vec2, manager_unit_vector);
		// 유닛을 찾으면 검색을 중단한다.
		if (unit != nullptr) {
			// 있을때의 처리를 한다.
			R_click_unit_process(unit, _unit_vector);
			return;
		}
	}
	// 없을때의 처리를 한다.
	R_click_not_unit_process(_vec2, _unit_vector);
}

void OrderManager::R_click_unit_process(Unit* _unit, const std::vector<Unit*>& _unit_vector)
{
	// 유닛의 소속팀에 따라 명령이 달라져야함
	// 유닛 행동을 지시하는 클래스가 만들어지면 상세 정의 필요
	attack_unit(_unit, _unit_vector);
}

void OrderManager::R_click_not_unit_process(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector)
{
	CCLOG("pos_x : %f, pos_y : %f", _vec2.x, _vec2.y);
	move_unit(_vec2, _unit_vector);
}

Unit * OrderManager::find_click_unit(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		// 유닛의 바운딩 박스 저장
		cocos2d::Rect rect = unit->getBoundingBox();
		// 바운딩 박스와 위치가 겹치는지 확인
		if (rect.containsPoint(_vec2)) {
			// 겹친 유닛 반환
			return unit;
		}
	}
	// 겹친 유닛이 없으면 nullptr 반환
	return nullptr;
}

// 유닛을 공격한다.
// 유닛 행동 함수에 따라 내용이 변경될수 있다.
void OrderManager::attack_unit(Unit* const _unit, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		unit->attack_unit(_unit);
	}
}

// 유닛을 이동한다.
// 유닛 행동 함수에 따라 내용이 변경될수 있다.
void OrderManager::move_unit(const cocos2d::Vec2& _vec2, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		unit->move_unit(_vec2);
	}
}