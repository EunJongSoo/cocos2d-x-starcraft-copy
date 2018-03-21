/****************************
수정일 : 2018-03-21
작성자 : 은종수
파일명 : MouseManager.cpp
****************************/

#include "MouseManager.h"

using namespace cocos2d;
/*
생성자에서는 변수 초기화만 한다.
*/
MouseManager::MouseManager() : 
	state(MouseInfo::Mouse_state::none),
	order(MouseInfo::Mouse_state::none),
	start_pos(Vec2::ZERO),
	end_pos(Vec2::ZERO)
{
}

MouseManager::~MouseManager() {
}

/*
MouseManager를 초기화할때 코코스의 이벤트 리스너를 등록한다.
저렇게 등록해두면 해당 이벤트가 발생할때 
저 함수들이 호출되며 마우스 이벤트가 매개변수로 넘어간다.
*/
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
	/*
	if문에서 마우스 오더가 없다가 아니면 이니까 있으면이다.
	입력이 있으면 MouseInfo를 만들고, 없으면 만들지 않는다.

	그리고 만들고 나면 그 오더를 전달했기 때문에
	오더가 없다로 상태를 바꾼다.

	그리고 있었으면 새로 동적할당한 정보를, 없었으면 nullptr을 반환한다.

	아래쪽에 주석처리된 부분은 자연스럽게 정보를 전달하려고
	큐에다가 순서대로 쌓았다가 하나씩 빼서 쓴다는 생각으로 했는데
	처리 속도가 느려서 기각된 주석처리 해둔거다.

	정확하게는 모르겠고 큐를 써서 하나씩 내보내면 누락되는 지시가 없어서
	다 처리하려고 하다보니 느려지는거고

	그냥 바로바로 내보내면 빠르게 움직이는 몇개가 생략되는거 같다.
	그런데 그정도는 사람이 인식을 못하니 빠르게 잘된다 정도의 느낌이다.

	추측이다.
	*/
	MouseInfo* info = new MouseInfo(MouseInfo::Mouse_state::none, start_pos, end_pos);;
	if (order != MouseInfo::Mouse_state::none) {
		info->set_mouse_state(state);
		order = MouseInfo::Mouse_state::none;
	}
	/*if (!fast_mouse_info_deque.empty()) {
		info = fast_mouse_info_deque[0];
		fast_mouse_info_deque.pop_front();
	}*/
	return info;
}

/*
마우스 클릭이 있을때의 이벤트를 처리한다.
들어온 이벤트가 마우스 이벤트인지 확인하고 아니면 리턴해준다.

코코스에서 넘어온 좌표값의 y를 보정해주고
버튼을 확인하여 각 버튼의 처리를 해주는 함수를 호출한다.
*/
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

/*
처음은 위와 똑같고 코코스에서 넘어온 좌표값의 y를 보정해준다.
그리고 상태가 dragging 또는 down이면 on_mouse_L_dragging_process를 호출하고

아니면 마우스 마지막 포지션을 지금 받은 포지션으로 바꿔준다.

on_mouse_move에서 나가는 마우스 포지션은 화면을 이동할때 사용하거나
드래그된 영역을 표시할때 사용한다.

마우스가 눌러진걸 확인하는 것과 누르면서 이동하는걸 감지할때는 동일한 동작이다
*/
// 마우스가 움직일때의 이벤트
void MouseManager::on_mouse_move(Event * _event) {
	if (_event->getType() != Event::Type::MOUSE) return;

	auto mouse = static_cast<EventMouse*>(_event);
	Vec2 vec2 = mouse->getLocation();
	correction_mouse_location_y(vec2);

	// 마우스의 현재 상태를 확인한다.
	switch (state) {
	case MouseInfo::Mouse_state::L_dragging:
		// 마우스의 상태가 L_down 일때의 처리를 한다.
	case MouseInfo::Mouse_state::L_down: {
		// 마우스 첫 클릭 좌표와 현재 좌표의 거리 차이가 지정한 수치를 넘었는지 확인한다.
		if (check_mouse_distance(vec2)) {
			// 마우스 상태를 L_dragging로 변경하고 현재 좌표를 마지막 위치로 설정한다.
			on_mouse_L_dragging_process(vec2);
			return;
		}
		break;
	}
	}
	end_pos = vec2;
}

/*
좌표값 보정 해주는 부분까지 동일하다.

오른클릭은 누른 순간 명령이 넘어가므로 별도의 명령이 없다. 
왼클릭은 그냥 원클릭과 드래그를 했을때를 구분해서 각각의 처리를 수행한다.
*/
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
		if (state == MouseInfo::Mouse_state::L_down) {
			on_mouse_L_up_process(vec2);
		}
		// 기존 마우스 상태가 L_dragging이면 L_drag로 변경한다.
		else if (state == MouseInfo::Mouse_state::L_dragging) {
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

/*
상수로 만든 0.5의 거리를 비교한다. 임의로 정한숫자다.
*/
// 마우스 거리를 확인한다.
bool MouseManager::check_mouse_distance(const Vec2& _vec2) {
	// 처음 좌표와 현재 좌표의 차이를 반환한다.
	return _vec2.distance(start_pos) > mouse_drag_distance;
}

/*
각 명령이 들어갈때마다 대입하는 값만 다르고
다 똑같이 대입하고 있어서 함수로 묶었다.
*/
void MouseManager::set_value(MouseInfo::Mouse_state _state, const Vec2& _start_pos, const Vec2 & _end_pos) {
	state = _state;
	order = _state;
	start_pos = _start_pos;
	end_pos = _end_pos;
}


/*
무슨 일을 하는지 표현하기 위해서 함수로 만들었지 상태값만 바뀌고 비슷한 부분이 많다.
dragging만 거리를 확인하는 부분이 추가되어 있다.
*/
// 왼클릭 프로세스
void MouseManager::on_mouse_L_down_process(const Vec2& _start_pos)
{
	set_value(MouseInfo::Mouse_state::L_down, _start_pos, _start_pos);
}

// 오른클릭 프로세스
void MouseManager::on_mouse_R_down_process(const Vec2& _start_pos)
{
	set_value(MouseInfo::Mouse_state::R_down, _start_pos, _start_pos);
}

void MouseManager::on_mouse_L_dragging_process(const Vec2 & _end_pos)
{
	// 이전 마지막 점과, 새로운 마지막 점의 거리가 일정 이상 날때
	if (end_pos.distance(_end_pos) > 1.0f) {
		set_value(MouseInfo::Mouse_state::L_dragging, start_pos, _end_pos);
	}
}

void MouseManager::on_mouse_L_up_process(const cocos2d::Vec2 & _end_pos)
{
	set_value(MouseInfo::Mouse_state::L_up, start_pos, _end_pos);
}

void MouseManager::on_mouse_L_drag_process(const cocos2d::Vec2 & _end_pos)
{
	set_value(MouseInfo::Mouse_state::L_drag, start_pos, _end_pos);
}