#include "UnitAnimation.h"

using namespace cocos2d;

UnitAnimation::UnitAnimation(const unit_type _type, Sprite* const _sprite) : frame(0), dt(0.0f) {
	this->init_unit_animation(_type, _sprite);
}

UnitAnimation::~UnitAnimation() {}

void UnitAnimation::init_unit_animation(const unit_type _type, Sprite* const _sprite) {
	// 데이터 불러오는 부분
	//dataload(_type);
	/*char str[16];
	int i;
	int j;
	int k;*/

	// 불러온 데이터로 세팅
	//this->init_animation(move, str, i, j, k);

	switch (_type)
	{
	case marine: {
		this->init_animation(move, "marine", 9, 68, 9);
		this->init_animation(attack, "marine", 8, 51, 2, 3, -17);
		this->init_animation(die, "marine", 8, 221);
		break;
	}
	case marine_weapon: {
		this->init_animation(idle, "tspark", 10, 0);
		for (clip* _clip : clip_vector) {
			if (_clip->state == idle) {
				_sprite->initWithSpriteFrame(_clip->animation_vector[0]);
			}
		}
	}
	default:
		break;
	}
	
}

bool UnitAnimation::run_action_aniamtion(const unit_state _state, Sprite* const _sprite, const float _dt, const int _dir, const int _frame) {
	for (clip* _clip : clip_vector) {
		if (_clip->state == _state) {
			return clip_aniamtion(_clip, _sprite, _dt, _dir, _frame);
		}
	}

}

void UnitAnimation::init_frame() {
	frame = 0;
	dt = 0;
}

void UnitAnimation::init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base) {
	init_clip(create_clip(_state), _str, _max_frame, _base);
}

void UnitAnimation::init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base, const int _ani_count) {
	init_clip(create_clip(_state), _str, _max_frame, _base, _ani_count);
}

void UnitAnimation::init_animation(const unit_state _state, const char* const _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num) {
	init_clip(create_clip(_state), _str, _max_frame, _base, _ani_count, _loop, _num);
}

void UnitAnimation::sprite_flipped_x(Sprite* const _sprite, const bool _is_left, const bool _is_flipped_x) {
	if (_is_left != _is_flipped_x) {
		_sprite->setFlippedX(_is_left);
	}
}

UnitAnimation::clip * UnitAnimation::create_clip(const unit_state _state)
{
	clip* _clip = new clip();
	_clip->state = _state;
	clip_vector.push_back(_clip);
	return _clip;
}

void UnitAnimation::init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base) {
	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
	_clip->max_frame = _max_frame;
	char str[16];
	// 모션 수
	for (int ani_count = 0; ani_count <_clip->max_frame; ++ani_count) {
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + ani_count);
		_clip->animation_vector.push_back(sprite_cache->spriteFrameByName(str));
	}
}

void UnitAnimation::init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count) {
	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
	_clip->max_frame = _max_frame;
	char str[16];
	// 방향 수
	for (int dir = 0; dir < 9; ++dir) {
		// 애니메이션 수
		for (int ani_count = 0; ani_count < _ani_count; ++ani_count) {
			sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + (dir * 2) + (ani_count * 17));
			_clip->animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		}
	}
}

void UnitAnimation::init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num) {
	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
	_clip->max_frame = _max_frame;
	char str[16];

	// 방향 수
	for (int dir = 0; dir < 9; ++dir) {
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, 17 + dir * 2);
		_clip->animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, 34 + dir * 2);
		_clip->animation_vector.push_back(sprite_cache->spriteFrameByName(str));
		for (int loop = 0; loop < _loop; ++loop) {
			// 애니메이션 수
			for (int ani_count = 0; ani_count < _ani_count; ++ani_count) {
				sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + (dir * 2) + (ani_count * _num));
				_clip->animation_vector.push_back(sprite_cache->spriteFrameByName(str));
			}
		}
	}
}

bool UnitAnimation::clip_aniamtion(const clip* const _clip, Sprite* const _sprite, const float _dt, const int _dir, const int _frame) {
	dt += _dt;
	if (0.05f > dt) return false;
	dt = 0;

	bool is_left = _dir > left_check;
	int tmp_dir = is_left ? _dir - 10 : _dir;
	sprite_flipped_x(_sprite, is_left, _sprite->isFlippedX());
	
	_sprite->setSpriteFrame(_clip->animation_vector[frame++ + tmp_dir * _clip->max_frame]);
	bool b = frame >= _clip->max_frame;
	if (b) {
		frame = _frame;
	}
	return b;
}