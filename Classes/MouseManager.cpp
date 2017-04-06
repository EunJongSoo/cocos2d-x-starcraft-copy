#include "MouseManager.h"
#include "MouseInfo.h"
#include "Point.h"
#include "Header.h"

using namespace cocos2d;

MouseManager::MouseManager() : 
	order(false), 
	mouse_info(nullptr) 
{}

MouseManager::~MouseManager() {}

bool MouseManager::init() {
	if (!Node::init())
		return false;

	// 마우스 이벤트 등록
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(MouseManager::on_mouse_down, this);
	listener->onMouseMove = CC_CALLBACK_1(MouseManager::on_mouse_move, this);
	listener->onMouseUp = CC_CALLBACK_1(MouseManager::on_mouse_up, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// 화면 크기 멤버 변수 저장
	win_size = Director::getInstance()->getWinSize();

	return true;
}

// 마우스 정보 초기화
// 해당 함수가 호출 될때마다 멤버 변수의 동적할당을 해제하고
// 다시 명령이 내려질때마다 동적할당을 한다면 횟수가 너무 빈번하다
// 어떻게 하는게 좋을지 질문할것
void MouseManager::init_mouse_info() {
	order = false;
	// 멤버 변수 동적할당 안전해제
	SAFE_DELETE(mouse_info);
}

// 마우스 클릭 되었을때 이벤트
void MouseManager::on_mouse_down(Event * _event) {
	// 마우스 이벤트 인지 확인
	if (_event->getType() != Event::Type::MOUSE) {
		return;
	}

	// 이벤트를 이벤트 마우스로 형변환
	auto mouse = static_cast<EventMouse*>(_event);
	
	// 마우의 좌표 확인
	Vec2 vec2 = mouse->getLocation();

	// 마우스의 버튼 확인
	switch (mouse->getMouseButton())
	{
		// 마우스 버튼이 왼쪽일때
	case MOUSE_BUTTON_LEFT:
		set_mouse_order(MouseInfo::mouse_state::L_down, vec2, set_pos::start);
		break;
		// 마우스 버튼이 오른쪽일때
	case MOUSE_BUTTON_RIGHT:
		set_mouse_order(MouseInfo::mouse_state::R_down, vec2, set_pos::start);
		break;
	}
}

// 마우스가 움직일때의 이벤트
void MouseManager::on_mouse_move(Event * _event) {
	if (_event->getType() != Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	Vec2 vec2 = mouse->getLocation();

	// 마우스 정보가 있는지 확인한다.
	if (is_mouse_info()) {
		return;
	}

	// 마우스의 현재 상태를 확인한다.
	switch (mouse_info->get_mouse_state()) {
		// 마우스의 상태가 L_down 일때의 처리를 한다.
	case MouseInfo::mouse_state::L_down: {
		// 마우스 첫 클릭 좌표와 현재 좌표의 거리가 차이가 지정한 수치를 넘었는지 확인한다.
		if (mouse_distance_check(vec2) > mouse_drag_distance) {
			// 마우스 상태를 L_dragging로 변경하고 현재 좌표를 마지막 위치로 설정한다.
			set_mouse_order(MouseInfo::mouse_state::L_dragging, vec2, set_pos::end);
		}
		break;
	}
		// 마우스의 상태가 L_dragging 일때의 처리를 한다.		
	case MouseInfo::mouse_state::L_dragging:
		// 마우스 상태를 L_dragging로 변경하고 현재 좌표를 마지막 위치로 설정한다.
		set_mouse_order(MouseInfo::mouse_state::L_dragging, vec2, set_pos::end);
		break;
	}
}

void MouseManager::on_mouse_up(Event * _event) {
	if (_event->getType() != Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	
	// 마우스 정보가 있는지 확인한다.
	if (is_mouse_info()) {
		return;
	}

	// 마우스 버튼을 확인한다.
	switch (mouse->getMouseButton()) {
		// 마우스 왼쪽 버튼일때 처리를 한다.
	case MOUSE_BUTTON_LEFT: {
		// 기존 마우스 상태가 L_down이면 L_up으로 변경한다.
		if (mouse_info->get_mouse_state() == MouseInfo::mouse_state::L_down) {
			set_mouse_order(MouseInfo::mouse_state::L_up);
		}
		// 기존 마우스 상태가 L_dragging이면 L_drag로 변경한다.
		else if (mouse_info->get_mouse_state() == MouseInfo::mouse_state::L_dragging) {
			set_mouse_order(MouseInfo::mouse_state::L_drag);
		}
		break;
	}
	}
}

// 마우스 좌표를 보정한다.
void MouseManager::correction_mouse_location_y(eun::Point& _point) {
	// 마우스 Y좌표 반전되어 있어서 화면의 세로 크기를 빼서 보정한다.
	_point.y = win_size.height - _point.y;
}

// 마우스 거리를 확인한다.
float MouseManager::mouse_distance_check(const Vec2& _vec2) {
	// 마우스 처음 좌표를 저장한다.
	eun::Point point = mouse_info->get_start_pos();
	// 처음 좌표와 현재 좌표의 차이를 반환한다.
	return _vec2.distance(Vec2(point.x, point.y));
}

// 마우스 명령을 설정한다.
void MouseManager::set_mouse_order(const int _state) {
	// 마우스 정보가 있는지 확인한다.
	if (!is_mouse_info()) {
		// 정보가 없으면 동적할당
		mouse_info = new MouseInfo();
	}
	
	// 마우스의 상태값을 설정한다.
	mouse_info->set_mouse_state(_state);
	// 마우스 명령여부를 설정한다.
	order = true;
}

// 마우스 명령을 설정한다.
void MouseManager::set_mouse_order(const int _state, const Vec2& _vec2, set_pos _start_end) {
	// 마우스 좌표를 Point 개체에 저장한다.
	eun::Point point(_vec2.x, _vec2.y);

	// 마우스 명령을 설정한다.
	this->set_mouse_order(_state);
	// 마우스 좌표를 보정한다.
	correction_mouse_location_y(point);

	// 마우스 좌표가 어딘지 확인한다.
	switch (_start_end)
	{
		// 처음 좌표에 설정한다.
	case MouseManager::start:	mouse_info->set_start_pos(point);	break;
		// 마지막 좌표에 설정한다.
	case MouseManager::end:		mouse_info->set_end_pos(point);	break;
	}
}

// 마우스 정보가 있는지 확인한다.
bool MouseManager::is_mouse_info()
{
	return (mouse_info != nullptr);
}
