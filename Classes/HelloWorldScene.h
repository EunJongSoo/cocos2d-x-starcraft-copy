#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "unit.h"

#include "Header.h"

class InputManager;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void update(float _dt);
	void input_process();
	void draw_process(float _dt);
	Unit* _unit;
	Unit* _unit2;
	int unit_state;

private:
	InputManager* input_manager;
};

#endif // __HELLOWORLD_SCENE_H__
