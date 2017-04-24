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

using namespace cocos2d;

HelloWorld::HelloWorld() :
	input_manager(nullptr),
	picking_manager(nullptr),
	unit_layer(nullptr),
	bg_layer(nullptr),
	draw_node(nullptr),
	scroll_direction(direction::center)
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

	//// �׸� ���� �ҷ�����
	//auto sprite_cache = SpriteFrameCache::getInstance();
	//sprite_cache->addSpriteFramesWithFile("img/unit/marine/marine.plist", "img/unit/marine/marine.png");
	//sprite_cache->addSpriteFramesWithFile("img/unit/marine/tspark.plist", "img/unit/marine/tspark.png");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	// ī�޶� ��ǥ�� ���� ���� ����

	// ����߰�
	bg_layer = BackGroundLayer::create();
	bg_layer->create_map();
	this->addChild(bg_layer, 0);

	// unit layer �߰�
	unit_layer = UnitLayer::create();
	unit_layer->setPosition(0, 0);
	this->addChild(unit_layer, 1);
		
	// draw_node �߰�
	draw_node = DrawNode::create();
	this->addChild(draw_node, 2);
	
	// ui layer �߰�
	ui_layer = UiLayer::create();
	this->addChild(ui_layer, 3);

	// ���� ������Ʈ ����
	this->scheduleUpdate();

	// �ð� üũ
	int start, end;
	start = clock();
	end = clock();

    return true;
}

void HelloWorld::update(float _dt) {
	
	// ����
	InputInfo * _input_info = input_manager->input_prossce(get_origin());
	std::vector<PlayerUnitManager*>& unit_manager_vector = unit_layer->get_unit_manager_vector();

	// ���� ���μ���
	main_process(_input_info, unit_manager_vector, _dt);

	// �׸���
	draw_process(_input_info, unit_manager_vector, _dt);

	SAFE_DELETE(_input_info);
}

void HelloWorld::main_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _unit_vector, const float _dt) {
	
	if (_input->get_mouse_info()) {
		// ���۵� ���� ���� ��� ������
		picking_manager->picking_unit(_input, _unit_vector);
	}
	if (_input->get_normal_mouse_info()) {
		Vec2 mouse_pos = _input->get_normal_mouse_info()->get_end_pos();
		check_dir(mouse_pos);
	}
	background_scroll();
	// ��� ������ �����̱�
}

void HelloWorld::background_scroll()
{
	float x = 0.0f, y = 0.0f;
	switch (scroll_direction)
	{
	case direction::center: {
		x = 0.0f, y = 0.0f;
		break;
	}
	case direction::up: {
		y = 1.0f;
		break;
	}
	case direction::up_right2: {
		x = 1.0f, y = 1.0f;
		break;
	}
	case direction::right: {
		x = 1.0f;
		break;
	}
	case direction::down_right2: {
		x = 1.0f, y = -1.0f;
		break;
	}
	case direction::down: {
		y = -1.0f;
		break;
	}
	case direction::up_left2: {
		x = -1.0f, y = 1.0f;
		break;
	}
	case direction::left: {
		x = -+1.0f;
		break;
	}
	case direction::down_left2: {
		x = -1.0f, y = -1.0f;
		break;
	}
	}
	auto camera = Camera::getDefaultCamera();
	Vec2 camera_pos = camera->getPosition();


	if (camera_pos.x - 320.0f + x <= 0) {
		x = 0.0f;
	}
	if (camera_pos.y - 240.0f + y <= 0) {
		y = 0.0f;
	}

	if ((camera_pos.x + 320.0f + x) >= 4096.0f) {
		x = 0.0f;
	}
	if ((camera_pos.y + 240.0f + y) >= 4192.0f) {
		y = 0.0f;
	}

	//CCLOG("camera x : %f, camera y : %f", camera_pos.x, camera_pos.y);

	float camera_speed = 32.0f;
	Vec2 origin = Vec2(x, y) * camera_speed;
	camera->setPosition(camera_pos + origin);
	ui_layer->setPosition(ui_layer->getPosition() + origin);
	//draw_node->setPosition(draw_node->getPosition() + origin);
}

void HelloWorld::check_dir(const cocos2d::Vec2 & _pos) {
	scroll_direction = direction::center;
	if (_pos.y > 475.0f + get_origin().y) {
		scroll_direction = direction::up;
		if (_pos.x > 635.0f + get_origin().x)					scroll_direction = direction::up_right2;
		else if (_pos.x < 5.0f + get_origin().x) 				scroll_direction = direction::up_left2;
	}
	else if (_pos.y < 5.0f + get_origin().y) {
		scroll_direction = direction::down;
		if (_pos.x > 635.0f + get_origin().x)					scroll_direction = direction::down_right2;
		else if (_pos.x < 5.0f + get_origin().x) 				scroll_direction = direction::down_left2;
	}
	else if (_pos.x > 635.0f + get_origin().x)					scroll_direction = direction::right;
	else if (_pos.x < 5.0f + get_origin().x) 				scroll_direction = direction::left;
}

void HelloWorld::draw_process(InputInfo * const _input, const std::vector<PlayerUnitManager*>& _unit_vector, const float _dt) {
	// �巡���� ������ �׷��ش�.
	create_drag_rect(_input);

	// ��ü ���� �ִϸ��̼� �����ϱ�
	for (PlayerUnitManager* manager : _unit_vector) {
		std::vector<Unit*> unit_vector = manager->get_unit_vector();
		for (Unit* unit : unit_vector) {
			unit->run_action_animation(_dt);
		}
	}
}

// ��� �̰��� �ʿ���
void HelloWorld::create_drag_rect(InputInfo * const _input) {
	MouseInfo* mouse_info = _input->get_mouse_info();
	if (mouse_info) {
		// ������ ȭ�鿡 �׸� �׸��� �����Ѵ�.
		draw_node->clear();

		// ���콺 ���°� �巡�� ������ Ȯ���Ѵ�.
		if (mouse_info->get_mouse_state() == MouseInfo::mouse_state::L_dragging) {
			// ���콺 Ŭ�� �������� ������ ���� �����Ѵ�.
			Vec2 start_vec2(mouse_info->get_start_pos());
			Vec2 end_vec2(mouse_info->get_end_pos());

			// �簢���� �׸���.
			draw_node->drawRect(start_vec2, end_vec2, Color4F(10, 20, 30, 100));
		}
	}
}

//
//mouse_info = input_manager->input_process();
//unit_array = player_manager->get_unit_array();
//unit pick_unit = picking(mouse_info, unit_array);
//game_manager->main_process(pick_unit);
//
//mouse_info = input_manager->input_process(player_manager->get_unit_array());

//	//
//	// DebugDraw ����
//	//
//	debugDraw = DebugDraw::create();
//	this->addChild(debugDraw);
//	debugDraw->appendLine(1, player->getPosition(), enemyUFO->getPosition());
//
//
//	//
//	// DrawNode ����
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
//	// �÷��̾� ������ ȸ���ϴ� UFO ��ġ ���
//	new_pos.x = cos(CC_DEGREES_TO_RADIANS(-angle)) * (e_pos.x - p_pos.x) - sin(CC_DEGREES_TO_RADIANS(-angle)) * (e_pos.y - p_pos.y) + p_pos.x;
//	new_pos.y = sin(CC_DEGREES_TO_RADIANS(-angle)) * (e_pos.x - p_pos.x) + cos(CC_DEGREES_TO_RADIANS(-angle)) * (e_pos.y - p_pos.y) + p_pos.y;
//	enemyUFO->setPosition(new_pos);
//
//	// DebugDraw ����
//	// ���󺯰� �׽�Ʈ
//	float r = RandomHelper::random_real(0.0f, 1.0f);
//	float g = RandomHelper::random_real(0.0f, 1.0f);
//	float b = RandomHelper::random_real(0.0f, 1.0f);
//	debugDraw->changeLineByTag(1, player->getPosition(), enemyUFO->getPosition(), r, g, b);
//}