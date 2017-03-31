#ifndef MOUSE_MANAGER_H_
#define MOUSE_MANAGER_H_

#include "cocos2d.h"

class MouseManager : public cocos2d::Node {
public:
	enum class mouse_state {
		none, L_down, L_drag, L_double, L_up, R_down, R_up
	};
public:
	MouseManager();
	virtual ~MouseManager();
	virtual bool init() {
		if (!cocos2d::Node::init())
			return false;

		auto listener = cocos2d::EventListenerMouse::create();
		listener->onMouseDown = CC_CALLBACK_1(MouseManager::on_mouse_down, this);
		listener->onMouseMove = CC_CALLBACK_1(MouseManager::on_mouse_move, this);
		listener->onMouseUp = CC_CALLBACK_1(MouseManager::on_mouse_up, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		return true;
	}
	CREATE_FUNC(MouseManager);

public:
	mouse_state _mouse_state;


private:
	void on_mouse_down(cocos2d::Event* _event);
	void on_mouse_move(cocos2d::Event* _event);
	void on_mouse_up(cocos2d::Event* _event);

private:
	cocos2d::Vec2 _start_mouse_pos;
	cocos2d::Vec2 _end_mouse_pos;

};

#endif // !KEYBOARD_MANAGER_H_