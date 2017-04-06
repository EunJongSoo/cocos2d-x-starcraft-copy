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

// ���콺 ���� �ʱ�ȭ
// �ش� �Լ��� ȣ�� �ɶ����� ��� ������ �����Ҵ��� �����ϰ�
// �ٽ� ����� ������������ �����Ҵ��� �Ѵٸ� Ƚ���� �ʹ� ����ϴ�
// ��� �ϴ°� ������ �����Ұ�
void MouseManager::init_mouse_info() {
	order = false;
	// ��� ���� �����Ҵ� ��������
	SAFE_DELETE(mouse_info);
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

	// ���콺�� ��ư Ȯ��
	switch (mouse->getMouseButton())
	{
		// ���콺 ��ư�� �����϶�
	case MOUSE_BUTTON_LEFT:
		set_mouse_order(MouseInfo::mouse_state::L_down, vec2, set_pos::start);
		break;
		// ���콺 ��ư�� �������϶�
	case MOUSE_BUTTON_RIGHT:
		set_mouse_order(MouseInfo::mouse_state::R_down, vec2, set_pos::start);
		break;
	}
}

// ���콺�� �����϶��� �̺�Ʈ
void MouseManager::on_mouse_move(Event * _event) {
	if (_event->getType() != Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	Vec2 vec2 = mouse->getLocation();

	// ���콺 ������ �ִ��� Ȯ���Ѵ�.
	if (is_mouse_info()) {
		return;
	}

	// ���콺�� ���� ���¸� Ȯ���Ѵ�.
	switch (mouse_info->get_mouse_state()) {
		// ���콺�� ���°� L_down �϶��� ó���� �Ѵ�.
	case MouseInfo::mouse_state::L_down: {
		// ���콺 ù Ŭ�� ��ǥ�� ���� ��ǥ�� �Ÿ��� ���̰� ������ ��ġ�� �Ѿ����� Ȯ���Ѵ�.
		if (mouse_distance_check(vec2) > mouse_drag_distance) {
			// ���콺 ���¸� L_dragging�� �����ϰ� ���� ��ǥ�� ������ ��ġ�� �����Ѵ�.
			set_mouse_order(MouseInfo::mouse_state::L_dragging, vec2, set_pos::end);
		}
		break;
	}
		// ���콺�� ���°� L_dragging �϶��� ó���� �Ѵ�.		
	case MouseInfo::mouse_state::L_dragging:
		// ���콺 ���¸� L_dragging�� �����ϰ� ���� ��ǥ�� ������ ��ġ�� �����Ѵ�.
		set_mouse_order(MouseInfo::mouse_state::L_dragging, vec2, set_pos::end);
		break;
	}
}

void MouseManager::on_mouse_up(Event * _event) {
	if (_event->getType() != Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	
	// ���콺 ������ �ִ��� Ȯ���Ѵ�.
	if (is_mouse_info()) {
		return;
	}

	// ���콺 ��ư�� Ȯ���Ѵ�.
	switch (mouse->getMouseButton()) {
		// ���콺 ���� ��ư�϶� ó���� �Ѵ�.
	case MOUSE_BUTTON_LEFT: {
		// ���� ���콺 ���°� L_down�̸� L_up���� �����Ѵ�.
		if (mouse_info->get_mouse_state() == MouseInfo::mouse_state::L_down) {
			set_mouse_order(MouseInfo::mouse_state::L_up);
		}
		// ���� ���콺 ���°� L_dragging�̸� L_drag�� �����Ѵ�.
		else if (mouse_info->get_mouse_state() == MouseInfo::mouse_state::L_dragging) {
			set_mouse_order(MouseInfo::mouse_state::L_drag);
		}
		break;
	}
	}
}

// ���콺 ��ǥ�� �����Ѵ�.
void MouseManager::correction_mouse_location_y(eun::Point& _point) {
	// ���콺 Y��ǥ �����Ǿ� �־ ȭ���� ���� ũ�⸦ ���� �����Ѵ�.
	_point.y = win_size.height - _point.y;
}

// ���콺 �Ÿ��� Ȯ���Ѵ�.
float MouseManager::mouse_distance_check(const Vec2& _vec2) {
	// ���콺 ó�� ��ǥ�� �����Ѵ�.
	eun::Point point = mouse_info->get_start_pos();
	// ó�� ��ǥ�� ���� ��ǥ�� ���̸� ��ȯ�Ѵ�.
	return _vec2.distance(Vec2(point.x, point.y));
}

// ���콺 ����� �����Ѵ�.
void MouseManager::set_mouse_order(const int _state) {
	// ���콺 ������ �ִ��� Ȯ���Ѵ�.
	if (!is_mouse_info()) {
		// ������ ������ �����Ҵ�
		mouse_info = new MouseInfo();
	}
	
	// ���콺�� ���°��� �����Ѵ�.
	mouse_info->set_mouse_state(_state);
	// ���콺 ��ɿ��θ� �����Ѵ�.
	order = true;
}

// ���콺 ����� �����Ѵ�.
void MouseManager::set_mouse_order(const int _state, const Vec2& _vec2, set_pos _start_end) {
	// ���콺 ��ǥ�� Point ��ü�� �����Ѵ�.
	eun::Point point(_vec2.x, _vec2.y);

	// ���콺 ����� �����Ѵ�.
	this->set_mouse_order(_state);
	// ���콺 ��ǥ�� �����Ѵ�.
	correction_mouse_location_y(point);

	// ���콺 ��ǥ�� ����� Ȯ���Ѵ�.
	switch (_start_end)
	{
		// ó�� ��ǥ�� �����Ѵ�.
	case MouseManager::start:	mouse_info->set_start_pos(point);	break;
		// ������ ��ǥ�� �����Ѵ�.
	case MouseManager::end:		mouse_info->set_end_pos(point);	break;
	}
}

// ���콺 ������ �ִ��� Ȯ���Ѵ�.
bool MouseManager::is_mouse_info()
{
	return (mouse_info != nullptr);
}
