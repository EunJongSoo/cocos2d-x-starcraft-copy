#ifndef MOUSE_INFO_H_
#define MOUSE_INFO_H_

#include "cocos2d.h"

class MouseInfo {
public:
	enum mouse_state {
		none, L_down, L_dragging, L_drag, L_double, L_up, R_down, R_up, move
	};
public:
	MouseInfo() :
		state(mouse_state::none)
	{}
	~MouseInfo() {}

	inline void set_mouse_state(const int _state) { state = (mouse_state)(_state); }
	inline void set_start_pos(const cocos2d::Vec2& _start_pos) { start_pos = _start_pos; }
	inline void set_end_pos(const cocos2d::Vec2& _end_pos) { end_pos = _end_pos; }
	inline mouse_state get_mouse_state() const { return state; }
	inline const cocos2d::Vec2& get_start_pos() const { return start_pos; }
	inline const cocos2d::Vec2& get_end_pos() const { return end_pos; }

private:
	mouse_state state;
	cocos2d::Vec2 start_pos;
	cocos2d::Vec2 end_pos;
};

#endif // !MOUSE_INFO_H_
