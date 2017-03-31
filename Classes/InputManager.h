#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "KeyboardManager.h"
#include "MouseManager.h"

class InputManager {
public:
	InputManager() {}
	~InputManager() {}

	KeyboardManager* get_keyboard_manager() const { return keyboard_manager; }
	MouseManager* get_mouse_manager() const { return mouse_manager; }
private:
	KeyboardManager* keyboard_manager;
	MouseManager* mouse_manager;
};

#endif // !INPUT_MANAGER_H_
