/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : InputManager.cpp
****************************/

#include "InputManager.h"
#include "KeyboardManager.h"
#include "MouseManager.h"
#include "MouseInfo.h"
#include "InputInfo.h"

#include "Header.h"

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

InputManager::~InputManager() 
{
	SAFE_DELETE(keyboard_manager);
	SAFE_DELETE(mouse_manager);
}

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