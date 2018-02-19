/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : KeyboardManager.cpp
****************************/


#include "KeyboardManager.h"
#include "Header.h"

using namespace cocos2d;

KeyboardManager::KeyboardManager() {}

KeyboardManager::~KeyboardManager() {}

bool KeyboardManager::init() {
	if (!cocos2d::Node::init())
		return false;

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(KeyboardManager::on_key_pressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void KeyboardManager::on_key_pressed(EventKeyboard::KeyCode _key, Event* _event) {
	_last_key = _key;

	CCLOG("%d", _key);
}
