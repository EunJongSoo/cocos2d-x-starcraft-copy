#include "UnitAnimation.h"

using namespace cocos2d;

UnitAnimation::UnitAnimation(const unit_type _type) : frame(0), dt(0.0f) {
	init_unit_animation(_type);
}

UnitAnimation::~UnitAnimation() {}

void UnitAnimation::init_unit_animation(const unit_type _type) {
	// 데이터 불러오는 부분
	//dataload(_type);
	/*char str[16];
	int i;
	int j;
	int k;*/

	// 불러온 데이터로 세팅
	//this->init_animation(move, str, i, j, k);

	this->init_animation(move, "marine", 9, 68, 9);
	this->init_animation(attack, "marine", 8, 51, 2, 3, -17);
	this->init_animation(die, "marine", 8, 221);
}

void UnitAnimation::run_action_aniamtion(const unit_state _state, Sprite* const _sprite, const float _dt, const int _dir = 0, const int _frame = 0) {
	switch (_state)
	{
	case move:		clip_aniamtion(move_clip, _sprite, _dt, _dir, _frame);		break;
	case attack:	clip_aniamtion(attack_clip, _sprite, _dt, _dir, _frame);	break;
	case patrol:	clip_aniamtion(move_clip, _sprite, _dt, _dir, _frame);		break;
	case die:		clip_aniamtion(die_clip, _sprite, _dt, _dir, _frame);		break;
	default:		break;
	}
}

void UnitAnimation::init_frame() {
	frame = 0;
	dt = 0;
}

void UnitAnimation::init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base) {
	switch (_state)
	{
	case move: 		init_clip(move_clip, _str, _max_frame, _base);		break;
	case attack:	init_clip(attack_clip, _str, _max_frame, _base);	break;
	case die:		init_clip(die_clip, _str, _max_frame, _base);		break;
	default:	break;
	}
}

void UnitAnimation::init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base, const int _ani_count) {
	switch (_state)
	{
	case move:		init_clip(move_clip, _str, _max_frame, _base, _ani_count);		break;
	case attack:	init_clip(attack_clip, _str, _max_frame, _base, _ani_count);	break;
	case die:		init_clip(die_clip, _str, _max_frame, _base, _ani_count);		break;
	default:		break;
	}
}

void UnitAnimation::init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num) {
	switch (_state)
	{
	case move:		init_clip(move_clip, _str, _max_frame, _base, _ani_count, _loop, _num);		break;
	case attack:	init_clip(attack_clip, _str, _max_frame, _base, _ani_count, _loop, _num);	break;
	case die:		init_clip(die_clip, _str, _max_frame, _base, _ani_count, _loop, _num);		break;
	default:		break;
	}
}

void UnitAnimation::sprite_flipped_x(Sprite* const _sprite, const bool _is_left, const bool _is_flipped_x) {
	if (_is_left != _is_flipped_x) {
		_sprite->setFlippedX(_is_left);
	}
}

void UnitAnimation::init_clip(clip& _clip, const char* _str, const int _max_frame, const int _base) {
	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
	_clip.max_frame = _max_frame;
	char str[16];
	// 모션 수
	for (int ani_count = 0; ani_count <_clip.max_frame; ++ani_count) {
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + ani_count);
		_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
	}
}

void UnitAnimation::init_clip(clip& _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count) {
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

void UnitAnimation::init_clip(clip& _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num) {
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

void UnitAnimation::clip_aniamtion(const clip& _clip, Sprite* const _sprite, const float _dt, const int _dir, const int _frame) {
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