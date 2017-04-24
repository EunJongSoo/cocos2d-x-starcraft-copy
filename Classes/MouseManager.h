#ifndef MOUSE_MANAGER_H_
#define MOUSE_MANAGER_H_

#include <deque>
#include "cocos2d.h"
#include "MouseInfo.h"

class MouseManager : public cocos2d::Node {
public:
	MouseManager();
	virtual ~MouseManager();
	virtual bool init();
	CREATE_FUNC(MouseManager);

	MouseInfo* get_mouse_info();
	MouseInfo* get_normal_mouse_info();

private:
	void on_mouse_down(cocos2d::Event* _event);
	void on_mouse_move(cocos2d::Event* _event);
	void on_mouse_up(cocos2d::Event* _event);
	
	void on_mouse_L_down_process(const cocos2d::Vec2& _start_pos);
	void on_mouse_R_down_process(const cocos2d::Vec2& _start_pos);
	void on_mouse_L_dragging_process(const cocos2d::Vec2& _end_pos);
	void on_mouse_move_process(const cocos2d::Vec2& _end_pos);
	void on_mouse_L_up_process(const cocos2d::Vec2& _end_pos);
	void on_mouse_L_drag_process(const cocos2d::Vec2& _end_pos);

	void correction_mouse_location_y(cocos2d::Vec2& _point);
	bool mouse_distance_check(const cocos2d::Vec2& _vec2);
	void set_value(MouseInfo::mouse_state _state, const cocos2d::Vec2& _start_pos, const cocos2d::Vec2& _end_pos);
	void set_mouse_order();
private:
	cocos2d::Size win_size;

	MouseInfo::mouse_state state;
	MouseInfo::mouse_state order;
	cocos2d::Vec2 start_pos;
	cocos2d::Vec2 end_pos;

	std::deque<MouseInfo*> fast_mouse_info_deque;
	const float mouse_drag_distance = 0.5f;
};

#endif // !KEYBOARD_MANAGER_H_