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
	virtual bool init();
	CREATE_FUNC(MouseManager);

public:
	mouse_state _mouse_state;

private:
	void on_mouse_down(cocos2d::Event* _event);
	void on_mouse_move(cocos2d::Event* _event);
	void on_mouse_up(cocos2d::Event* _event);
	cocos2d::Vec2 mouse_location_y(const cocos2d::Vec2& _location);
	float mouse_distance_check(const cocos2d::Vec2& _location);

private:
	cocos2d::Vec2 _start_mouse_pos;
	cocos2d::Vec2 _end_mouse_pos;
	cocos2d::Size _win_size;

	const float mouse_drag_distance = 0.5f;
};

#endif // !KEYBOARD_MANAGER_H_