/****************************
������ : 2018-03-21
�ۼ��� : ������
���ϸ� : MouseManager.cpp
****************************/

#include "MouseManager.h"

using namespace cocos2d;
/*
�����ڿ����� ���� �ʱ�ȭ�� �Ѵ�.
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
MouseManager�� �ʱ�ȭ�Ҷ� ���ڽ��� �̺�Ʈ �����ʸ� ����Ѵ�.
������ ����صθ� �ش� �̺�Ʈ�� �߻��Ҷ� 
�� �Լ����� ȣ��Ǹ� ���콺 �̺�Ʈ�� �Ű������� �Ѿ��.
*/
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
	/*
	if������ ���콺 ������ ���ٰ� �ƴϸ� �̴ϱ� �������̴�.
	�Է��� ������ MouseInfo�� �����, ������ ������ �ʴ´�.

	�׸��� ����� ���� �� ������ �����߱� ������
	������ ���ٷ� ���¸� �ٲ۴�.

	�׸��� �־����� ���� �����Ҵ��� ������, �������� nullptr�� ��ȯ�Ѵ�.

	�Ʒ��ʿ� �ּ�ó���� �κ��� �ڿ������� ������ �����Ϸ���
	ť���ٰ� ������� �׾Ҵٰ� �ϳ��� ���� ���ٴ� �������� �ߴµ�
	ó�� �ӵ��� ������ �Ⱒ�� �ּ�ó�� �صаŴ�.

	��Ȯ�ϰԴ� �𸣰ڰ� ť�� �Ἥ �ϳ��� �������� �����Ǵ� ���ð� ���
	�� ó���Ϸ��� �ϴٺ��� �������°Ű�

	�׳� �ٷιٷ� �������� ������ �����̴� ��� �����Ǵ°� ����.
	�׷��� �������� ����� �ν��� ���ϴ� ������ �ߵȴ� ������ �����̴�.

	�����̴�.
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
���콺 Ŭ���� �������� �̺�Ʈ�� ó���Ѵ�.
���� �̺�Ʈ�� ���콺 �̺�Ʈ���� Ȯ���ϰ� �ƴϸ� �������ش�.

���ڽ����� �Ѿ�� ��ǥ���� y�� �������ְ�
��ư�� Ȯ���Ͽ� �� ��ư�� ó���� ���ִ� �Լ��� ȣ���Ѵ�.
*/
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

/*
ó���� ���� �Ȱ��� ���ڽ����� �Ѿ�� ��ǥ���� y�� �������ش�.
�׸��� ���°� dragging �Ǵ� down�̸� on_mouse_L_dragging_process�� ȣ���ϰ�

�ƴϸ� ���콺 ������ �������� ���� ���� ���������� �ٲ��ش�.

on_mouse_move���� ������ ���콺 �������� ȭ���� �̵��Ҷ� ����ϰų�
�巡�׵� ������ ǥ���Ҷ� ����Ѵ�.

���콺�� �������� Ȯ���ϴ� �Ͱ� �����鼭 �̵��ϴ°� �����Ҷ��� ������ �����̴�
*/
// ���콺�� �����϶��� �̺�Ʈ
void MouseManager::on_mouse_move(Event * _event) {
	if (_event->getType() != Event::Type::MOUSE) return;

	auto mouse = static_cast<EventMouse*>(_event);
	Vec2 vec2 = mouse->getLocation();
	correction_mouse_location_y(vec2);

	// ���콺�� ���� ���¸� Ȯ���Ѵ�.
	switch (state) {
	case MouseInfo::Mouse_state::L_dragging:
		// ���콺�� ���°� L_down �϶��� ó���� �Ѵ�.
	case MouseInfo::Mouse_state::L_down: {
		// ���콺 ù Ŭ�� ��ǥ�� ���� ��ǥ�� �Ÿ� ���̰� ������ ��ġ�� �Ѿ����� Ȯ���Ѵ�.
		if (check_mouse_distance(vec2)) {
			// ���콺 ���¸� L_dragging�� �����ϰ� ���� ��ǥ�� ������ ��ġ�� �����Ѵ�.
			on_mouse_L_dragging_process(vec2);
			return;
		}
		break;
	}
	}
	end_pos = vec2;
}

/*
��ǥ�� ���� ���ִ� �κб��� �����ϴ�.

����Ŭ���� ���� ���� ����� �Ѿ�Ƿ� ������ ����� ����. 
��Ŭ���� �׳� ��Ŭ���� �巡�׸� �������� �����ؼ� ������ ó���� �����Ѵ�.
*/
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
		if (state == MouseInfo::Mouse_state::L_down) {
			on_mouse_L_up_process(vec2);
		}
		// ���� ���콺 ���°� L_dragging�̸� L_drag�� �����Ѵ�.
		else if (state == MouseInfo::Mouse_state::L_dragging) {
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

/*
����� ���� 0.5�� �Ÿ��� ���Ѵ�. ���Ƿ� ���Ѽ��ڴ�.
*/
// ���콺 �Ÿ��� Ȯ���Ѵ�.
bool MouseManager::check_mouse_distance(const Vec2& _vec2) {
	// ó�� ��ǥ�� ���� ��ǥ�� ���̸� ��ȯ�Ѵ�.
	return _vec2.distance(start_pos) > mouse_drag_distance;
}

/*
�� ����� �������� �����ϴ� ���� �ٸ���
�� �Ȱ��� �����ϰ� �־ �Լ��� ������.
*/
void MouseManager::set_value(MouseInfo::Mouse_state _state, const Vec2& _start_pos, const Vec2 & _end_pos) {
	state = _state;
	order = _state;
	start_pos = _start_pos;
	end_pos = _end_pos;
}


/*
���� ���� �ϴ��� ǥ���ϱ� ���ؼ� �Լ��� ������� ���°��� �ٲ�� ����� �κ��� ����.
dragging�� �Ÿ��� Ȯ���ϴ� �κ��� �߰��Ǿ� �ִ�.
*/
// ��Ŭ�� ���μ���
void MouseManager::on_mouse_L_down_process(const Vec2& _start_pos)
{
	set_value(MouseInfo::Mouse_state::L_down, _start_pos, _start_pos);
}

// ����Ŭ�� ���μ���
void MouseManager::on_mouse_R_down_process(const Vec2& _start_pos)
{
	set_value(MouseInfo::Mouse_state::R_down, _start_pos, _start_pos);
}

void MouseManager::on_mouse_L_dragging_process(const Vec2 & _end_pos)
{
	// ���� ������ ����, ���ο� ������ ���� �Ÿ��� ���� �̻� ����
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