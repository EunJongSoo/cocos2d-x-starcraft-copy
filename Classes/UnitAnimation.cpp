#include <string>
#include "UnitAnimation.h"

using namespace cocos2d;
using std::string;

UnitAnimation::UnitAnimation() : _frame(0), _max_frame(0), _animation_time(0.5), _dt(0.0f) {
}

UnitAnimation::~UnitAnimation() {
}

bool UnitAnimation::init() {
	
	assert(Sprite::init());
	//// move 애니메이션
	//for (int i = 0; i < 9; ++i) {
	//	for (int j = 4; j < 13; ++j) {
	//		sprintf_s(str, sizeof(str), "marine%03d.bmp", j * 17 + i);
	//		move_sprite_frame[i * 9 + j] = sprite_cache->spriteFrameByName(str);
	//	}
	//}

	// die 애니메이션
	

	//// attack1 애니메이션
	//for (int i = 17; i < 34; i += 2) {
	//	sprintf_s(str, sizeof(str), "marine%03d.bmp", i);
	//	attack_sprite_frame1[i] = sprite_cache->spriteFrameByName(str);
	//}

	//// attack2 애니메이션
	//for (int i = 34; i < 67; i += 2) {
	//	sprintf_s(str, sizeof(str), "marine%03d.bmp", i);
	//	attack_sprite_frame2[i] = sprite_cache->spriteFrameByName(str);
	//}

	return true;
}

//void UnitAnimation::run_action_animation(const float __dt) {
//	_dt += __dt;
//	if (_animation_time > _dt) return;
//	_dt = 0;
//	this->setSpriteFrame(sprite_vector[_frame++]);
//	if (_frame >= _max_frame) {
//		_frame = 0;
//	}
//}

bool UnitAnimation::sprite_flip_x(const bool _b) {
	if (_b != this->isFlippedX())
		this->setFlippedX(_b);
	return _b;
}
//
//void UnitAnimation::set_animation(const unit_state _unit_state) {
//	switch (_unit_state)
//	{
//	case idle: run_idle_hold_animation(); break;
//	case move: run_move_petrol_animation(); break;
//	case attack: run_attack_animation(); break;
//	case hold: run_idle_hold_animation(); break;
//	case petrol: run_move_petrol_animation(); break;
//	case die: run_die_animation(); break;
//	default:
//		break;
//	}
//}
//
//void UnitAnimation::run_idle_hold_animation() {
//	_frame = 0;
//	_ani_frame = 0;
//	_max_frame = 1;
//	_animation_time = 1.0f / _max_frame;
//}
//
//void UnitAnimation::run_move_petrol_animation() {
//	_frame = 4;
//	_ani_frame = 4;
//	_max_frame = 12;
//	_animation_time = 1.0f / _max_frame;
//}
//
//void UnitAnimation::run_attack_animation() {
//	_frame = 1;
//	_ani_frame = 1;
//	_max_frame = 4;
//	_animation_time = 1.0f / _max_frame;
//}
//
//void UnitAnimation::run_die_animation() {
//	_frame = 0;
//	_ani_frame = 13;
//	_max_frame = 8;
//	_animation_time = 1.0f / _max_frame;
//}
