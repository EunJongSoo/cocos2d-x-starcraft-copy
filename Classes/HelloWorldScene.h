/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : HelloWorldScene.h
****************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Header.h"

class Unit;
class InputManager;
class InputInfo;
class PickingManager;
class BackGroundLayer;
class UnitLayer;
class UiLayer;
class PlayerUnitManager;
class CameraManager;
class OrderManager;

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	~HelloWorld();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	virtual void update(float _dt);
	const std::vector<Unit*>& main_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _manager_vector);
	void draw_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _manager_vector, const float _dt);
private:
	void create_drag_rect(InputInfo * const _input);
	cocos2d::Vec2 get_origin() const;
	void camera_scroll(InputInfo * const _input);

	InputManager* input_manager;
	PickingManager* picking_manager;
	BackGroundLayer* bg_layer;
	UnitLayer* unit_layer;
	UiLayer* ui_layer;
	cocos2d::DrawNode* draw_node;
	CameraManager* camera_manager;
	OrderManager* order_manager;
};

#endif // __HELLOWORLD_SCENE_H__
