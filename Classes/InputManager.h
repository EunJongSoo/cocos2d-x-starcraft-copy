/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : InputManager.h
****************************/

#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "cocos2d.h"

class InputInfo;
class KeyboardInfo;
class KeyboardManager;
class MouseManager;
class MouseInfo;

class InputManager : public cocos2d::Node {
public:
	InputManager();
	~InputManager();

	void input_process(const cocos2d::Vec2& _origin, InputInfo* const _input);
private:
	KeyboardManager* keyboard_manager;
	MouseManager* mouse_manager;
};

#endif // !INPUT_MANAGER_H_
