#include "Unit.h"
#include "UnitAnimation.h"
#include "UnitWeapon.h"

using namespace cocos2d;


Unit::Unit() :
	_unit_dir(direction::up),
	_tile_x(0),
	_tile_y(0),
	_production_time(0.0f),
	_selete_unit(false),
	_races_type(races_type::terran),
	_unit_state(unit_state::idle),
	_unit_effects(special_effects::none),
	_unit_info(nullptr),
	_unit_info2(nullptr),
	_production_info(nullptr),
	_target_unit(nullptr),
	_unit_animation(nullptr),
	_weapon(nullptr)
{
}

Unit::~Unit() {
	delete _unit_animation;
	delete _unit_info;
	delete _unit_info2;
}

Unit * Unit::create(const unit_type _type, const Vec2& _pos) {
	Unit * pRet = new Unit();
	if (pRet && pRet->init(_type, _pos)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		return (pRet = nullptr);
	}
}

bool Unit::init(unit_type _type, const Vec2& _pos) {
	assert(Sprite::init());

	// 유닛 애니메이션 생성
	_unit_animation = new UnitAnimation(_type, this);
	this->setPosition(_pos);

	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~

	char str[16] = { 0, };
	sprintf_s(str, sizeof(str), "marine016.bmp");
	auto sprite_cache = SpriteFrameCache::getInstance();
	this->initWithSpriteFrame(sprite_cache->spriteFrameByName(str));

	_unit_info = new unit_info(1, 1, 1, 1, 1, 1, 1, unit_type::marine, upgrade_type::bionic, "marine");
	_unit_info2 = new unit_info2(1, 1, 1, 1, 1);

	// 유닛 종류에 따라 달라짐
	_unit_info2->move_speed = 2.0f;
	_unit_info2->attack_speed = 0.3f;
	
	return true;
}

void Unit::attack_unit(Unit* const _target) {
	chang_order(unit_state::attack);
	_target_unit = _target;

	Vec2 vec2 = _target_unit->getPosition() - this->getPosition();
	vec2.normalize();
	check_dir(vec2);
}

void Unit::move_unit(const Vec2& _move_pos) {
	chang_order(unit_state::move);
	_move_vec2 = _move_pos;
}

void Unit::stop_unit() {
	chang_order(unit_state::idle);
}

void Unit::patrol_unit(const Vec2& _move_pos) {
	chang_order(unit_state::patrol);
	_move_vec2 = _move_pos;
	_my_pos_vec2 = this->getPosition();
}

void Unit::hold_unit() {
	chang_order(unit_state::hold);
}

void Unit::die_unit() {
	chang_order(unit_state::die);
}

void Unit::hit(int _dmg) {
	int dmg = _dmg - _unit_info->defence;
	if (dmg <= 0)
		dmg = 1;
	_unit_info->hp -= dmg;
	int hp = _unit_info->hp;

	if (hp <= 0) {
		_unit_info->hp = 0;
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

void Unit::run_action_move() {
	Rect bounding = this->getBoundingBox();
	if (bounding.containsPoint(_move_vec2)) {
		_unit_state = idle;
	}
	else {
		Vec2 vec2 = this->getPosition();
		Vec2 dir = _move_vec2 - vec2;
		dir.normalize();

		check_dir(dir);
		this->setPosition(vec2 + (dir * _unit_info2->move_speed));
	}
}

void Unit::check_dir(const cocos2d::Vec2 & _dir) {
	if (_dir.y > up_right_left2) {
		if (_dir.y > up)						_unit_dir = direction::up;
		else if (_dir.y > up_right_left1) 		_unit_dir = (_dir.x > 0) ? direction::up_right1 : direction::up_left1;
		else                         			_unit_dir = (_dir.x > 0) ? direction::up_right2 : direction::up_left2;
	}
	else if (_dir.y > down_right_left1) {
		if (_dir.y > up_right_left3)			_unit_dir = (_dir.x > 0) ? direction::up_right3 : direction::up_left3;
		else if (_dir.y > right_left)			_unit_dir = (_dir.x > 0) ? direction::right : direction::left;
		else									_unit_dir = (_dir.x > 0) ? direction::down_right1 : direction::down_left1;
	}
	else {
		if (_dir.y > -down_right_left2)			_unit_dir = (_dir.x > 0) ? direction::down_right2 : direction::down_left2;
		else if (_dir.y > down_right_left3)		_unit_dir = (_dir.x > 0) ? direction::down_right3 : direction::down_left3;
		else                             		_unit_dir = direction::down;
	}
}

void Unit::chang_order(const unit_state _state) {
	_unit_animation->init_frame();
	_unit_state = _state;
}
