#include "Unit.h"
#include "UnitAnimation.h"
#include "SimpleAudioEngine.h"
#include "UnitWeapon.h"

using namespace cocos2d;
using namespace CocosDenshion;

Unit::Unit() : unit_state(unit_state::idle) {
}

Unit::~Unit() {
	delete unit_animation;
	//delete attack_animation;
	//delete die_animation;
}

bool Unit::init() {

	assert(Sprite::init());

	int num = rand() % 17;

	char str[16] = { 0, };
	sprintf_s(str, sizeof(str), "marine016.bmp");

	auto sprite_cache = SpriteFrameCache::getInstance();
	this->initWithSpriteFrame(sprite_cache->spriteFrameByName(str));

	unit_animation = new UnitAnimation();
	unit_animation->init_animation(move, "marine", 9, 68, 9);
	unit_animation->init_animation(attack, "marine", 8, 51, 2, 3, -17);
	unit_animation->init_animation(die, "marine", 8, 221);

	/*move_animation = new UnitAnimation();
	this->addChild(move_animation);
	move_animation->init_animation("marine", 9, 68, 9, move);

	attack_animation = new UnitAnimation();
	this->addChild(attack_animation);
	attack_animation->init_animation("marine", 8, 51, 2, 3, -17, attack);

	die_animation = new UnitAnimation();
	this->addChild(die_animation);
	die_animation->init_animation("marine", 8, 221, die);*/

	move_speed = 2.0f;
	attack_speed = 0.3f;
	unit_dir = up;
	unit_state = idle;
	
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
	unit_state = unit_state::petrol;
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
	int dmg = _dmg - unit_info.armor;
	if (dmg <= 0)
		dmg = 1;
	unit_info.hp -= dmg;
	int hp = unit_info.hp;

	if (hp <= 0) {
		unit_info.hp = 0;
		die_unit();
	}
}

void Unit::run_action_animation(float _dt) {
	unit_animation->run_action_aniamtion(unit_state, this, _dt, unit_dir);


	switch (unit_state)
	{
	case production:
		break;
	case idle:
		break;
	case move:
		// 捞悼贸府
		run_action_move();
		// 局聪皋捞记 贸府
		unit_animation->run_action_aniamtion(move, this, _dt, unit_dir);
		break;
	case attack: {
		// 局聪皋捞记 贸府
		unit_animation->run_action_aniamtion(attack, this, _dt, unit_dir, 2);
		if (fire) {
			SimpleAudioEngine::getInstance()->playEffect("sound/marine/tmafir00.wav");
			weapon = new UnitWeapon();
			this->getParent()->addChild(weapon);
			weapon->set_target(target_unit);
			bullet_vector.push_back(weapon);
		}
		break;
	}
	case petrol: {
		// 捞悼贸府
		run_action_move();
		if (unit_state == idle) {
			unit_state = petrol;
			std::swap(move_vec2, my_pos_vec2);
		}
		// 局聪皋捞记 贸府
		unit_animation->run_action_aniamtion(move, this, _dt, unit_dir);
		break;
	}
	case hold:
		break;
	case die:
		unit_animation->run_action_aniamtion(die, this, _dt);
		break;
	default:
		break;
	}



	for (UnitWeapon* weapon : bullet_vector) {
		weapon->run_action_weapon_animation();
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
		this->setPosition(vec2 + (dir * move_speed));
	}
}

void Unit::check_dir(const cocos2d::Vec2 & _dir) {
	if (_dir.y > 0.3333333f) {
		if (_dir.y > 0.99f) {
			unit_dir = up;
		}
		else if (_dir.y > 0.6666666f) {
			unit_dir = (_dir.x > 0) ? up_right1 : up_left1;
		}
		else {
			unit_dir = (_dir.x > 0) ? up_right2 : up_left2;
		}
	}
	else if (_dir.y > -0.3333333f) {
		if (_dir.y > 0.1f) {
			unit_dir = (_dir.x > 0) ? up_right3 : up_left3;
		}
		else if (_dir.y > -0.1f) {
			unit_dir = (_dir.x > 0) ? right : left;
		}
		else {
			unit_dir = (_dir.x > 0) ? down_right1 : down_left1;
		}
	}
	else {
		if (_dir.y > -0.6666666f) {
			unit_dir = (_dir.x > 0) ? down_right2 : down_left2;
		}
		else if (_dir.y > -0.99f) {
			unit_dir = (_dir.x > 0) ? down_right3 : down_left3;
		}
		else {
			unit_dir = down;
		}
	}
}

void Unit::init_frame() {
	unit_animation->init_frame();
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