/****************************
������ : 2017-02-19
�ۼ��� : ������
���ϸ� : InputManager.cpp
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
	// Ű���� ���� Ŭ���� ����
	keyboard_manager = KeyboardManager::create();

	// ���콺 ���� Ŭ���� ����
	mouse_manager = MouseManager::create();

	// ������ �߰�
	this->addChild(keyboard_manager);
	this->addChild(mouse_manager);
}

InputManager::~InputManager() 
{
	SAFE_DELETE(keyboard_manager);
	SAFE_DELETE(mouse_manager);
}

// ����ڿ��Լ� �Է¹��� ����� ó���ϴ� ���
void InputManager::input_process(const cocos2d::Vec2& _origin, InputInfo* const _input)
{
	// ��ü�� �����ؼ� ���콺 ������ �����͸� ����? �޴´�? �߶󳽴�?
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