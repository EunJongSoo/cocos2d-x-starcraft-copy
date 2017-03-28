#include "UnitAnimation.h"

using namespace cocos2d;

UnitAnimation::UnitAnimation() : frame(0), dt(0.0f) {}
UnitAnimation::~UnitAnimation() {}


void UnitAnimation::run_action_aniamtion(unit_state _state, Sprite* _sprite, float _dt, int _dir, int _frame) {
	switch (_state)
	{
	case move:		clip_aniamtion(move_clip, _sprite, _dt, _dir, _frame);		break;
	case attack:	clip_aniamtion(attack_clip, _sprite, _dt, _dir, _frame);	break;
	case patrol:	clip_aniamtion(move_clip, _sprite, _dt, _dir, _frame);		break;
	case die:		clip_aniamtion(die_clip, _sprite, _dt, _dir, _frame);		break;
	default:		break;
	}
}

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
	for (int ani_count = 0; ani_count <_clip.max_frame; ++ani_count) {
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + ani_count);
		_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
	}
}

void UnitAnimation::init_clip(clip& _clip, char* _str, int _max_frame, int _base, int _ani_count) {
	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
	_clip.max_frame = _max_frame;
	char str[16];
	// 방향 수
	for (int dir = 0; dir < 9; ++dir) {
		// 애니메이션 수
		for (int ani_count = 0; ani_count < _ani_count; ++ani_count) {
			sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + (dir * 2) + (ani_count * 17));
			_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		}
	}
}

void UnitAnimation::init_clip(clip& _clip, char* _str, int _max_frame, int _base, int _ani_count, int _loop, int _num) {
	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
	_clip.max_frame = _max_frame;
	char str[16];

	// 방향 수
	for (int dir = 0; dir < 9; ++dir) {
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, 17 + dir * 2);
		_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, 34 + dir * 2);
		_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		for (int loop = 0; loop < _loop; ++loop) {
			// 애니메이션 수
			for (int ani_count = 0; ani_count < _ani_count; ++ani_count) {
				sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + (dir * 2) + (ani_count * _num));
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