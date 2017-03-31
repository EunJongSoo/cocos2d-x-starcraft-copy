#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InputManager.h"
#include "UnitLayer.h"

#include "Unit.h"

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
	this->addChild(input_manager);

	// 그림 파일 불러오기
	auto sprite_cache = SpriteFrameCache::getInstance();
	sprite_cache->addSpriteFramesWithFile("img/unit/marine/marine.plist", "img/unit/marine/marine.png");
	sprite_cache->addSpriteFramesWithFile("img/unit/marine/tspark.plist", "img/unit/marine/tspark.png");


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(sprite, 0);

	// unit layer 추가
	unit_layer = UnitLayer::create();
	unit_layer->setPosition(0, 0);
	this->addChild(unit_layer, 1);


	// 메인 업데이트 시작
	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float _dt) {
	
	// 조작
	input_process();
	
	// ??

	// 그리기
	draw_process(_dt);
}

// 짬뽕..
void HelloWorld::input_process() {
	if (input_manager->is_mouse_order()) {
		MouseManager::mouse_order& order = input_manager->get_mouse_order();
		switch (order.mouse_state) {
		case MouseManager::mouse_state::R_down: {

		}
		default:
			break;
		}

		input_manager->mouse_order_init();
	}
}
void HelloWorld::draw_process(float _dt) {



}