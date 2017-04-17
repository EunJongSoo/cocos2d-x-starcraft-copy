#include "Unit.h"
#include "UnitAnimation.h"
#include "UnitWeapon.h"

#include "TemplateSingleton.h"
#include "ResourcesManager.h"

using namespace cocos2d;

Unit::Unit() :
	_unit_dir(direction::up),
	_production_time(0.0f),
	_select_unit(false),
	_player_color(kWhite),
	_races_type(races_type::terran),
	_unit_state(unit_state::idle),
	_unit_effects(special_effects::none),
	_unit_info(nullptr),
	_unit_info2(nullptr),
	_production_info(nullptr),
	_target_unit(nullptr),
	_unit_animation(nullptr),
	_weapon(nullptr)
{}

Unit::~Unit() {
	// 멤버 변수 동적할당 안전해제
	SAFE_DELETE(_unit_animation);
	SAFE_DELETE(_unit_info);
	SAFE_DELETE(_unit_info2);
}

// cocos2d-x의 create 함수 변경
// 매개변수로 생성할 유닛의 타입과 위치를 받는다.
Unit * Unit::create(const unit_type _type, const cocos2d::Vec2& _vec2, player_color _color) {
	Unit * pRet = new Unit();
	if (pRet && pRet->init(_type, _vec2, _color)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		return (pRet = nullptr);
	}
}

// cocos2d-x의 init 함수 변경
// 매개변수로 생성할 유닛의 타입과 위치를 받는다.
bool Unit::init(unit_type _type, const cocos2d::Vec2& _vec2, player_color _color) {
	assert(Sprite::init());

	// 유닛 색상 지정
	_player_color = _color;

	// 유닛 애니메이션 생성
	_unit_animation = new UnitAnimation(_type, _player_color, this);
	this->setPosition(_vec2);

	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~


	auto resources_manager = TemplateSingleton<ResourcesManager>::get_instance();

	// 임시작성
	// 마린의 이미지로 초기화한다.
	char str[16] = { 0, };
	sprintf_s(str, sizeof(str), "marine0016.bmp");
	auto sprite_cache = SpriteFrameCache::getInstance();
	this->initWithTexture(resources_manager->load_resources(_player_color, str));

	// 임시작성
	// 유닛 정보를 생성한다.
	_unit_info = new unit_info(1, 1, 1, 1, 1, 1, 1, unit_type::marine, upgrade_type::bionic, "marine");
	_unit_info2 = new unit_info2(1, 1, 1, 1, 1);

	// 임시작성
	// 유닛 종류에 따라 달라짐
	_unit_info2->move_speed = 2.0f;
	_unit_info2->attack_speed = 0.3f;
	
	return true;
}

// 유닛 공격 명령
void Unit::attack_unit(Unit* const _target) {
	// 유닛의 현재 상태를 설정한다.
	set_state(unit_state::attack);
	
	// 타겟을 설정한다.
	_target_unit = _target;

	// 타겟의 위치와 유닛의 위치를 빼서 저장한다.
	Vec2 vec2 = _target_unit->getPosition() - this->getPosition();
	// 정규화 한다.
	vec2.normalize();
	// 방향을 확인한다.
	check_dir(vec2);
}

// 유닛 이동 명령
void Unit::move_unit(const cocos2d::Vec2& _vec2) {
	set_state(unit_state::move);
	_move_vec2 = _vec2;
}

// 유닛 정지 명령
void Unit::stop_unit() {
	set_state(unit_state::idle);
}

// 유닛 순찰 명령
void Unit::patrol_unit(const cocos2d::Vec2& _vec2) {
	set_state(unit_state::patrol);
	_move_vec2 = _vec2;
	_my_pos_vec2 = this->getPosition();
}

// 유닛 고정 명령
void Unit::hold_unit() {
	set_state(unit_state::hold);
}

// 유닛이 죽으면 호출
void Unit::die_unit() {
	set_state(unit_state::die);
}

// 공격 당할때 호출된다.
void Unit::hit(int _dmg) {
	// 공격력에서 방어력을 뺀다.
	int dmg = _dmg - _unit_info->defence;
	// 공격력이 0이하이면 1로 만든다.
	if (dmg <= 0)
		dmg = 1;
	// 데미지 만큼 체력을 깍는다.
	_unit_info->hp -= dmg;

	// 체력이 0이하인지 확인한다.
	int hp = _unit_info->hp;
	if (hp <= 0) {
		// 체력을 0으로 만든다.
		_unit_info->hp = 0;
		// 유닛이 죽는다.
		die_unit();
	}
}

void Unit::run_action_animation(float _dt) {
	// 후처리는 다른 곳에서..
	// unit_animation->run_action_aniamtion(unit_state, this, _dt, unit_dir);

	switch (_unit_state)
	{
	case production: 		break;
	case idle:				break;
	case move:
		run_action_move();														// 이동처리
		_unit_animation->run_action_aniamtion(move, this, _dt, _unit_dir);		// 애니메이션 처리
		break;
	case attack: {
		_unit_animation->run_action_aniamtion(attack, this, _dt, _unit_dir, 2);	// 애니메이션 처리		
		{																		// 생성 조건필요한데..
			_weapon = new UnitWeapon(_target_unit, unit_type::marine_weapon);
			this->getParent()->addChild(_weapon);
			_bullet_vector.push_back(_weapon);
		}
		break;
	}
	case patrol: {
		run_action_move();														// 이동처리, 기능 이관 해야됨
		if (_unit_state == idle) {
			_unit_state = patrol;
			std::swap(_move_vec2, _my_pos_vec2);
		}
		_unit_animation->run_action_aniamtion(move, this, _dt, _unit_dir);		// 애니메이션 처리
		break;
	}
	case hold: 		break;
	case die: 		_unit_animation->run_action_aniamtion(die, this, _dt); 		break;
	default:
		break;
	}
	weapon_animaiton(_dt);
}

// 임시 작성, 기능 이관 해야됨
void Unit::weapon_animaiton(float _dt) {
	
	for (UnitWeapon* weapon : _bullet_vector) {
		weapon->run_action_animation(_dt);
	}
	int i = 0, j = -1;
	for (UnitWeapon* weapon : _bullet_vector) {
		if (!weapon->isVisible()) {
			j = i;
		}
		++i;
	}
	if (j != -1) {
		this->getParent()->removeChild(_bullet_vector.at(j));
		delete _bullet_vector.at(j);
		_bullet_vector.erase(_bullet_vector.begin() + j);
	}
}

// 임시 작성, 기능 이관 해야된다.
void Unit::run_action_move() {
	Rect bounding = this->getBoundingBox();
	if (bounding.containsPoint(_move_vec2)) {
		_unit_state = idle;
	}
	else {
		// 현재 유닛 위치를 저장
		Vec2 unit_position = this->getPosition();
		// 목표 위치에서 유닛 위치를 뺀다
		Vec2 dir = _move_vec2 - unit_position;
		// 결과값을 정규화한다.
		dir.normalize();
		// 정규화 후 방향을 확인한다.
		check_dir(dir);

		// 방향에 이동속도를 곱한 후 현재 위치에 더한다.
		Vec2 tmp = unit_position + (dir * _unit_info2->move_speed);
		// 위치를 변경한다.
		this->setPosition(tmp);
	}
}

// 방향을 확인한다.
void Unit::check_dir(const cocos2d::Vec2 & _dir) {
	// 정규화된 값을 받아야한다.

	// y값이 0.33f보다 높은지 확인한다.
	if (_dir.y > up_right_left2) {
		// y값이 0.99f 보다 높은지 확인한다.
		if (_dir.y > up)						_unit_dir = direction::up;
		// y값이 0.66f 보다 높은지 확인한다.
		else if (_dir.y > up_right_left1) 		_unit_dir = (_dir.x > 0) ? direction::up_right1 : direction::up_left1;
		// 나머지는 0.33f보다 높고 0.66f보다 낮다.
		else                         			_unit_dir = (_dir.x > 0) ? direction::up_right2 : direction::up_left2;
	}
	// y값이 -0.33f보다 높은지 확인한다.
	else if (_dir.y > down_right_left1) {
		// y값이 0.1f보다 높은지 확인한다.
		if (_dir.y > up_right_left3)			_unit_dir = (_dir.x > 0) ? direction::up_right3 : direction::up_left3;
		// y값이 -0.1f 보다 높은지 확인한다.
		else if (_dir.y > right_left)			_unit_dir = (_dir.x > 0) ? direction::right : direction::left;
		// 나머지는 -0.33보다 높고 -0.1f보다 낮다.
		else									_unit_dir = (_dir.x > 0) ? direction::down_right1 : direction::down_left1;
	}
	// 나머지는 -0.33보다 낮다.
	else {
		// y값이 -0.66f보다 높은지 확인한다.
		if (_dir.y > -down_right_left2)			_unit_dir = (_dir.x > 0) ? direction::down_right2 : direction::down_left2;
		// y값이 -0.99f보다 높은지 확인한다.
		else if (_dir.y > down_right_left3)		_unit_dir = (_dir.x > 0) ? direction::down_right3 : direction::down_left3;
		// 나머지는 -0.99보다 낮다.
		else                             		_unit_dir = direction::down;
	}
}

// 상태를 설정한다.
void Unit::set_state(const unit_state _state) {
	// 애니메이션 프레임을 초기화한다.
	_unit_animation->init_frame();
	// 상태를 설정한다.
	_unit_state = _state;
}
