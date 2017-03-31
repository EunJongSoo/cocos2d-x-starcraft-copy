#ifndef MOUSE_MANAGER_H_
#define MOUSE_MANAGER_H_

#include "cocos2d.h"

class MouseManager : public cocos2d::Node {
public:
	enum mouse_state {
		none, L_down, L_drag, L_double, L_up, R_down, R_up
	};
	struct mouse_order {
		mouse_order() : 
			mouse_state(mouse_state::none)
		{}
		
		mouse_state mouse_state;
		cocos2d::Vec2 start_mouse_pos;
		cocos2d::Vec2 end_mouse_pos;
	};
public:
	MouseManager();
	virtual ~MouseManager();
	virtual bool init();
	CREATE_FUNC(MouseManager);

	void init_mouse_order();
	inline bool is_order() const { 
		return _is_order;	
	}
public:
	mouse_order _mouse_order;

private:
	void on_mouse_down(cocos2d::Event* _event);
	void on_mouse_move(cocos2d::Event* _event);
	void on_mouse_up(cocos2d::Event* _event);
	cocos2d::Vec2 mouse_location_y(const cocos2d::Vec2& _location);
	float mouse_distance_check(const cocos2d::Vec2& _location);
	void set_mouse_order(mouse_state _state);
	void set_mouse_order(mouse_state _state, const cocos2d::Vec2& _pos);
private:
	bool _is_order;
	const float mouse_drag_distance = 0.5f;
	
	cocos2d::Size _win_size;
};

#endif // !KEYBOARD_MANAGER_H_