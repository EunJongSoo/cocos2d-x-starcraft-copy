#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Header.h"

class InputManager;
class InputInfo;
class PickingManager;
class UnitLayer;
class Unit;

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	~HelloWorld();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	virtual void update(float _dt);
	void main_process(InputInfo * const _input, const std::vector<Unit*>& _unit_array, const float _dt);
	void draw_process(float _dt);
private:
	InputManager* input_manager;
	PickingManager* picking_manager;
	UnitLayer* unit_layer;
	
};

#endif // __HELLOWORLD_SCENE_H__
