#include "MouseManager.h"

using namespace cocos2d;

MouseManager::MouseManager() : 
	state(MouseInfo::mouse_state::none),
	order(MouseInfo::mouse_state::none),
	start_pos(Vec2::ZERO),
	end_pos(Vec2::ZERO)
{
}

MouseManager::~MouseManager() {
}

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

MouseInfo * MouseManager::get_mouse_info()
{
	MouseInfo* info = nullptr;
	if (order != MouseInfo::mouse_state::none) {
		info = new MouseInfo(state, start_pos, end_pos);
		order = MouseInfo::mouse_state::none;
	}
	/*if (!fast_mouse_info_deque.empty()) {
		info = fast_mouse_info_deque[0];
		fast_mouse_info_deque.pop_front();
	}*/
	return info;
}

MouseInfo * MouseManager::get_normal_mouse_info()
{
	/*MouseInfo* mouse_info = nullptr;
	if (state == MouseInfo::mouse_state::move) {
		mouse_info = new MouseInfo(state, start_pos, end_pos);
	}*/
	MouseInfo* mouse_info = new MouseInfo(MouseInfo::mouse_state::move, start_pos, end_pos);
	return mouse_info;
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
	correction_mouse_location_y(vec2);

	// 마우스의 버튼 확인
	switch (mouse->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT: on_mouse_L_down_process(vec2);	break;
	case MOUSE_BUTTON_RIGHT: on_mouse_R_down_process(vec2);	break;
	}
}

// 마우스가 움직일때의 이벤트
void MouseManager::on_mouse_move(Event * _event) {
	if (_event->getType() != Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	Vec2 vec2 = mouse->getLocation();
	correction_mouse_location_y(vec2);

	// 마우스의 현재 상태를 확인한다.
	switch (state) {
	case MouseInfo::mouse_state::L_dragging:
		// 마우스의 상태가 L_down 일때의 처리를 한다.
	case MouseInfo::mouse_state::L_down: {
		// 마우스 첫 클릭 좌표와 현재 좌표의 거리가 차이가 지정한 수치를 넘었는지 확인한다.
		if (mouse_distance_check(vec2)) {
			// 마우스 상태를 L_dragging로 변경하고 현재 좌표를 마지막 위치로 설정한다.
			on_mouse_L_dragging_process(vec2);
		}
		break;
	}
	default: {
		// 마우스 이동 명령이 일정 숫자 이상 되어야 전달되도록 지연시킴
		// move 명령이 자주 전달되어 다른 명령이 무시당하는 현상 때문에 추가
		on_mouse_move_process(vec2);
	}
	}
}

void MouseManager::on_mouse_up(Event * _event) {
	if (_event->getType() != Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	
	Vec2 vec2 = mouse->getLocation();
	correction_mouse_location_y(vec2);

	// 마우스 버튼을 확인한다.
	switch (mouse->getMouseButton()) {
		// 마우스 왼쪽 버튼일때 처리를 한다.
	case MOUSE_BUTTON_LEFT: {
		// 기존 마우스 상태가 L_down이면 L_up으로 변경한다.
		if (state == MouseInfo::mouse_state::L_down) {
			on_mouse_L_up_process(vec2);
		}
		// 기존 마우스 상태가 L_dragging이면 L_drag로 변경한다.
		else if (state == MouseInfo::mouse_state::L_dragging) {
			on_mouse_L_drag_process(vec2);
		}
		break;
	}
	}
}

// 마우스 좌표를 보정한다.
void MouseManager::correction_mouse_location_y(Vec2& _point) {
	// 마우스 Y좌표 반전되어 있어서 화면의 세로 크기를 빼서 보정한다.
	_point.y = win_size.height - _point.y;
}

// 마우스 거리를 확인한다.
bool MouseManager::mouse_distance_check(const Vec2& _vec2) {
	// 처음 좌표와 현재 좌표의 차이를 반환한다.
	return _vec2.distance(start_pos) > mouse_drag_distance;
}

void MouseManager::set_value(MouseInfo::mouse_state _state, const Vec2& _start_pos, const Vec2 & _end_pos) {
	state = _state;
	order = _state;
	start_pos = _start_pos;
	end_pos = _end_pos;
}

// 왼클릭 프로세스
void MouseManager::on_mouse_L_down_process(const Vec2& _start_pos)
{
	set_value(MouseInfo::mouse_state::L_down, _start_pos, _start_pos);
	set_mouse_order();
}

// 오른클릭 프로세스
void MouseManager::on_mouse_R_down_process(const Vec2& _start_pos)
{
	set_value(MouseInfo::mouse_state::R_down, _start_pos, _start_pos);
	set_mouse_order();
}

void MouseManager::on_mouse_L_dragging_process(const Vec2 & _end_pos)
{
	// 이전 마지막 점과, 새로운 마지막 점의 거리가 일정 이상 날때
	if (end_pos.distance(_end_pos) > 1.0f) {
		set_value(MouseInfo::mouse_state::L_dragging, start_pos, _end_pos);
		set_mouse_order();
	}
}

void MouseManager::on_mouse_move_process(const Vec2 & _end_pos)
{
	//set_value(MouseInfo::mouse_state::move, start_pos, _end_pos);
	end_pos = _end_pos;
}

void MouseManager::on_mouse_L_up_process(const cocos2d::Vec2 & _end_pos)
{
	set_value(MouseInfo::mouse_state::L_up, start_pos, _end_pos);
	set_mouse_order();
	//set_value(MouseInfo::mouse_state::none, Vec2::ZERO, Vec2::ZERO);
}

void MouseManager::on_mouse_L_drag_process(const cocos2d::Vec2 & _end_pos)
{
	set_value(MouseInfo::mouse_state::L_drag, start_pos, _end_pos);
	set_mouse_order();
	//set_value(MouseInfo::mouse_state::none, Vec2::ZERO, Vec2::ZERO);
}

// 마우스 명령을 설정한다.
void MouseManager::set_mouse_order() {
	/*MouseInfo* mouse_info = new MouseInfo(state, start_pos, end_pos);
	fast_mouse_info_deque.push_back(mouse_info);*/
}