#include "MouseManager.h"

using namespace cocos2d;

MouseManager::MouseManager() : _mouse_state(mouse_state::none) {
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

	return true;
}

void MouseManager::on_mouse_down(Event * _event) {
	if (_event->getType() != cocos2d::Event::Type::MOUSE) return;

	auto mouse = static_cast<EventMouse*>(_event);
	
	switch (mouse->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT:		_mouse_state = mouse_state::L_down; break;
	case MOUSE_BUTTON_RIGHT:	_mouse_state = mouse_state::R_down;	break;
	default:	break;
	}
}

void MouseManager::on_mouse_move(Event * _event) {
	if (_event->getType() != cocos2d::Event::Type::MOUSE) return;
	
	auto mouse = static_cast<EventMouse*>(_event);
	
	switch (_mouse_state) {
	case mouse_state::L_down:
		_mouse_state = mouse_state::L_drag;
		_start_mouse_pos = mouse->getLocation();
		break;
	case mouse_state::L_drag:
		_end_mouse_pos = mouse->getLocation();
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
		_mouse_state = mouse_state::L_up;
		break;
	}
	}
}