/****************************
������ : 2018-03-21
�ۼ��� : ������
���ϸ� : MouseManager.h
****************************/

#ifndef MOUSE_MANAGER_H_
#define MOUSE_MANAGER_H_

#include "cocos2d.h"
#include "MouseInfo.h"

/*���ڽ����� ���콺 ������ �޾Ƽ� ����Ϸ��� �ϴ� �Է��� ����
Scene�� �ʿ��ϴ� �� ���� �Է��� ����� �װ� ���� �Լ��� �޾ƿ��°Ŵ�

�׷��ϱ� �� ���콺 �Ŵ����� �� Scene�� �ڽ����� �߰����־��
���⼭ ���콺 ��ȣ�� �޾ƿü� �ִ�

InputManager�� �ڽ����� MouseManager�� �߰��ϴ°� 
InputManager�� MainScene�� �ڽ����� �߰��Ǳ� �����̴�.

�̰� ��Ծ �ּ�ó���ߴ��� ������ �Ǵ� �ȵǴ� �ߴ��Ŵ�... ��

��¶�� �׷� ������ �� ���콺 �Ŵ����� ���ڽ��� Node Ŭ������ ��ӹ޴´�.
*/
class MouseManager : public cocos2d::Node {
public:
	/*�տ��� �ô� ���� Ŭ������ �ʱ�ȭ ��� �Ű������� �ʿ��ؼ� create �Լ��� ����������
	MouseManager�� �׷��� ���� ������ �Ϲ���(?)�� ���·� �ۼ��ߴ�.
	�ʱ�ȭ �ϴ� �κ��̳� CREATE_FUNC �κи��̴�.
	
	CREATE_FUNC�� ����ؼ� ���������� �صθ�
	�ش� Ŭ������ �����Ҵ��Ҷ� ~::create() �̷������� �Ҵ��ϴµ�
	
	���߿� �ڵ����� ���������� �ϱ� ������ ���� �Ű澵�ʿ䰡 ����.
	�׷��� InputManager�� �Ҹ��� �κп� ���������� �ɾ�а� ���� ������������ ���... ��

	�̰� ġ�鼭 �ش�κ� �ּ� ó���ߴ�.
	*/
	MouseManager();
	virtual ~MouseManager();
	virtual bool init();
	CREATE_FUNC(MouseManager);

	/* �̰� �ܺ�(InputManager)���� �Է¹��� ���콺 ������ �������� �ֵ��� �������.
	2���ΰ� �Ʒ� ������ �� ���캸��*/
	MouseInfo* get_mouse_info();

private:
	/*
	������.. �Ϲ����� ���콺 ��� ��� �̶�� �ؾߵǳ�
	���ڽ� ���콺 ������ �޾ƿö� �̺�Ʈ �����ʸ� ����ؾ��Ѵ�.
	�� �� �Ű��� �Ǵ� �Լ��� �ʿ��Ѵ� �Ʒ� 3���� �̴�.
	��, �� Ŭ���� ���ο��� �����ϰ� �ִ�.
	*/
	void on_mouse_down(cocos2d::Event* _event);
	void on_mouse_move(cocos2d::Event* _event);
	void on_mouse_up(cocos2d::Event* _event);
	
	/*
	InputManager���� ���� �׷����� ���� ������ ó���ϴ� 
	�Լ��� �̸��� process�� ���� �ٿ�����. 

	���� ���콺 Ŭ��? ��������, �巡���Ҷ�, ������ � ó���� �ϴ��� ������ �Լ���.
	*/
	void on_mouse_L_down_process(const cocos2d::Vec2& _start_pos);
	void on_mouse_R_down_process(const cocos2d::Vec2& _start_pos);
	void on_mouse_L_dragging_process(const cocos2d::Vec2& _end_pos);
	void on_mouse_L_up_process(const cocos2d::Vec2& _end_pos);
	void on_mouse_L_drag_process(const cocos2d::Vec2& _end_pos);

	/*
	y���� Ŭ�������� ��ǥ�� �����Ǿ� �ִ�.
	�� ���콺 ��ǥ�� �����ϱ� ���ؼ� ���� �Լ���.
	*/
	void correction_mouse_location_y(cocos2d::Vec2& _point);

	/*
	���콺 �̵��Ÿ� Ȯ���ϱ� ���� �Լ���. 
	���콺�� ������ �����̸� �巡���ε� 
	�Ÿ��� �ʹ� ª���� �����ϱ� ������ 
	������� ������ �ξ��� �� �Ÿ��� Ȯ���ϴ� �Լ���.
	*/
	bool check_mouse_distance(const cocos2d::Vec2& _vec2);

	/*
	���� �Է��ϴ� ����� �Ȱ����� 
	�Է��ϴ� ���� ����ϴ� ��ġ�� �޶�
	�Լ� �ϳ��� �������.
	*/
	void set_value(MouseInfo::Mouse_state _state, const cocos2d::Vec2& _start_pos, const cocos2d::Vec2& _end_pos);

private:
	/*
	ȭ�� ũ�⸦ ������ ����
	*/
	cocos2d::Size win_size;

	/*
	���콺 ���°����� ��Ŭ�� ��Ŭ�� �巡�� ���� �����̴�. 
	���� ������ ���ϴ� ���� cpp ������ �ڼ��� �����Ұ� ����.
	*/
	MouseInfo::Mouse_state state;
	MouseInfo::Mouse_state order;
	/*
	���콺 �巡���Ҷ� �������� ������ �����ϱ� ���� ������.
	*/
	cocos2d::Vec2 start_pos;
	cocos2d::Vec2 end_pos;

	/*
	����� ������ ���콺 �巡�� �ּҰŸ���.
	*/
	const float mouse_drag_distance = 0.5f;
};

#endif // !KEYBOARD_MANAGER_H_