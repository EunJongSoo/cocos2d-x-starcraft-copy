#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "cocos2d.h"

class InputInfo;
class KeyboardInfo;
class KeyboardManager;
class MouseManager;
class MouseInfo;

class InputManager : public cocos2d::Node {
public:
	InputManager();
	~InputManager();

	InputInfo* input_prossce(const cocos2d::Vec2& _origin);
private:
	KeyboardManager* keyboard_manager;
	MouseManager* mouse_manager;
};

#endif // !INPUT_MANAGER_H_
