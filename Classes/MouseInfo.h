/****************************
수정일 : 2018-03-21
작성자 : 은종수
파일명 : MouseInfo.h
****************************/

#ifndef MOUSE_INFO_H_
#define MOUSE_INFO_H_

#include "cocos2d.h"

/*
마우스 정보를 담는 클래스다.
상태값, 마우스 시작점, 끝점, 오리진을 가지고 있다.

마우스로 클릭하면 코코스에서 보는 화면의 좌표값이 넘어온다.
화면을 스크롤 시켜도 찍음점의 좌표값을 가지고 온다.

그래서 화면이 스크롤 됬을때의 좌표값을 계산하기 위해서
카메라 위치와 포지션 값을 계산해서 오리진 값을 가지고 와서 보정해준다.
*/
class MouseInfo {
public:
	enum class Mouse_state {
		none, 
		L_down, 
		L_dragging, 
		L_drag, 
		L_double, 
		L_up, 
		R_down, 
		R_up, 
	};
public:
	MouseInfo(Mouse_state _state, const cocos2d::Vec2& _start_pos, const cocos2d::Vec2& _end_pos) :
		state(_state),
		start_pos(_start_pos),
		end_pos(_end_pos),
		origin(cocos2d::Vec2::ZERO)
	{}
	~MouseInfo() {}

	inline void set_mouse_state(const Mouse_state& _state) { state = _state; }
 	inline void set_mouse_origin(const cocos2d::Vec2& _origin) { origin = _origin; }
	inline Mouse_state get_mouse_state() const { return state; }
	inline const cocos2d::Vec2 get_start_pos() const { return start_pos + origin; }
	inline const cocos2d::Vec2 get_end_pos() const { return end_pos + origin; }

private:
	MouseInfo();
	Mouse_state state;
	cocos2d::Vec2 start_pos;
	cocos2d::Vec2 end_pos;
	cocos2d::Vec2 origin;
};

#endif // !MOUSE_INFO_H_
