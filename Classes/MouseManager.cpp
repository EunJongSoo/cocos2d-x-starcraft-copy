#include "MouseManager.h"

using namespace cocos2d;

MouseManager::MouseManager() : _is_order(false) {
}

MouseManager::~MouseManager() {
}

bool MouseManager::init() {
	if (!Node::init())
		return false;

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(MouseManager::on_mouse_down, this);
	listener->onMouseMove = CC_CALLBACK_1(MouseManager::on_mouse_move, this);
	listener->onMouseUp = CC_CALLBACK_1(MouseManager::on_mouse_up, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	_win_size = Director::getInstance()->getWinSize();

	return true;
}

void MouseManager::init_mouse_order() {
	_is_order = false;
}

void MouseManager::on_mouse_down(Event * _event) {
	if (_event->getType() != cocos2d::Event::Type::MOUSE) return;

	auto mouse = static_cast<EventMouse*>(_event);
	
	switch (mouse->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT:
		set_mouse_order(mouse_state::L_down, mouse->getLocation());
		break;
	case MOUSE_BUTTON_RIGHT:
		set_mouse_order(mouse_state::R_down, mouse->getLocation());
		break;
	default:	break;
	}
}

void MouseManager::on_mouse_move(Event * _event) {
	if (_event->getType() != cocos2d::Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	
	switch (_mouse_order.mouse_state) {
	case mouse_state::L_down:
		if (mouse_distance_check(mouse->getLocation()) > mouse_drag_distance)
			set_mouse_order(mouse_state::L_drag);
		break;
	case mouse_state::L_drag:
		_mouse_order.end_mouse_pos = mouse_location_y(mouse->getLocation());
		break;
	default:
		break;
	}
}

void MouseManager::on_mouse_up(Event * _event) {
	if (_event->getType() != cocos2d::Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	
	switch (mouse->getMouseButton()) {
	case MOUSE_BUTTON_LEFT: {
		_mouse_order.mouse_state = mouse_state::L_up;
		break;
	}
	}
}

Vec2 MouseManager::mouse_location_y(const Vec2& _location) {
	Vec2 location = _location;
	location.y = _win_size.height - location.y;
	return location;
}

float MouseManager::mouse_distance_check(const Vec2& _location) {
	return _mouse_order.start_mouse_pos.distance(_location);
}

void MouseManager::set_mouse_order(mouse_state _state) {
	_is_order = true;
	_mouse_order.mouse_state = _state;
}

void MouseManager::set_mouse_order(mouse_state _state, const Vec2& _pos) {
	this->set_mouse_order(_state);
	_mouse_order.start_mouse_pos = mouse_location_y(_pos);
}
