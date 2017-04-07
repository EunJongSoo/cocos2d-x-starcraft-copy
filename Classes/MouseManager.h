#ifndef MOUSE_MANAGER_H_
#define MOUSE_MANAGER_H_

#include "cocos2d.h"

// class 전방선언
class MouseInfo;

class MouseManager : public cocos2d::Node {
public:
	MouseManager();
	virtual ~MouseManager();
	virtual bool init();
	CREATE_FUNC(MouseManager);

	void init_mouse_info();

	// inline 함수
	inline MouseInfo* get_mouse_info() { return mouse_info; }
	inline bool is_order() const { 	return order; }

private:
	enum set_pos {
		start, end
	};
	void on_mouse_down(cocos2d::Event* _event);
	void on_mouse_move(cocos2d::Event* _event);
	void on_mouse_up(cocos2d::Event* _event);
	
	void correction_mouse_location_y(cocos2d::Vec2& _point);
	float mouse_distance_check(const cocos2d::Vec2& _vec2);
	void set_mouse_order(const int _state);
	void set_mouse_order(const int _state, cocos2d::Vec2& _vec2, set_pos _start_end);
	
private:
	bool order;
	cocos2d::Size win_size;
	MouseInfo* mouse_info;
	
	const float mouse_drag_distance = 0.5f;
};

#endif // !KEYBOARD_MANAGER_H_