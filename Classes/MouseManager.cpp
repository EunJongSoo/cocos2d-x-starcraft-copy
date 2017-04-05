#include "MouseManager.h"
#include "MouseInfo.h"

using namespace cocos2d;

MouseManager::MouseManager() : order(false), mouse_info(nullptr) {
	mouse_info = new MouseInfo();
}

MouseManager::~MouseManager() {
	if (mouse_info != nullptr) {
		delete mouse_info;
		mouse_info = nullptr;
	}
}

bool MouseManager::init() {
	if (!Node::init())
		return false;

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(MouseManager::on_mouse_down, this);
	listener->onMouseMove = CC_CALLBACK_1(MouseManager::on_mouse_move, this);
	listener->onMouseUp = CC_CALLBACK_1(MouseManager::on_mouse_up, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	win_size = Director::getInstance()->getWinSize();

	return true;
}

void MouseManager::init_mouse_init() {
	order = false;
}

void MouseManager::on_mouse_down(Event * _event) {
	if (_event->getType() != cocos2d::Event::Type::MOUSE) return;

	auto mouse = static_cast<EventMouse*>(_event);
	
	switch (mouse->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT:
		set_mouse_order(MouseInfo::mouse_state::L_down, mouse->getLocation(), set_pos::start);
		break;
	case MOUSE_BUTTON_RIGHT:
		set_mouse_order(MouseInfo::mouse_state::R_down, mouse->getLocation(), set_pos::start);
		break;
	}
}

void MouseManager::on_mouse_move(Event * _event) {
	if (_event->getType() != cocos2d::Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	
	switch (mouse_info->get_mouse_state()) {
	case MouseInfo::mouse_state::L_down: {
		if (mouse_distance_check(mouse->getLocation()) > mouse_drag_distance) {
			set_mouse_order(MouseInfo::mouse_state::L_dragging, mouse->getLocation(), set_pos::end);
		}
		break;
	}
	case MouseInfo::mouse_state::L_dragging:
		set_mouse_order(MouseInfo::mouse_state::L_dragging, mouse->getLocation(), set_pos::end);
		break;
	}
}

void MouseManager::on_mouse_up(Event * _event) {
	if (_event->getType() != cocos2d::Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	
	switch (mouse->getMouseButton()) {
	case MOUSE_BUTTON_LEFT: {
		if (mouse_info->get_mouse_state() == MouseInfo::mouse_state::L_down) {
			set_mouse_order(MouseInfo::mouse_state::L_up);
		}
		else if (mouse_info->get_mouse_state() == MouseInfo::mouse_state::L_dragging) {
			set_mouse_order(MouseInfo::mouse_state::L_drag);
		}
		break;
	}
	}
}

void MouseManager::correction_mouse_location_y(Vec2& _location) {
	_location.y = win_size.height - _location.y;
}

float MouseManager::mouse_distance_check(const Vec2& _location) {
	float x = mouse_info->get_start_pos_x();
	float y = mouse_info->get_start_pos_y();
	return _location.distance(Vec2(x, y));
}

void MouseManager::set_mouse_order(const int _state) {
	mouse_info->set_mouse_state(_state);
	order = true;
}

void MouseManager::set_mouse_order(const int _state, Vec2& _pos, set_pos _start_end) {
	this->set_mouse_order(_state);
	correction_mouse_location_y(_pos);
	switch (_start_end)
	{
	case MouseManager::start:	mouse_info->set_start_pos(_pos.x, _pos.y);	break;
	case MouseManager::end:		mouse_info->set_end_pos(_pos.x, _pos.y);	break;
	}
}
