/****************************
������ : 2017-02-19
�ۼ��� : ������
���ϸ� : KeyboardManager.h
****************************/

#ifndef KEYBOARD_MANAGER_H_
#define KEYBOARD_MANAGER_H_

#include "cocos2d.h"

struct CV5;

class KeyboardManager : public cocos2d::Node {
public:
	KeyboardManager();
	virtual ~KeyboardManager();
	virtual bool init();
	CREATE_FUNC(KeyboardManager);

public:
	cocos2d::EventKeyboard::KeyCode _last_key;

private:
	void on_key_pressed(cocos2d::EventKeyboard::KeyCode _key, cocos2d::Event* _event);
};

#endif // !KEYBOARD_MANAGER_H_
