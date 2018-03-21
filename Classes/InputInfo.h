/****************************
������ : 2018-03-21
�ۼ��� : ������
���ϸ� : InputInfo.h
****************************/

#ifndef INPUT_INFO_H_
#define INPUT_INFO_H_

#include "Header.h"
#include "MouseInfo.h"

class InputInfo {
public:
	InputInfo()	{}
	~InputInfo() {
		SAFE_DELETE(mouse_info);
	}
	inline MouseInfo * get_mouse_info() const { return mouse_info; }
	inline void set_info(MouseInfo* _info) {
		mouse_info = _info;
	}

private:
	MouseInfo* mouse_info;
	//KeyboardInfo* keyboard_info;

};

#endif // !INPUT_INFO_H_

