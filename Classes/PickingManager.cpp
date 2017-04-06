#include <vector>
#include "PickingManager.h"
#include "InputInfo.h"
#include "MouseInfo.h"
#include "Unit.h"
#include "PlayerUnitManager.h"
#include "cocos2d.h"

PickingManager::PickingManager() {}
PickingManager::~PickingManager() {}

// input 정보를 확인하여 관련 이벤트를 동작
void PickingManager::picking_unit(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _manager_vector)
{
	// 마우스 명령 확인
	if (_input->get_mouse_order()) {
		MouseInfo* info = _input->get_mouse_info();

		// 마우스 명령 종류에 따라 해당 이벤트를 동작
		switch (info->get_mouse_state())
		{
		case MouseInfo::R_down: {
			run_action_mouse_R_down(info, _manager_vector);
			break;
		}
		case MouseInfo::L_down: {
			
			break;
		}
		case MouseInfo::L_dragging: {
			break;
		}
		case MouseInfo::L_drag: {
			run_action_mouse_L_drag(info, _manager_vector);
			break;
		}
		case MouseInfo::L_double:	break;
		case MouseInfo::L_up: {
			run_action_mouse_L_up(info, _manager_vector);
			break;
		}
		case MouseInfo::R_up:		break;
		}
	}
}

// 마우스 왼클릭 끝날때 이벤트
void PickingManager::run_action_mouse_L_up(MouseInfo * const _info, const std::vector<PlayerUnitManager*>& _manager_vector)
{
	// 유닛이 클릭 되었을때의 처리를 한다.
	for (PlayerUnitManager* manager : _manager_vector) {
		std::vector<Unit*>& unit_vector = manager->get_unit_vector();
		mouse_L_up_process(_info, unit_vector);
	}
}

// 마우스 왼클릭 드래그 끝날때 이벤트
void PickingManager::run_action_mouse_L_drag(MouseInfo * const _info, const std::vector<PlayerUnitManager*>& _manager_vector)
{
	// 모든 선택된 유닛을 취소한다.
	for (PlayerUnitManager* manager : _manager_vector) {
		std::vector<Unit*>& unit_vector = manager->get_unit_vector();
		mouse_L_drag_process(_info, unit_vector);
	}
}

// 마우스 오른클릭 시작할때 이벤트
void PickingManager::run_action_mouse_R_down(MouseInfo * const _info, const std::vector<PlayerUnitManager*>& _manager_vector)
{
	for (PlayerUnitManager* manager : _manager_vector) {
		std::vector<Unit*>& unit_vector = manager->get_unit_vector();
		mouse_R_down_process(_info, unit_vector, _manager_vector);
	}
}

void PickingManager::mouse_L_up_process(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector)
{
	// 유닛을 선택을 취소한다.
	select_unit(_unit_vector, false);

	// 클릭된 유닛을 찾는다.
	Unit* unit = find_click_unit(_info, _unit_vector);

	// 선택된 유닛이 있는지 확인한다.
	if (is_unit(unit)) {
		// 유닛을 선택한다.
		select_unit(unit, true);
	}
}

void PickingManager::mouse_L_drag_process(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector)
{
	// 유닛을 선택을 취소한다.
	select_unit(_unit_vector, false);
	// 드래그한 유닛을 찾는다.
	std::vector<Unit*> unit_vector = find_drag_unit(_info, _unit_vector);
	if (is_unit(unit_vector)) {
		select_unit(unit_vector, true);
	}
}

void PickingManager::mouse_R_down_process(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector, const std::vector<PlayerUnitManager*>& _manager_vector)
{
	// 선택된 유닛을 찾는다.
	std::vector<Unit*> select_unit_vector = find_select_unit(_unit_vector);

	// 선택된 유닛이 있는지 확인한다.
	if (!is_unit(select_unit_vector)) {
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
	std::vector<Unit*> manager_unit_vector;
	for (PlayerUnitManager* manager : _manager_vector) {
		manager_unit_vector = manager->get_unit_vector();
		unit = find_click_unit(_info, manager_unit_vector);
		// 유닛을 찾으면 검색을 중단한다.
		if (unit != nullptr) {
			break;
		}
	}
	// 유닛이 있는지 확인한다.
	if (is_unit(unit))
	{
		// 있을때의 처리를 한다.
		R_click_unit_process(unit, select_unit_vector);
	}
	else
	{
		// 없을때의 처리를 한다.
		R_click_not_unit_process(_info, select_unit_vector);
	}
}

void PickingManager::R_click_unit_process(Unit* _unit, const std::vector<Unit*>& _unit_vector)
{
	// 유닛의 소속팀에 따라 명령이 달라져야함
	// 유닛 행동을 지시하는 클래스가 만들어지면 상세 정의 필요
	attack_unit(_unit, _unit_vector);
}

void PickingManager::R_click_not_unit_process(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector)
{
	move_unit(_info->get_start_pos(), _unit_vector);
}

// 선택한 유닛의 bool 상태값 변경
void PickingManager::select_unit(Unit* const _unit, bool _b)
{
	_unit->set_select_unit(_b);
}

// 선택한 유닛들의 bool 상태값 변경
void PickingManager::select_unit(const std::vector<Unit*>& _unit_vector, bool _b)
{
	// 전체 유닛대상으로 검색
	for (Unit* unit : _unit_vector) {
		// 유닛의 bool 값 변경
		unit->set_select_unit(_b);
	}
}

// 클릭한 유닛을 찾는다.
Unit * PickingManager::find_click_unit(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector)
{
	// 위치 정보 임시저장
	eun::Point point = _info->get_start_pos();
	for (Unit* unit : _unit_vector) {
		// 유닛의 바운딩 박스 저장
		cocos2d::Rect rect = unit->getBoundingBox();
		// 바운딩 박스와 위치가 겹치는지 확인
		if (rect.containsPoint(cocos2d::Vec2(point.x, point.y))) {
			// 겹친 유닛 반환
			return unit;
		}
	}
	// 겹친 유닛이 없으면 nullptr 반환
	return nullptr;
}

// 드래그한 유닛을 찾는다.
std::vector<Unit*> PickingManager::find_drag_unit(MouseInfo * const _info, const std::vector<Unit*>& _unit_vector)
{
	std::vector<Unit*> select_unit_vector;

	// 마우스 클릭한 첫 포인트 임시 저장
	eun::Point start_point = _info->get_start_pos();
	// 마우스 클릭땐 마지막 포인트 임시 저장
	eun::Point end_point = _info->get_end_pos();
	
	// 마우스 클릭한 두 점으로 생긴 사각형의 왼쪽 아래값을 찾는다.
	// cocos2d-x의 좌표계는 왼쪽 아래가 0, 0
	eun::Point min_point = start_point.min_point(end_point);
	
	// 드래그한 크기를 계산한다.
	// 첫 포인트에서 마지막 포인트를 빼고 절대값으로 변경
	float width = fabsf(start_point.x - end_point.x);
	float height = fabsf(start_point.y - end_point.y);

	// 왼쪽 아래 점부터 가로 세로 크기를 사용해서 Rect 변수를 만든다.
	cocos2d::Rect drag_rect = cocos2d::Rect(min_point.x, min_point.y, width, height);

	for (Unit* unit : _unit_vector) {
		cocos2d::Rect rect = unit->getBoundingBox();
		// 유닛의 바운딩 박스와 드래그로 만든 박스가 겹치는지 검사
		if (rect.intersectsRect(drag_rect)) {
			// 저장한 유닛이 12개가 되면 검색을 중지한다.
			if (select_unit_vector.size() == 12) {
				break;
			}
			// 겹친 유닛을 vector에 저장
			select_unit_vector.push_back(unit);
		}
	}
	return select_unit_vector;
}

// 현재 선택된 유닛을 찾는다.
std::vector<Unit*> PickingManager::find_select_unit(const std::vector<Unit*>& _unit_vector)
{
	// 선택된 유닛을 저장할 벡터
	std::vector<Unit*> select_unit_vector;
	for (Unit* unit : _unit_vector) {
		// 유닛이 선택되었는지 확인
		if (unit->is_select()) {
			// 선택된 유닛을 저장
			select_unit_vector.push_back(unit);
		}
	}
	// 반환시 복사되어 반환
	return select_unit_vector;
}

// 유닛을 공격한다.
// 유닛 행동 함수에 따라 내용이 변경될수 있다.
void PickingManager::attack_unit(Unit* const _unit, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		unit->attack_unit(_unit);
	}
}

// 유닛을 이동한다.
// 유닛 행동 함수에 따라 내용이 변경될수 있다.
void PickingManager::move_unit(eun::Point _point, const std::vector<Unit*>& _unit_vector)
{
	for (Unit* unit : _unit_vector) {
		unit->move_unit(_point);
	}
}

// 유닛이 있는지 확인한다.
inline bool PickingManager::is_unit(Unit * _unit)
{
	return (_unit != nullptr); 
}

// 유닛이 있는지 확인한다.
inline bool PickingManager::is_unit(const std::vector<Unit*>& _unit_vector)
{
	return (_unit_vector.size() > 0);
}
