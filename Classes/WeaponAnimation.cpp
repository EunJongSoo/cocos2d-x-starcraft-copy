#include "WeaponAnimation.h"

WeaponAnimation::WeaponAnimation(unit_type _type) : frame(0), dt(0.0f) {
	init_unit_animation(_type);
}

WeaponAnimation::~WeaponAnimation() {
}

void WeaponAnimation::run_action_aniamtion(cocos2d::Sprite* const _sprite, const float _dt, const int _dir, const int _frame) {
	_sprite->setSpriteFrame(bullet_clip.animation_vector[frame++]);
	if (frame >= bullet_clip.max_frame) {
		_sprite->setVisible(false);
	}
}

void WeaponAnimation::init_frame() {

}

void WeaponAnimation::init_unit_animation(const unit_type _type) {
	// 데이터 로드~

	init_animation();


	

}

void WeaponAnimation::init_animation(const char* const _str, const int _max_frame, const int _base) {
	init_clip(bullet_clip, _str, _max_frame, _base);
}

void WeaponAnimation::init_clip(clip& _clip, const char* _str, const int _max_frame, const int _base) {
	auto sprite_cache = cocos2d::SpriteFrameCache::getInstance();
	_clip.max_frame = _max_frame;
	char str[16];
	// 모션 수
	for (int ani_count = 0; ani_count <_clip.max_frame; ++ani_count) {
		sprintf_s(str, sizeof(str), "%s%03d.bmp", _str, _base + ani_count);
		_clip.animation_vector.push_back(sprite_cache->spriteFrameByName(str));
	}
}