/****************************
수정일 : 2018-03-20
작성자 : 은종수
파일명 : InputManager.h
****************************/

#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "cocos2d.h"

class InputInfo;
class KeyboardManager;
class KeyboardInfo;
class MouseManager;
class MouseInfo;

/*인풋 매니저는 노드 클래스를 상속 받는다.
코코스라는 그림판 위에서 입력을 받는걸 받아 오려면 노드 클래스가 필요하기 때문이다.

이 인풋 매니저는 키보드 마우스에서 입력 받은 신호를 가지고 와서 
InputInfo에 포장해 전달하는 역할을 한다.*/
class InputManager : public cocos2d::Node {
public:
	InputManager();
	~InputManager();

	/*입력이 들어오는걸 처리하는 방법*/
	void input_process(const cocos2d::Vec2& _origin, InputInfo* const _input);
private:
	/*키보드에서 들어오는 입력을 관리할 매니저*/
	KeyboardManager* keyboard_manager;
	/*마우스에서 들어오는 입력을 관리할 매니저*/
	MouseManager* mouse_manager;
};

#endif // !INPUT_MANAGER_H_
