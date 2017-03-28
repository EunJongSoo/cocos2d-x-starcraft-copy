#include "Unit.h"
#include "UnitAnimation.h"
#include "SimpleAudioEngine.h"
#include "UnitWeapon.h"

using namespace cocos2d;
using namespace CocosDenshion;

Unit::Unit() : _unit_state(unit_state::idle) {
}

Unit::~Unit() {
	delete move_animation;
	delete attack_animation;
}

bool Unit::init() {

	assert(Sprite::init());

	auto sprite_cache = SpriteFrameCache::getInstance();
	this->initWithSpriteFrame(sprite_cache->spriteFrameByName("marine016.bmp"));

	move_animation = new UnitAnimation();
	this->addChild(move_animation);
	move_animation->init_animation("marine", 9, 68, 9);

	attack_animation = new UnitAnimation();
	this->addChild(attack_animation);
	attack_animation->init_animation("marine", 8, 51, 2, 3, -17);

	_move_speed = 2.0f;
	_attack_speed = 0.3f;
	_unit_dir = up;
	_unit_state = idle;
	
	return true;
}

void Unit::attack_unit(Unit* const _target) {
	_target_unit = _target;
	_unit_state = unit_state::attack;
	Vec2 vec2 = _target_unit->getPosition() - this->getPosition();
	vec2.normalize();
	check_dir(vec2);
}

void Unit::move_unit(const float _x, const float _y) {
	move_vec2 = Vec2(_x, _y);
	_move_x = _x;
	_move_y = _y;
	_unit_state = unit_state::move;
}

void Unit::stop_unit() {
	_unit_state = unit_state::idle;
}

void Unit::patrol_unit() {
	_unit_state = unit_state::petrol;
}

void Unit::hold_unit() {
	_unit_state = unit_state::hold;
}

void Unit::die_unit() {
	_unit_state = unit_state::die;
}

void Unit::run_action_animation(float _dt) {
	switch (_unit_state)
	{
	case production:
		break;
	case idle:
		break;
	case move:
		// 捞悼贸府
		run_action_move();
		// 局聪皋捞记 贸府
		move_animation->run_action_aniamtion(_dt, _unit_dir);
		break;
	case attack: {
		// 局聪皋捞记 贸府
		attack_animation->run_action_aniamtion(_dt, _unit_dir, 2);
		/*if (_fire) {
			SimpleAudioEngine::getInstance()->playEffect("sound/marine/tmafir00.wav");
			weapon = UnitWeapon::create();
			weapon->setPosition(_target_unit->getPosition());
			bullet_vector.push_back(weapon);
			weapon->retain();
			this->addChild(weapon);
		}*/
		break;
	}
	case petrol:
		break;
	case hold:
		break;
	case die:
		break;
	default:
		break;
	}
	for (UnitWeapon* weapon : bullet_vector) {
		weapon->run_action_weapon_animation();
	}
}

void Unit::run_action_move() {
	Rect bounding = this->getBoundingBox();
	if (bounding.containsPoint(move_vec2)) {
		_unit_state = idle;
	}
	else {
		Vec2 vec2 = this->getPosition();
		vec2 = move_vec2 - vec2;
		vec2.normalize();

		check_dir(vec2);
		this->setPosition(_position + (vec2 * _move_speed));
	}
}

void Unit::check_dir(const cocos2d::Vec2 & _dir) {
	if (_dir.y > 0.3333333f) {
		if (_dir.y > 0.99f) {
			_unit_dir = up;
		}
		else if (_dir.y > 0.6666666f) {
			_unit_dir = (_dir.x > 0) ? up_right1 : up_left1;
		}
		else {
			_unit_dir = (_dir.x > 0) ? up_right2 : up_left2;
		}
	}
	else if (_dir.y > -0.3333333f) {
		if (_dir.y > 0.1f) {
			_unit_dir = (_dir.x > 0) ? up_right3 : up_left3;
		}
		else if (_dir.y > -0.1f) {
			_unit_dir = (_dir.x > 0) ? right : left;
		}
		else {
			_unit_dir = (_dir.x > 0) ? down_right1 : down_left1;
		}
	}
	else {
		if (_dir.y > -0.6666666f) {
			_unit_dir = (_dir.x > 0) ? down_right2 : down_left2;
		}
		else if (_dir.y > -0.99f) {
			_unit_dir = (_dir.x > 0) ? down_right3 : down_left3;
		}
		else {
			_unit_dir = down;
		}
	}
}

//void Unit::move_run_action_animation(const float __dt) {
//	_dt += __dt;
//	if (0.05f > _dt) return;
//	_dt = 0;
//	if (sprite_flip_x(_unit_dir > left_check)) {
//		_unit_dir2 = _unit_dir - 10;
//	}
//	else {
//		_unit_dir2 = _unit_dir;
//	}
//	this->setSpriteFrame(move_clip.move_animation_vector[_frame++ + _unit_dir2 * _max_frame]);
//	if (_frame >= _max_frame) {
//		_frame = 0;
//
//	}
//}
//
//void Unit::attack_run_action_animation(const float __dt) {
//	_dt += __dt;
//	_dt2 += __dt;
//	if (0.05f > _dt) return;
//	if (_attack_speed > _dt2) return;
//
//	if (_frame == 2) {
//		_fire = true;
//	}
//	else {
//		_fire = false;
//	}
//
//	_dt = 0;
//	if (sprite_flip_x(_unit_dir > left_check)) {
//		_unit_dir2 = _unit_dir - 10;
//	}
//	else {
//		_unit_dir2 = _unit_dir;
//	}
//	this->setSpriteFrame(attack_animation_vector[_frame++ + _unit_dir2 * _max_frame]);
//	if (_frame >= _max_frame) {
//		_frame = 2;
//		_dt2 = 0;
//	}
//}