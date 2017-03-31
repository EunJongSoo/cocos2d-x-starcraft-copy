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
private:
	KeyboardManager* keyboard_manager;
	MouseManager* mouse_manager;
};

#endif // !INPUT_MANAGER_H_
