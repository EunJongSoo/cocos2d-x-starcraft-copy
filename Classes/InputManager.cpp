#include "InputManager.h"
#include "KeyboardManager.h"
#include "MouseManager.h"
#include "InputInfo.h"
#include "MouseInfo.h"

InputManager::InputManager() : 
	input_order(false), 
	input(nullptr),
	keyboard_manager(nullptr),
	mouse_manager(nullptr)
{
	input = new InputInfo();
	keyboard_manager = KeyboardManager::create();
	mouse_manager = MouseManager::create();
	this->addChild(keyboard_manager);
	this->addChild(mouse_manager);
}

InputManager::~InputManager() 
{
	if (input != nullptr) {
		delete input;
		input = nullptr;
	}
}

InputInfo * InputManager::input_prossce()
{
	if (is_mouse_order()) {
		input->set_mouse_order(true);
		input->set_mouse_info(this->get_mouse_info());
		this->mouse_order_init();
	}
	return input;
}

inline void InputManager::mouse_order_init()
{ 
	mouse_manager->init_mouse_info(); 
}

MouseInfo* InputManager::get_mouse_info() const 
{ 
	return mouse_manager->get_mouse_info();
}

bool InputManager::is_mouse_order() const 
{
	return mouse_manager->is_order();
}