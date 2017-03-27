#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

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
    
	auto sprite_cache = SpriteFrameCache::getInstance();
	sprite_cache->addSpriteFramesWithFile("unit/marine/marine.plist", "unit/marine/marine.png");

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

	// ���콺 �̺�Ʈ ���
	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(HelloWorld::on_mouse_up, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	


	unit_state = 1;

    return true;
}

void HelloWorld::on_mouse_up(Event *_event) {
	// ���콺 �¿� ��ư ������ ���ؼ� ����ȯ
	EventMouse* e = static_cast<EventMouse*>(_event);

	// EventMouse���� ��ǥ�� �޾ƿ��� y��ǥ���� ������ �Ʒ� ������ Ŀ���� ������ 
	// y ��ǥ ������ ���� ���� ��ŭ ���༭ Ŭ���� ��ġ�� ã�´�
	auto win_size = Director::getInstance()->getWinSize();
	Vec2 location = e->getLocation();
	location.y = win_size.height - location.y;

	static int i = 0;

	switch (e->getMouseButton()) {
	case MOUSE_BUTTON_LEFT: {
		int i = _unit->_unit_dir;
		++i;
		if (i == 9) i = 11;
		if (i == 18) i = 0;
		_unit->_unit_dir = (direction)i;
		
		break;
	}
	case MOUSE_BUTTON_RIGHT: {
		
		if (_unit2->getBoundingBox().containsPoint(location)) {
			_unit->attack_unit(_unit2);
		}
		else {
			_unit->move_unit(location.x, location.y);
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
}
