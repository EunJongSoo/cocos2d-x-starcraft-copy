#include "Unit.h"
#include "UnitAnimation.h"
#include "UnitWeapon.h"

using namespace cocos2d;


Unit::Unit() : unit_state(unit_state::idle), unit_dir(direction::up) {
}

Unit::~Unit() {
	delete unit_animation;
}

bool Unit::init() {
	assert(Sprite::init());

	// 유닛 애니메이션 생성
	unit_animation = new UnitAnimation(unit_type::marine, this);

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
	init_frame();
	target_unit = _target;
	unit_state = unit_state::attack;
	Vec2 vec2 = target_unit->getPosition() - this->getPosition();
	vec2.normalize();
	check_dir(vec2);
}

void Unit::move_unit(const Vec2& _move_pos) {
	init_frame();
	move_vec2 = _move_pos;
	unit_state = unit_state::move;
}

void Unit::stop_unit() {
	init_frame();
	unit_state = unit_state::idle;
}

void Unit::patrol_unit(const Vec2& _move_pos) {
	init_frame();
	move_vec2 = _move_pos;
	my_pos_vec2 = this->getPosition();
	unit_state = unit_state::patrol;
}

void Unit::hold_unit() {
	init_frame();
	unit_state = unit_state::hold;
}

void Unit::die_unit() {
	init_frame();
	unit_state = unit_state::die;
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

	switch (unit_state)
	{
	case production: 		break;
	case idle:				break;
	case move:
		run_action_move();														// 이동처리
		unit_animation->run_action_aniamtion(move, this, _dt, unit_dir);		// 애니메이션 처리
		break;
	case attack: {
		unit_animation->run_action_aniamtion(attack, this, _dt, unit_dir, 2);	// 애니메이션 처리		
		{																		// 생성 조건필요한데..
			weapon = new UnitWeapon(target_unit, unit_type::marine_weapon);
			this->getParent()->addChild(weapon);
			bullet_vector.push_back(weapon);
		}
		break;
	}
	case patrol: {
		run_action_move();														// 이동처리, 기능 이관 해야됨
		if (unit_state == idle) {
			unit_state = patrol;
			std::swap(move_vec2, my_pos_vec2);
		}
		unit_animation->run_action_aniamtion(move, this, _dt, unit_dir);		// 애니메이션 처리
		break;
	}
	case hold: 		break;
	case die: 		unit_animation->run_action_aniamtion(die, this, _dt); 		break;
	default:
		break;
	}
	weapon_animaiton(_dt);
}

// 임시 작성, 기능 이관 해야됨
void Unit::weapon_animaiton(float _dt) {
	
	for (UnitWeapon* weapon : bullet_vector) {
		weapon->run_action_animation(_dt);
	}
	int i = 0, j = -1;
	for (UnitWeapon* weapon : bullet_vector) {
		if (!weapon->isVisible()) {
			j = i;
		}
		++i;
	}
	if (j != -1) {
		this->getParent()->removeChild(bullet_vector.at(j));
		delete bullet_vector.at(j);
		bullet_vector.erase(bullet_vector.begin() + j);
	}
}

void Unit::run_action_move() {
	Rect bounding = this->getBoundingBox();
	if (bounding.containsPoint(move_vec2)) {
		unit_state = idle;
	}
	else {
		Vec2 vec2 = this->getPosition();
		Vec2 dir = move_vec2 - vec2;
		dir.normalize();

		check_dir(dir);
		this->setPosition(vec2 + (dir * _unit_info2->move_speed));
	}
}

void Unit::check_dir(const cocos2d::Vec2 & _dir) {
	if (_dir.y > up_right_left2) {
		if (_dir.y > up)						unit_dir = direction::up;
		else if (_dir.y > up_right_left1) 		unit_dir = (_dir.x > 0) ? direction::up_right1 : direction::up_left1;
		else                         			unit_dir = (_dir.x > 0) ? direction::up_right2 : direction::up_left2;
	}
	else if (_dir.y > down_right_left1) {
		if (_dir.y > up_right_left3)			unit_dir = (_dir.x > 0) ? direction::up_right3 : direction::up_left3;
		else if (_dir.y > right_left)			unit_dir = (_dir.x > 0) ? direction::right : direction::left;
		else									unit_dir = (_dir.x > 0) ? direction::down_right1 : direction::down_left1;
	}
	else {
		if (_dir.y > -down_right_left2)			unit_dir = (_dir.x > 0) ? direction::down_right2 : direction::down_left2;
		else if (_dir.y > down_right_left3)		unit_dir = (_dir.x > 0) ? direction::down_right3 : direction::down_left3;
		else                             		unit_dir = direction::down;
	}
}

void Unit::init_frame() {
	unit_animation->init_frame();
}
