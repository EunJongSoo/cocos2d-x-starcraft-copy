#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "InputManager.h"
#include "InputInfo.h"
#include "MouseInfo.h"

#include "PickingManager.h"

#include "UnitLayer.h"
#include "Unit.h"
#include "PlayerUnitManager.h"

#include "BackGroundLayer.h"

#include "UiLayer.h"

#include "CameraManager.h"
#include "MapData.h"
#include "TemplateSingleton.h"

using namespace cocos2d;

HelloWorld::HelloWorld() :
	input_manager(nullptr),
	picking_manager(nullptr),
	unit_layer(nullptr),
	bg_layer(nullptr),
	draw_node(nullptr),
	camera_manager(nullptr)
{
}

HelloWorld::~HelloWorld()
{
	this->removeAllChildren();
	SAFE_DELETE(input_manager);
	SAFE_DELETE(picking_manager);
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

	//// 그림 파일 불러오기
	//auto sprite_cache = SpriteFrameCache::getInstance();
	//sprite_cache->addSpriteFramesWithFile("img/unit/marine/marine.plist", "img/unit/marine/marine.png");
	//sprite_cache->addSpriteFramesWithFile("img/unit/marine/tspark.plist", "img/unit/marine/tspark.png");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 배경추가
	bg_layer = BackGroundLayer::create();
	bg_layer->create_map();
	this->addChild(bg_layer, 0);

	// unit layer 추가
	unit_layer = UnitLayer::create();
	unit_layer->setPosition(0, 0);
	this->addChild(unit_layer, 1);
		
	// draw_node 추가
	draw_node = DrawNode::create();
	this->addChild(draw_node, 2);
	
	// ui layer 추가
	ui_layer = UiLayer::create();
	this->addChild(ui_layer, 3);

	// 맵 정보 불러오기
	MapData* map_data = TemplateSingleton<MapData>::get_instance();

	// camera_manager 추가
	camera_manager = new CameraManager(map_data->get_width(), map_data->get_height());

	// 메인 업데이트 시작
	this->scheduleUpdate();

	// 시간 체크
	int start, end;
	start = clock();
	end = clock();

    return true;
}

void HelloWorld::update(float _dt) {
	
	// 조작
	InputInfo * _input_info = input_manager->input_prossce(get_origin());
	std::vector<PlayerUnitManager*>& unit_manager_vector = unit_layer->get_unit_manager_vector();

	// 메인 프로세스
	main_process(_input_info, unit_manager_vector, _dt);

	// 그리기
	draw_process(_input_info, unit_manager_vector, _dt);

	SAFE_DELETE(_input_info);
}

void HelloWorld::main_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _unit_vector, const float _dt) {
	
	if (_input->get_mouse_info()) {
		// 조작된 유닛 에게 명령 내리기
		picking_manager->picking_unit(_input, _unit_vector);
	}
	// 모든 유닛을 움직이기
}



void HelloWorld::draw_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _unit_vector, const float _dt) {
	// 드래그한 범위를 그려준다.
	create_drag_rect(_input);
	camera_scroll(_input);
	// 전체 유닛 애니메이션 변경하기
	for (PlayerUnitManager* manager : _unit_vector) {
		std::vector<Unit*> unit_vector = manager->get_unit_vector();
		for (Unit* unit : unit_vector) {
			unit->run_action_animation(_dt);
		}
	}
}

// 기능 이관이 필요함
void HelloWorld::create_drag_rect(InputInfo * const _input) {
	MouseInfo* mouse_info = _input->get_mouse_info();
	if (mouse_info) {
		// 있으면 화면에 그린 그림을 삭제한다.
		draw_node->clear();

		// 마우스 상태가 드래그 중인지 확인한다.
		if (mouse_info->get_mouse_state() == MouseInfo::mouse_state::L_dragging) {
			// 마우스 클릭 시작점과 끝점의 값을 저장한다.
			Vec2 start_vec2(mouse_info->get_start_pos());
			Vec2 end_vec2(mouse_info->get_end_pos());

			// 사각형을 그린다.
			draw_node->drawRect(start_vec2, end_vec2, Color4F(10, 20, 30, 100));
		}
	}
}

Vec2 HelloWorld::get_origin() const
{
	return camera_manager->get_origin();
}

void HelloWorld::camera_scroll(InputInfo * const _input)
{
	const Vec2& move_pos = camera_manager->camera_scroll(_input->get_normal_mouse_info()->get_end_pos());
	ui_layer->setPosition(ui_layer->getPosition() + move_pos);
}

//
//mouse_info = input_manager->input_process();
//unit_array = player_manager->get_unit_array();
//unit pick_unit = picking(mouse_info, unit_array);
//game_manager->main_process(pick_unit);
//
//mouse_info = input_manager->input_process(player_manager->get_unit_array());

//	//
//	// DebugDraw 생성
//	//
//	debugDraw = DebugDraw::create();
//	this->addChild(debugDraw);
//	debugDraw->appendLine(1, player->getPosition(), enemyUFO->getPosition());
//
//
//	//
//	// DrawNode 생성
//	//
//	DrawNode* drawNode = DrawNode::create();
//	this->addChild(drawNode);
//	drawNode->drawLine(Point(500.0f, 100.0f), Point(800.0f, 400.0f), Color4F(0.0f, 1.0f, 0.0f, 1.0f));
//	drawNode->drawCircle(Point(500.0f, 500.0f), 70.0f, 45.0f, 10, true, Color4F(0.0f, 0.0f, 1.0f, 1.0f));
//	drawNode->drawRect(Point(200.0f, 300.0f), Point(300.0f, 200.0f), Color4F(1.0f, 1.0f, 0.0f, 1.0f));
//
//
//	this->schedule(schedule_selector(HelloWorld::updateCallback, this));
//
//	return true;
//}
//
//void HelloWorld::updateCallback(float dt)
//{
//	Point p_pos = player->getPosition();
//	Point e_pos = enemyUFO->getPosition();
//	Point new_pos;
//	float angle = 30.0f * dt;
//
//	// 플레이어 주위를 회전하는 UFO 위치 계산
//	new_pos.x = cos(CC_DEGREES_TO_RADIANS(-angle)) * (e_pos.x - p_pos.x) - sin(CC_DEGREES_TO_RADIANS(-angle)) * (e_pos.y - p_pos.y) + p_pos.x;
//	new_pos.y = sin(CC_DEGREES_TO_RADIANS(-angle)) * (e_pos.x - p_pos.x) + cos(CC_DEGREES_TO_RADIANS(-angle)) * (e_pos.y - p_pos.y) + p_pos.y;
//	enemyUFO->setPosition(new_pos);
//
//	// DebugDraw 갱신
//	// 색상변경 테스트
//	float r = RandomHelper::random_real(0.0f, 1.0f);
//	float g = RandomHelper::random_real(0.0f, 1.0f);
//	float b = RandomHelper::random_real(0.0f, 1.0f);
//	debugDraw->changeLineByTag(1, player->getPosition(), enemyUFO->getPosition(), r, g, b);
//}