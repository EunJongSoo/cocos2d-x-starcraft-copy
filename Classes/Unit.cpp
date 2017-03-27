#include "Unit.h"
#include "MarineDieAnimation.h"
#include "MarineAttackAnimation.h"
#include "MarineMoveAnimation.h"

using namespace cocos2d;

Unit::Unit() : _unit_state(unit_state::idle) {
}

Unit::~Unit() {
}

bool Unit::init() {

	assert(Sprite::init());

	auto sprite_cache = SpriteFrameCache::getInstance();
	this->initWithSpriteFrame(sprite_cache->spriteFrameByName("marine016.bmp"));

	char str[16];

	// move animation
	for (int j = 0; j < 9; ++j) {
		for (int i = 0; i < 9; ++i) {
			sprintf_s(str, sizeof(str), "marine%03d.bmp", 68 + j * 2 + i * 17);
			move_animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		}
	}

	// attack animation
	for (int j = 0; j < 9; ++j) {
		sprintf_s(str, sizeof(str), "marine%03d.bmp", 17 + j * 2);
		attack_animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		sprintf_s(str, sizeof(str), "marine%03d.bmp", 34 + j * 2);
		attack_animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		for (int i = 0; i < 3; ++i) {
			sprintf_s(str, sizeof(str), "marine%03d.bmp", 51 + j * 2);
			attack_animation_vector.push_back(sprite_cache->spriteFrameByName(str));
			sprintf_s(str, sizeof(str), "marine%03d.bmp", 34 + j * 2);
			attack_animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		}
	}

	// die animation
	for (int i = 221; i < 229; ++i) {
		sprintf_s(str, sizeof(str), "marine%03d.bmp", i);
		die_animation_vector.push_back(sprite_cache->spriteFrameByName(str));
	}

	_move_speed = 2.0f;
	_attack_speed = 0.3f;
	_dt = 0.0f;
	_unit_dir = up;
	_unit_state = idle;

	_frame = 0;
	_max_frame = 0;
	_unit_dir2 = up;

	_dt2 = 0.2f;

	return true;
}

void Unit::init_state() {
	switch (_unit_state)
	{
	case production:
		break;
	case idle:
		break;
	case move:
		break;
	case attack:
		break;
	case petrol:
		break;
	case hold:
		break;
	case die:
		break;
	default:
		break;
	}
}

void Unit::attack_unit(Unit* const _target) {
	init_state();

	_target_unit = _target;
	_unit_state = unit_state::attack;
	_frame = 0;
	_max_frame = 8;

	Vec2 vec2 = _target_unit->getPosition() - this->getPosition();
	vec2.normalize();
	check_dir(vec2);

	/*attack_animation->setVisible(true);
	move_animation->setVisible(false);
	die_animation->setVisible(false);*/
}

void Unit::move_unit(const float _x, const float _y) {
	init_state();

	move_vec2 = Vec2(_x, _y);
	_move_x = _x;
	_move_y = _y;
	_unit_state = unit_state::move;
	_frame = 0;
	_max_frame = 9;
	/*move_animation->setVisible(true);
	attack_animation->setVisible(false);
	die_animation->setVisible(false);*/
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
	init_state();

	_unit_state = unit_state::die;
	/*move_animation->setVisible(false);
	attack_animation->setVisible(false);
	die_animation->setVisible(true);*/
}

void Unit::run_action_animation(float _dt) {
	switch (_unit_state)
	{
	case production:
		break;
	case idle:
		break;
	case move:
		// 局聪皋捞记 贸府
		move_run_action_animation(_dt);
		//move_animation->run_action_animation(_dt, _unit_dir);
		// 捞悼贸府
		move_();
		break;
	case attack: {
		// 局聪皋捞记 贸府
		attack_run_action_animation(_dt);
		//attack_animation->run_action_animation(_dt, _unit_dir);
		// 傍拜贸府
		break;
	}
	case petrol:
		break;
	case hold:
		break;
	case die:
		//die_animation->run_action_animation(_dt);
		// 荤噶贸府
		break;
	default:
		break;
	}
}

void Unit::move_() {
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

void Unit::move_run_action_animation(const float __dt) {
	_dt += __dt;
	if (0.05f > _dt) return;
	_dt = 0;
	if (sprite_flip_x(_unit_dir > left_check)) {
		_unit_dir2 = _unit_dir - 10;
	}
	else {
		_unit_dir2 = _unit_dir;
	}
	this->setSpriteFrame(move_animation_vector[_frame++ + _unit_dir2 * _max_frame]);
	if (_frame >= _max_frame) {
		_frame = 0;

	}
}

void Unit::attack_run_action_animation(const float __dt) {
	_dt += __dt;
	_dt2 += __dt;
	if (0.05f > _dt) return;
	if (_attack_speed > _dt2) return;
	_dt = 0;
	if (sprite_flip_x(_unit_dir > left_check)) {
		_unit_dir2 = _unit_dir - 10;
	}
	else {
		_unit_dir2 = _unit_dir;
	}
	this->setSpriteFrame(attack_animation_vector[_frame++ + _unit_dir2 * _max_frame]);
	if (_frame >= _max_frame) {
		_frame = 2;
		_dt2 = 0;
	}
}

bool Unit::sprite_flip_x(const bool _b) {
	if (_b != this->isFlippedX())
		this->setFlippedX(_b);
	return _b;
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