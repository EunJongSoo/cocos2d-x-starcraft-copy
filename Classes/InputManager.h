#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "KeyboardManager.h"
#include "MouseManager.h"

class InputManager : public cocos2d::Node {
public:
	InputManager() {
		keyboard_manager = KeyboardManager::create();
		mouse_manager = MouseManager::create();
		this->addChild(keyboard_manager);
		this->addChild(mouse_manager);
	}
	~InputManager() {}

	MouseManager::mouse_order get_mouse_order() const {
		return mouse_manager->_mouse_order;
	}
	void mouse_order_init() {
		mouse_manager->init_mouse_order();
	}

	inline bool is_mouse_order() const {
		return mouse_manager->is_order();
	}

private:
	KeyboardManager* keyboard_manager;
	MouseManager* mouse_manager;
};

#endif // !INPUT_MANAGER_H_
