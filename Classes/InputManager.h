#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "cocos2d.h"

class InputInfo;
class MouseInfo;
class KeyboardManager;
class MouseManager;

class InputManager : public cocos2d::Node {
public:
	InputManager();
	~InputManager();

	InputInfo* input_prossce();

	void mouse_order_init();
	MouseInfo* get_mouse_info() const;
	bool is_mouse_order() const;

private:
	bool input_order;

	InputInfo* input;
	KeyboardManager* keyboard_manager;
	MouseManager* mouse_manager;
};

#endif // !INPUT_MANAGER_H_
