#include "UnitAnimation.h"

using namespace cocos2d;

UnitAnimation::UnitAnimation() : frame(0), dt(0.0f) {}
UnitAnimation::~UnitAnimation() {}


void UnitAnimation::run_action_aniamtion(unit_state _state, Sprite* _sprite, float _dt, int _dir, int _frame) {
	switch (_state)
	{
	case move:
		clip_aniamtion(move_clip, _sprite, _dt, _dir, _frame);
		break;
	case attack:
		clip_aniamtion(attack_clip, _sprite, _dt, _dir, _frame);
		break;
	case petrol:
		break;
	case die:
		clip_aniamtion(die_clip, _sprite, _dt, _dir, _frame);
		break;
	default:
		break;
	}
}

//void UnitAnimation::move_aniamtion(Sprite* _sprite, float _dt, int _dir, int _frame) {
//	dt += _dt;
//	if (0.05f > dt) return;
//	dt = 0;
//
//	int _tmp_dir = sprite_flipped_x(_sprite, _dir > left_check, _sprite->isFlippedX(), _dir);
//
//	_sprite->setSpriteFrame(move_clip.animation_vector[frame++ + _tmp_dir * move_clip.max_frame]);
//	if (frame >= move_clip.max_frame) {
//		frame = _frame;
//	}
//}
//
//void UnitAnimation::attack_aniamtion(cocos2d::Sprite* _sprite, float _dt, int _dir, int _frame) {
//	dt += _dt;
//	if (0.05f > dt) return;
//	dt = 0;
//
//	int _tmp_dir = sprite_flipped_x(_sprite, _dir > left_check, _sprite->isFlippedX(), _dir);
//
//	_sprite->setSpriteFrame(attack_clip.animation_vector[frame++ + _tmp_dir * attack_clip.max_frame]);
//	if (frame >= attack_clip.max_frame) {
//		frame = _frame;
//	}
//}
//
//void UnitAnimation::die_aniamtion(cocos2d::Sprite* _sprite, float _dt, int _dir, int _frame) {
//	dt += _dt;
//	if (0.05f > dt) return;
//	dt = 0;
//	
//	int _tmp_dir = sprite_flipped_x(_sprite, _dir > left_check, _sprite->isFlippedX(), _dir);
//	
//	_sprite->setSpriteFrame(die_clip.animation_vector[frame++ + _tmp_dir * die_clip.max_frame]);
//	if (frame >= die_clip.max_frame) {
//		frame = _frame;
//	}
//}

void UnitAnimation::init_animation(unit_state _state, char* _str, int _max_frame, int _base) {
	switch (_state)
	{
	case move: 		init_clip(move_clip, _str, _max_frame, _base);		break;
	case attack:	init_clip(attack_clip, _str, _max_frame, _base);	break;
	case die:		init_clip(die_clip, _str, _max_frame, _base);		break;
	default:	break;
	}
}

void UnitAnimation::init_animation(unit_state _state, char* _str, int _max_frame, int _base, int _ani_count) {
	switch (_state)
	{
	case move:		init_clip(move_clip, _str, _max_frame, _base, _ani_count);		break;
	case attack:	init_clip(attack_clip, _str, _max_frame, _base, _ani_count);	break;
	case die:		init_clip(die_clip, _str, _max_frame, _base, _ani_count);		break;
	default:		break;
	}
}

void UnitAnimation::init_animation(unit_state _state, char* _str, int _max_frame, int _base, int _ani_count, int _loop, int _num) {
	switch (_state)
	{
	case move:		init_clip(move_clip, _str, _max_frame, _base, _ani_count, _loop, _num);		break;
	case attack:	init_clip(attack_clip, _str, _max_frame, _base, _ani_count, _loop, _num);	break;
	case die:		init_clip(die_clip, _str, _max_frame, _base, _ani_count, _loop, _num);		break;
	default:		break;
	}
}

void UnitAnimation::init_frame() {
	frame = 0;
	dt = 0;
}

void UnitAnimation::sprite_flipped_x(Sprite* _sprite, bool _is_left, bool _is_flipped_x) {
	if (_is_left != _is_flipped_x) {
		_sprite->setFlippedX(_is_left);
	}
}


void UnitAnimation::init_clip(clip& _clip, char* _str, int _max_frame, int _base) {
	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
	_clip.max_frame = _max_frame;
	char str[16];
	// 모션 수
	for (int i = 0; i <_clip.max_frame; ++i) {
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + i);
		_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
	}
}


void UnitAnimation::init_clip(clip& _clip, char* _str, int _max_frame, int _base, int _ani_count) {
	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
	_clip.max_frame = _max_frame;
	char str[16];
	// 방향 수
	for (int j = 0; j < 9; ++j) {
		// 애니메이션 수
		for (int i = 0; i < _ani_count; ++i) {
			sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + j * 2 + i * 17);
			_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		}
	}
}

void UnitAnimation::init_clip(clip& _clip, char* _str, int _max_frame, int _base, int _ani_count, int _loop, int _num) {
	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
	_clip.max_frame = _max_frame;
	char str[16];

	// 방향 수
	for (int j = 0; j < 9; ++j) {
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, 17 + j * 2);
		_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, 34 + j * 2);
		_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		for (int k = 0; k < _loop; ++k) {
			// 애니메이션 수
			for (int i = 0; i < _ani_count; ++i) {
				sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + j * 2 + i * _num);
				_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
			}
		}
	}
}


void UnitAnimation::clip_aniamtion(const clip& _clip, Sprite* _sprite, float _dt, int _dir, int _frame) {
	dt += _dt;
	if (0.05f > dt) return;
	dt = 0;

	bool is_left = _dir > left_check;
	int tmp_dir = is_left ? _dir - 10 : _dir;
	sprite_flipped_x(_sprite, is_left, _sprite->isFlippedX());
	
	_sprite->setSpriteFrame(_clip.animation_vector[frame++ + tmp_dir * _clip.max_frame]);
	if (frame >= _clip.max_frame) {
		frame = _frame;
	}
}

//// init_animation을 하나에 하려면 매개변수가 너무 많아짐
//void UnitAnimation::init_animation(char* _str, int _max_frame, int _base, int _ani_count, int _loop, int _num,
//	int _dir, bool _attack, int _ready_count, int _ready_base)
//{
//	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
//	_parent = static_cast<cocos2d::Sprite*>(this->getParent());
//	max_frame = _max_frame;
//	char str[16];
//
//	// 방향 수
//	for (int j = 0; j < _dir; ++j) {
//		// 공격 준비 자세
//		if (_attack) {
//			for (int l = 0; l < _ready_count; ++l) {
//				sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _ready_base + j * 2 + l * 17);
//				animation_vector.push_back(sprite_cache->spriteFrameByName(str));
//			}
//		}
//		// 같은 동작 반복시
//		for (int k = 0; k < _loop; ++k) {
//			// 애니메이션 수
//			for (int i = 0; i < _ani_count; ++i) {
//				sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + j * 2 + i * _num);
//				animation_vector.push_back(sprite_cache->spriteFrameByName(str));
//			}
//		}
//	}
//}

//
//UnitAnimation::UnitAnimation() : _frame(0), _max_frame(0), _animation_time(0.5), _dt(0.0f) {
//}
//
//UnitAnimation::~UnitAnimation() {
//}
//
//bool UnitAnimation::init() {
//	
//	assert(Sprite::init());
//	//// move 애니메이션
//	//for (int i = 0; i < 9; ++i) {
//	//	for (int j = 4; j < 13; ++j) {
//	//		sprintf_s(str, sizeof(str), "marine%03d.bmp", j * 17 + i);
//	//		move_sprite_frame[i * 9 + j] = sprite_cache->spriteFrameByName(str);
//	//	}
//	//}
//
//	// die 애니메이션
//	
//
//	//// attack1 애니메이션
//	//for (int i = 17; i < 34; i += 2) {
//	//	sprintf_s(str, sizeof(str), "marine%03d.bmp", i);
//	//	attack_sprite_frame1[i] = sprite_cache->spriteFrameByName(str);
//	//}
//
//	//// attack2 애니메이션
//	//for (int i = 34; i < 67; i += 2) {
//	//	sprintf_s(str, sizeof(str), "marine%03d.bmp", i);
//	//	attack_sprite_frame2[i] = sprite_cache->spriteFrameByName(str);
//	//}
//
//	return true;
//}
//
////void UnitAnimation::run_action_animation(const float __dt) {
////	_dt += __dt;
////	if (_animation_time > _dt) return;
////	_dt = 0;
////	this->setSpriteFrame(sprite_vector[_frame++]);
////	if (_frame >= _max_frame) {
////		_frame = 0;
////	}
////}
//
//bool UnitAnimation::sprite_flip_x(const bool _b) {
//	if (_b != this->isFlippedX())
//		this->setFlippedX(_b);
//	return _b;
//}
////
////void UnitAnimation::set_animation(const unit_state _unit_state) {
////	switch (_unit_state)
////	{
////	case idle: run_idle_hold_animation(); break;
////	case move: run_move_petrol_animation(); break;
////	case attack: run_attack_animation(); break;
////	case hold: run_idle_hold_animation(); break;
////	case petrol: run_move_petrol_animation(); break;
////	case die: run_die_animation(); break;
////	default:
////		break;
////	}
////}
////
////void UnitAnimation::run_idle_hold_animation() {
////	_frame = 0;
////	_ani_frame = 0;
////	_max_frame = 1;
////	_animation_time = 1.0f / _max_frame;
////}
////
////void UnitAnimation::run_move_petrol_animation() {
////	_frame = 4;
////	_ani_frame = 4;
////	_max_frame = 12;
////	_animation_time = 1.0f / _max_frame;
////}
////
////void UnitAnimation::run_attack_animation() {
////	_frame = 1;
////	_ani_frame = 1;
////	_max_frame = 4;
////	_animation_time = 1.0f / _max_frame;
////}
////
////void UnitAnimation::run_die_animation() {
////	_frame = 0;
////	_ani_frame = 13;
////	_max_frame = 8;
////	_animation_time = 1.0f / _max_frame;
////}
