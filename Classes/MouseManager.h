/****************************
수정일 : 2018-03-21
작성자 : 은종수
파일명 : MouseManager.h
****************************/

#ifndef MOUSE_MANAGER_H_
#define MOUSE_MANAGER_H_

#include "cocos2d.h"
#include "MouseInfo.h"

/*코코스에서 마우스 정보를 받아서 사용하려면 일단 입력을 받을
Scene이 필요하다 그 곳에 입력이 생기면 그걸 관련 함수로 받아오는거다

그러니까 이 마우스 매니저가 그 Scene의 자식으로 추가되있어야
여기서 마우스 신호를 받아올수 있다

InputManager의 자식으로 MouseManager를 추가하는건 
InputManager가 MainScene의 자식으로 추가되기 때문이다.

이걸 까먹어서 주석처리했더니 동작이 되니 안되니 했던거다... 헐

어쨋든 그런 이유로 이 마우스 매니저는 코코스의 Node 클래스를 상속받는다.
*/
class MouseManager : public cocos2d::Node {
public:
	/*앞에서 봤던 유닛 클래스는 초기화 당시 매개변수가 필요해서 create 함수를 수정했지만
	MouseManager는 그런게 없기 때문에 일반적(?)인 형태로 작성했다.
	초기화 하는 부분이나 CREATE_FUNC 부분말이다.
	
	CREATE_FUNC을 사용해서 저런식으로 해두면
	해당 클래스를 동적할당할때 ~::create() 이런식으로 할당하는데
	
	나중에 자동으로 안전해제를 하기 때문에 따로 신경쓸필요가 없다.
	그런데 InputManager의 소멸자 부분에 안전해제를 걸어둔걸 보면 무슨생각으로 사냐... 나

	이거 치면서 해당부분 주석 처리했다.
	*/
	MouseManager();
	virtual ~MouseManager();
	virtual bool init();
	CREATE_FUNC(MouseManager);

	/* 이건 외부(InputManager)에서 입력받은 마우스 정보를 가져갈수 있도록 만들었다.
	2개인건 아래 내용을 더 살펴보자*/
	MouseInfo* get_mouse_info();

private:
	/*
	뭐랄까.. 일반적인 마우스 사용 방법 이라고 해야되나
	코코스 마우스 정보를 받아올때 이벤트 리스너를 등록해야한다.
	그 때 매개가 되는 함수가 필요한다 아래 3가지 이다.
	좌, 우 클릭은 내부에서 구분하고 있다.
	*/
	void on_mouse_down(cocos2d::Event* _event);
	void on_mouse_move(cocos2d::Event* _event);
	void on_mouse_up(cocos2d::Event* _event);
	
	/*
	InputManager에서 부터 그렇지만 뭔가 됬을때 처리하는 
	함수의 이름을 process를 많이 붙여놨다. 

	각각 마우스 클릭? 눌렀을때, 드래그할때, 땟을때 어떤 처리를 하는지 정의한 함수다.
	*/
	void on_mouse_L_down_process(const cocos2d::Vec2& _start_pos);
	void on_mouse_R_down_process(const cocos2d::Vec2& _start_pos);
	void on_mouse_L_dragging_process(const cocos2d::Vec2& _end_pos);
	void on_mouse_L_up_process(const cocos2d::Vec2& _end_pos);
	void on_mouse_L_drag_process(const cocos2d::Vec2& _end_pos);

	/*
	y축이 클릭했을때 좌표가 반전되어 있다.
	그 마우스 좌표를 보정하기 위해서 만든 함수다.
	*/
	void correction_mouse_location_y(cocos2d::Vec2& _point);

	/*
	마우스 이동거리 확인하기 위한 함수다. 
	마우스를 누르고 움직이면 드래그인데 
	거리가 너무 짧으면 불편하기 때문에 
	어느정도 간격을 두었고 그 거리를 확인하는 함수다.
	*/
	bool check_mouse_distance(const cocos2d::Vec2& _vec2);

	/*
	값을 입력하는 방식이 똑같은데 
	입력하는 값과 사용하는 위치만 달라서
	함수 하나로 묶어놨다.
	*/
	void set_value(MouseInfo::Mouse_state _state, const cocos2d::Vec2& _start_pos, const cocos2d::Vec2& _end_pos);

private:
	/*
	화면 크기를 저장할 변수
	*/
	cocos2d::Size win_size;

	/*
	마우스 상태값으로 좌클릭 우클릭 드래그 같은 값들이다. 
	오더 변수가 뭐하는 건지 cpp 파일을 자세히 봐야할거 같다.
	*/
	MouseInfo::Mouse_state state;
	MouseInfo::Mouse_state order;
	/*
	마우스 드래그할때 시작점과 끝점을 저장하기 위한 변수다.
	*/
	cocos2d::Vec2 start_pos;
	cocos2d::Vec2 end_pos;

	/*
	상수로 지정한 마우스 드래그 최소거리다.
	*/
	const float mouse_drag_distance = 0.5f;
};

#endif // !KEYBOARD_MANAGER_H_