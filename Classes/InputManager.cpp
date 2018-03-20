/****************************
수정일 : 2018-03-20
작성자 : 은종수
파일명 : InputManager.cpp
****************************/

#include "InputManager.h"
#include "KeyboardManager.h"
#include "MouseManager.h"
#include "MouseInfo.h"
#include "InputInfo.h"

#include "Header.h"
/*
생성자에서 변수 초기화 해주고 키보드 마우스 매니저 클래스를 생성하고
인풋 매니저 자식으로 추가한다.

왜 자식으로 추가했는지 궁금해서 주석 처리하고 실행하니 동작을 안한다.
왜그런지는 잘 모르겠다.
*/
InputManager::InputManager() : 
	keyboard_manager(nullptr),
	mouse_manager(nullptr)
{
	// 키보드 관리 클래스 생성
	keyboard_manager = KeyboardManager::create();

	// 마우스 관리 클래스 생성
	mouse_manager = MouseManager::create();

	// 밑으로 추가
	this->addChild(keyboard_manager);
	this->addChild(mouse_manager);
}
/*키보드, 마우스 매니저를 create로 생성하면 코코스에서 자동으로 안전해제를 한다.
그래서 필요가 없는데 왜 등록을 했는지 모르겠다.*/
InputManager::~InputManager() 
{
	SAFE_DELETE(keyboard_manager);
	SAFE_DELETE(mouse_manager);
}

/*
입력 받은걸 처리하는 프로세스인데 마우스쪽만 코딩을 해서 키보드쪽 처리 내용이 없다.
마우스로 입력한 정보를 받아오는데 정보가 2개가 있다
왜 그런지 기억이 안나는데.. 마우스 매니저 처리되는걸 확인해봐야 할거 같다.
*/

// 사용자에게서 입력받은 명령을 처리하는 방법
void InputManager::input_process(const cocos2d::Vec2& _origin, InputInfo* const _input)
{
	// 객체를 생성해서 마우스 정보의 포인터를 복사? 받는다? 잘라낸다?
	MouseInfo* info = mouse_manager->get_mouse_info();
	if (info) {
		info->set_mouse_origin(_origin);
	}
	MouseInfo* normal_info = mouse_manager->get_normal_mouse_info();
	if (normal_info) {
		normal_info->set_mouse_origin(_origin);
	}
	_input->set_info(info, normal_info);
}