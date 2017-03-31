#ifndef KEYBOARD_MANAGER_H_
#define KEYBOARD_MANAGER_H_

#include "cocos2d.h"

class KeyboardManager : public cocos2d::Node {
public:
	KeyboardManager() {}
	virtual ~KeyboardManager() {}
	virtual bool init() {
		if (!cocos2d::Node::init())
			return false;

		return true;
	}
	CREATE_FUNC(KeyboardManager);
private:

};

#endif // !KEYBOARD_MANAGER_H_
