#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "InputManager.h"
#include "InputInfo.h"
#include "MouseInfo.h"

#include "PickingManager.h"

#include "UnitLayer.h"
#include "Unit.h"


using namespace cocos2d;

HelloWorld::HelloWorld() :
	input_manager(nullptr),
	picking_manager(nullptr),
	unit_layer(nullptr)
{
}

HelloWorld::~HelloWorld()
{
	this->removeAllChildren();
	CC_SAFE_DELETE(input_manager);
	CC_SAFE_DELETE(picking_manager);
}

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

	picking_manager = new PickingManager();


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
	InputInfo * _input_info = input_manager->input_prossce();
	std::vector<Unit*>& unit_array = unit_layer->get_unit_array();

	// 메인 프로세스
	main_process(_input_info, unit_array, _dt);


	// 그리기
	draw_process(_dt);
}

void HelloWorld::main_process(InputInfo * const _input, const std::vector<Unit*>& _unit_array, const float _dt) {
	
	// 조작된 유닛 움직이기
	if (_input->get_mouse_order()) {
		picking_manager->picking_unit(_input, _unit_array);
	}

	// 전체 유닛 현재 명령 수행하기
	for (Unit* unit : _unit_array) {
		unit->run_action_animation(_dt);
	}
}

void HelloWorld::draw_process(float _dt) {

}
//
//mouse_info = input_manager->input_process();
//unit_array = player_manager->get_unit_array();
//unit pick_unit = picking(mouse_info, unit_array);
//game_manager->main_process(pick_unit);
//
//mouse_info = input_manager->input_process(player_manager->get_unit_array());