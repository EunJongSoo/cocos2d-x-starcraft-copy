/****************************
������ : 2018-03-20
�ۼ��� : ������
���ϸ� : InputManager.h
****************************/

#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "cocos2d.h"

class InputInfo;
class KeyboardManager;
class KeyboardInfo;
class MouseManager;
class MouseInfo;

/*��ǲ �Ŵ����� ��� Ŭ������ ��� �޴´�.
���ڽ���� �׸��� ������ �Է��� �޴°� �޾� ������ ��� Ŭ������ �ʿ��ϱ� �����̴�.

�� ��ǲ �Ŵ����� Ű���� ���콺���� �Է� ���� ��ȣ�� ������ �ͼ� 
InputInfo�� ������ �����ϴ� ������ �Ѵ�.*/
class InputManager : public cocos2d::Node {
public:
	InputManager();
	~InputManager();

	/*�Է��� �����°� ó���ϴ� ���*/
	void input_process(const cocos2d::Vec2& _origin, InputInfo* const _input);
private:
	/*Ű���忡�� ������ �Է��� ������ �Ŵ���*/
	KeyboardManager* keyboard_manager;
	/*���콺���� ������ �Է��� ������ �Ŵ���*/
	MouseManager* mouse_manager;
};

#endif // !INPUT_MANAGER_H_
