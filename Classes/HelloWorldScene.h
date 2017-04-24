#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Header.h"

class InputManager;
class InputInfo;
class PickingManager;
class BackGroundLayer;
class UnitLayer;
class UiLayer;
class PlayerUnitManager;

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	~HelloWorld();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	virtual void update(float _dt);
	void main_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _unit_array, const float _dt);
	void draw_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _unit_vector, const float _dt);
private:
	void create_drag_rect(InputInfo * const _input);
	void background_scroll();

	InputManager* input_manager;
	PickingManager* picking_manager;
	BackGroundLayer* bg_layer;
	UnitLayer* unit_layer;
	UiLayer* ui_layer;
	cocos2d::DrawNode* draw_node;

	direction scroll_direction;
	void check_dir(const cocos2d::Vec2 & _dir);
};

#endif // __HELLOWORLD_SCENE_H__
