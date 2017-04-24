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
	keyboard_manager = KeyboardManager::create();
	mouse_manager = MouseManager::create();
	this->addChild(keyboard_manager);
	this->addChild(mouse_manager);
}

InputManager::~InputManager() 
{
	SAFE_DELETE(keyboard_manager);
	SAFE_DELETE(mouse_manager);
}

InputInfo * InputManager::input_prossce(const cocos2d::Vec2& _origin)
{
	MouseInfo* info = mouse_manager->get_mouse_info();
	if (info) {
		info->set_mouse_origin(_origin);
	}
	MouseInfo* normal_info = mouse_manager->get_normal_mouse_info();
	if (normal_info) {
		normal_info->set_mouse_origin(_origin);
	}
	InputInfo* input = new InputInfo(info, normal_info);
	return input;
}