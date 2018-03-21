/****************************
������ : 2018-03-21
�ۼ��� : ������
���ϸ� : MouseInfo.h
****************************/

#ifndef MOUSE_INFO_H_
#define MOUSE_INFO_H_

#include "cocos2d.h"

/*
���콺 ������ ��� Ŭ������.
���°�, ���콺 ������, ����, �������� ������ �ִ�.

���콺�� Ŭ���ϸ� ���ڽ����� ���� ȭ���� ��ǥ���� �Ѿ�´�.
ȭ���� ��ũ�� ���ѵ� �������� ��ǥ���� ������ �´�.

�׷��� ȭ���� ��ũ�� �������� ��ǥ���� ����ϱ� ���ؼ�
ī�޶� ��ġ�� ������ ���� ����ؼ� ������ ���� ������ �ͼ� �������ش�.
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
