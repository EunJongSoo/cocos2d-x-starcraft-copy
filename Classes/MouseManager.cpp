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

	// ���콺 �̺�Ʈ ���
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(MouseManager::on_mouse_down, this);
	listener->onMouseMove = CC_CALLBACK_1(MouseManager::on_mouse_move, this);
	listener->onMouseUp = CC_CALLBACK_1(MouseManager::on_mouse_up, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// ȭ�� ũ�� ��� ���� ����
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

// ���콺 Ŭ�� �Ǿ����� �̺�Ʈ
void MouseManager::on_mouse_down(Event * _event) {
	// ���콺 �̺�Ʈ ���� Ȯ��
	if (_event->getType() != Event::Type::MOUSE) {
		return;
	}

	// �̺�Ʈ�� �̺�Ʈ ���콺�� ����ȯ
 	auto mouse = static_cast<EventMouse*>(_event);
	
	// ������ ��ǥ Ȯ��
	Vec2 vec2 = mouse->getLocation();
	correction_mouse_location_y(vec2);

	// ���콺�� ��ư Ȯ��
	switch (mouse->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT: on_mouse_L_down_process(vec2);	break;
	case MOUSE_BUTTON_RIGHT: on_mouse_R_down_process(vec2);	break;
	}
}

// ���콺�� �����϶��� �̺�Ʈ
void MouseManager::on_mouse_move(Event * _event) {
	if (_event->getType() != Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	Vec2 vec2 = mouse->getLocation();
	correction_mouse_location_y(vec2);

	// ���콺�� ���� ���¸� Ȯ���Ѵ�.
	switch (state) {
	case MouseInfo::mouse_state::L_dragging:
		// ���콺�� ���°� L_down �϶��� ó���� �Ѵ�.
	case MouseInfo::mouse_state::L_down: {
		// ���콺 ù Ŭ�� ��ǥ�� ���� ��ǥ�� �Ÿ��� ���̰� ������ ��ġ�� �Ѿ����� Ȯ���Ѵ�.
		if (mouse_distance_check(vec2)) {
			// ���콺 ���¸� L_dragging�� �����ϰ� ���� ��ǥ�� ������ ��ġ�� �����Ѵ�.
			on_mouse_L_dragging_process(vec2);
		}
		break;
	}
	default: {
		// ���콺 �̵� ����� ���� ���� �̻� �Ǿ�� ���޵ǵ��� ������Ŵ
		// move ����� ���� ���޵Ǿ� �ٸ� ����� ���ô��ϴ� ���� ������ �߰�
		on_mouse_move_process(vec2);
	}
	}
}

void MouseManager::on_mouse_up(Event * _event) {
	if (_event->getType() != Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	
	Vec2 vec2 = mouse->getLocation();
	correction_mouse_location_y(vec2);

	// ���콺 ��ư�� Ȯ���Ѵ�.
	switch (mouse->getMouseButton()) {
		// ���콺 ���� ��ư�϶� ó���� �Ѵ�.
	case MOUSE_BUTTON_LEFT: {
		// ���� ���콺 ���°� L_down�̸� L_up���� �����Ѵ�.
		if (state == MouseInfo::mouse_state::L_down) {
			on_mouse_L_up_process(vec2);
		}
		// ���� ���콺 ���°� L_dragging�̸� L_drag�� �����Ѵ�.
		else if (state == MouseInfo::mouse_state::L_dragging) {
			on_mouse_L_drag_process(vec2);
		}
		break;
	}
	}
}

// ���콺 ��ǥ�� �����Ѵ�.
void MouseManager::correction_mouse_location_y(Vec2& _point) {
	// ���콺 Y��ǥ �����Ǿ� �־ ȭ���� ���� ũ�⸦ ���� �����Ѵ�.
	_point.y = win_size.height - _point.y;
}

// ���콺 �Ÿ��� Ȯ���Ѵ�.
bool MouseManager::mouse_distance_check(const Vec2& _vec2) {
	// ó�� ��ǥ�� ���� ��ǥ�� ���̸� ��ȯ�Ѵ�.
	return _vec2.distance(start_pos) > mouse_drag_distance;
}

void MouseManager::set_value(MouseInfo::mouse_state _state, const Vec2& _start_pos, const Vec2 & _end_pos) {
	state = _state;
	order = _state;
	start_pos = _start_pos;
	end_pos = _end_pos;
}

// ��Ŭ�� ���μ���
void MouseManager::on_mouse_L_down_process(const Vec2& _start_pos)
{
	set_value(MouseInfo::mouse_state::L_down, _start_pos, _start_pos);
	set_mouse_order();
}

// ����Ŭ�� ���μ���
void MouseManager::on_mouse_R_down_process(const Vec2& _start_pos)
{
	set_value(MouseInfo::mouse_state::R_down, _start_pos, _start_pos);
	set_mouse_order();
}

void MouseManager::on_mouse_L_dragging_process(const Vec2 & _end_pos)
{
	// ���� ������ ����, ���ο� ������ ���� �Ÿ��� ���� �̻� ����
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

// ���콺 ����� �����Ѵ�.
void MouseManager::set_mouse_order() {
	/*MouseInfo* mouse_info = new MouseInfo(state, start_pos, end_pos);
	fast_mouse_info_deque.push_back(mouse_info);*/
}