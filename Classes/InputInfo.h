/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : InputInfo.h
****************************/

#ifndef INPUT_INFO_H_
#define INPUT_INFO_H_

#include "Header.h"

#include "MouseInfo.h"
//#include "key"

//class MouseInfo;
//class KeyboardInfo;

class InputInfo {
public:
	InputInfo()	{}
	~InputInfo() {
		SAFE_DELETE(mouse_info);
		SAFE_DELETE(normal_mouse_info);
	}
	inline MouseInfo * get_mouse_info() const { return mouse_info; }
	inline MouseInfo * get_normal_mouse_info() const { return normal_mouse_info; }
	inline void set_info(MouseInfo* _info, MouseInfo* _normal) {
		mouse_info = _info;
		normal_mouse_info = _normal;
	}

private:
	MouseInfo* mouse_info;
	MouseInfo* normal_mouse_info;
	//KeyboardInfo* keyboard_info;

};

#endif // !INPUT_INFO_H_

