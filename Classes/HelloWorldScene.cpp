#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InputManager.h"


using namespace cocos2d;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	input_manager = new InputManager();
	/*this->addChild(input_manager->get_keyboard_manager());
	this->addChild(input_manager->get_mouse_manager());*/

    
	auto sprite_cache = SpriteFrameCache::getInstance();
	sprite_cache->addSpriteFramesWithFile("img/unit/marine/marine.plist", "img/unit/marine/marine.png");
	sprite_cache->addSpriteFramesWithFile("img/unit/marine/tspark.plist", "img/unit/marine/tspark.png");


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(sprite);


	_unit = Unit::create();
	_unit->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(_unit);
    
	_unit2 = Unit::create();
	_unit2->setPosition(Vec2(50.0f + visibleSize.width / 2, 50.0f + visibleSize.height / 2));
	this->addChild(_unit2);

	this->scheduleUpdate();

	// 마우스 이벤트 등록
	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(HelloWorld::on_mouse_up, this);
	listener->onMouseMove = CC_CALLBACK_1(HelloWorld::on_mouse_move, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	unit_state = 1;

    return true;
}

void HelloWorld::on_mouse_move(Event *_event) {
	CCLOG("dd");
}

void HelloWorld::on_mouse_up(Event *_event) {
	// 마우스 좌우 버튼 구분을 위해서 형변환
	EventMouse* e = static_cast<EventMouse*>(_event);

	// EventMouse에서 좌표를 받아오면 y좌표값이 위에서 아래 쪽으로 커지기 때문에 
	// y 좌표 값에서 세로 길이 만큼 빼줘서 클릭한 위치를 찾는다
	auto win_size = Director::getInstance()->getWinSize();
	Vec2 location = e->getLocation();
	location.y = win_size.height - location.y;

	static int i = 0;

	switch (e->getMouseButton()) {
	case MOUSE_BUTTON_LEFT: {
		_unit->stop_unit();
		break;
	}
	case MOUSE_BUTTON_RIGHT: {
		
		if (_unit2->getBoundingBox().containsPoint(location)) {
			_unit->attack_unit(_unit2);
		}
		else {
			_unit->patrol_unit(location);
		}
		break;
	}
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::update(float _dt) {
	_unit->run_action_animation(_dt);
	_unit2->run_action_animation(_dt);
}
