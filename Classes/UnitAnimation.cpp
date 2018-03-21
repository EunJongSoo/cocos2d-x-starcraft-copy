/****************************
������ : 2018-03-20
�ۼ��� : ������
���ϸ� : UnitAnimation.cpp
****************************/

#include "UnitAnimation.h"
#include "TemplateSingleton.h"
#include "ResourcesManager.h"

using namespace cocos2d;

/* ���� �ִϸ��̼��� ������
��� ������ �ʱ�ȭ�� �ʱ�ȭ �Լ��� ȣ���Ѵ�.
������ ���� �ʾ������� ������������ ���� ���ӿ��� ������ ������ ������
�ǹ̰� �������� �ִ�.*/
UnitAnimation::UnitAnimation(const unit_type _type, cocos2d::Sprite * const _sprite):
	frame(0),
	dt(0.0f),
	color(player_color::none),
	unit_sprite(_sprite)
{
	this->init_unit_animation(_type);
}

/* ���� ������ ������ �޴� ���� �ٸ���*/
UnitAnimation::UnitAnimation(const unit_type _type, player_color _color, Sprite* const _sprite) :
	frame(0), 
	dt(0.0f),
	color(_color),
	unit_sprite(_sprite)
{
	this->init_unit_animation(_type);
}

/* ������� ���� �Ǵ� ����Ʈ�� �Ҹ��ϸ� �����Ҵ��� Ŭ���� ���� �����ش�.*/
UnitAnimation::~UnitAnimation() {
	for (clip* _clip : clip_vector) {
		SAFE_DELETE(_clip);
	}
	clip_vector.clear();
}

/* ���� �ִϸ��̼��� �ʱ�ȭ�ϴ� �Լ���.
�̿ϼ� �κ��̴� �����͸� �ҷ����� �κ��� ���� �ԷµǾ� �ִµ�
���ֺ��� ������ ������ ���� �ҷ��� ü�踦 �����صǴ� �κ��̴�.

������ ������ �̹����� ����߱� ������ ������ ���, �̵�, ����, �׾������� ���� ����Ʈ
�ִϸ��̼� Ŭ���� �ʱ�ȭ ��Ű�� �ִ�.*/
void UnitAnimation::init_unit_animation(const unit_type _type) {
	// ������ �ҷ����� �κ�
	//dataload(_type);
	/*char str[16];
	int i;
	int j;
	int k;*/

	// �ҷ��� �����ͷ� ����
	//this->init_animation(move, str, i, j, k);

	switch (_type)
	{
	case marine: {
		this->init_clip(create_clip(UnitState::idle), "marine", 1, 0, 1);
		this->init_clip(create_clip(UnitState::move), "marine", 9, 68, 9);
		this->init_clip(create_clip(UnitState::attack), "marine", 8, 51, 2, 3, -17);
		this->init_clip(create_clip(UnitState::die), "marine", 8, 221);
		break;
	}
	case marine_weapon: {
		this->init_clip(create_clip(UnitState::idle), "tspark", 15, 0);
	}
	default:
		break;
	}
	
}

/* Ŭ�� ���Ϳ��� �Ű������� ���� ������ Ŭ���� ã�� 
ã�Ƽ� run_clip_aniamtion�� �ð��� ���� ������ ���� �ѱ�µ�
�⺻�� 0 �������̴�.

�׷��� ������ �����Ҷ��� 2��� �������� ������.
ó�� ����Ҷ��� 0 �����Ӻ��� ����� ��Ű����
�� �������ʹ� 2�����Ӻ��� �����Ű�� �ϱ� ���ؼ� 2��� ���ڸ� �����ش�.

�Ű������� �ѱ�� �κ��� ���� Ŭ�����̱� ������ ���� �������� �����ε�
���� ����� ��� ���������� ó���� �κ��̴�.

case UnitState::attack: {
_unit_animation->run_action_aniamtion(UnitState::attack, _dt, _unit_dir, 2);

���� Ŭ������ ���� ó�� �κ��� ���� ���� �������� 2��� 
���� �Է��� ���ڰ� ���̴µ� �߸��Ǿ���.

��𼱰� �����͸� ������� �ؼ� ���ֺ��� ����ǵ��� �ؾߵ� �κ��̸�
���� �ִϸ��̼� ������ �������� �� �κ��̴�

������ �ʿ��ѵ� ���� ���ֺ� �����͸� ������ �κ��� �۾����� �ʾ�
���������� �ڷ� �и���.
*/
bool UnitAnimation::run_action_aniamtion(UnitState _state, const float _dt, const int _dir) {
	int frame = 0;
	
	if (_state == UnitState::attack) {
		frame = 2;
	}
	else if (_state == UnitState::patrol) {
		_state = UnitState::move;
	}

	for (clip* _clip : clip_vector) {
		if (_clip->state == _state) {
			return run_clip_aniamtion(_clip, _dt, _dir, frame);
		}
	}
}

/* �����Ӱ� �ð��� 0���� �ʱ�ȭ �Ѵ�.
�ִϸ��̼��� ���°� ����ɶ� ȣ��ǰ� �ִ�.
*/
void UnitAnimation::init_frame() {
	frame = 0;
	dt = 0;
}

/* �̹����� ���� ��Ű�� �Լ���
���ڽ��� Sprite���� �����Ǵ� ����̴�.
�Ű������� �������� Ȯ���ϰ� ���� �̹����� �¿��������� Ȯ���Ѵ�.

�⺻ �̹����� �����ʸ� �ֱ� ������ �¿������ ���� �ʾҴٸ� ������ �̹����̸�
������ �̹����� �¿������ ���� �ʾұ� ������ false�� ��ȯ�ȴ�

�׸��� ������ true�� ��� ���� �ٸ��� ������ �¿� ������ ���Ѽ�
�̹����� �����̹����� �ٲ۴�.
*/
void UnitAnimation::flipped_sprite_x(const bool _is_left) {
	if (_is_left != unit_sprite->isFlippedX()) {
		unit_sprite->setFlippedX(_is_left);
	}
}

/* Ŭ���� ����� Ŭ�� ���Ϳ� �־��ش�.
������� Ŭ���� �ʱ�ȭ ������� �ϱ� ������ ��ȯ���ش�.*/
UnitAnimation::clip * UnitAnimation::create_clip(const UnitState _state)
{
	clip* _clip = new clip();
	_clip->state = _state;
	clip_vector.push_back(_clip);
	return _clip;
}

/* Ŭ���� �ʱ�ȭ ���ش�.
�ִϸ��̼ǿ� ���� Ŭ���� �ʱ�ȭ �ϴ� ����� �ٸ���
��Ȯ�ϰԴ� ������ �̹����� ������ ���缭 �ʱ�ȭ �ϴ� ����� �ٸ���

Ŭ���� �� �ִϸ��̼��� ������� ��� �����
������ ��Ÿũ����Ʈ���� ������ �̹����� �ִϸ��̼� ���� ���ĵǾ� ���� �ʰ�
�� ������ �̹����� ���ĵ� ��Ģ��� �ҷ��ͼ� Ŭ���� �����ϰ� �ִ�.

������ ���� 0~16�� �̹����� ��� ��� �̹�����.
�׷��� ������ �ð�������� �Ʒ��ʱ��� 9������ �̹����� �����Ǵµ�
�Ʒ����� ����� ��� 2�徿�̸� �� �Ʒ��� ������ ������ 7������ �¿� ���� ��Ű��
�� 16������ �ٶ󺸴� ���� �̹����� ���´�

��¶�� 17���� ���⸸ �ٸ� ���� �׸��̰�
�̰� �ִϸ��̼����� ������� 17�徿 �ǳʶ�鼭 Ŭ���� �����ؾ� �ȴ�.

�׷��� ���� ����̳� �״� ����� �� �ٸ���.
�ؼ� �� �� �ִϸ��̼ǿ� �°� Ŭ���� �ҷ����� ����� ���� 3���� ���������.

����� Ŭ���� ���� �ִϸ��̼ǿ��� ���� �ʱ�ȭ �Ѵ�.
�׷��� �� Ŭ���� ������ ����� �������� ���������
�Ȱ����� ��� ����ϱ� ���� �ȴ�.

�ƹ����� Ŭ���� ���ҽ� �Ŵ����� �Ѱܹ�����
������ ��������� ���ҽ� �Ŵ����� Ŭ���� �ҷ��ͼ� ����ϵ��� �����߰ڴ�.
*/
void UnitAnimation::init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base) {
	cocos2d::Texture2D* texture = nullptr;
	_clip->max_frame = _max_frame;
	char str[16];
	// ��� ��
	for (int ani_count = 0; ani_count < _max_frame; ++ani_count) {
		sprintf_s(str, sizeof(str), "%s%04d.bmp", _str, _base + ani_count);
		assert(texture = load_texture(str, color));
		add_texture(_clip, texture);
	}
}

void UnitAnimation::init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count) {
	cocos2d::Texture2D* texture = nullptr;
	_clip->max_frame = _max_frame;
	char str[16];
	// ���� ��
	for (int dir = 0; dir < 9; ++dir) {
		int dir2 = dir * 2;
		// �ִϸ��̼� ��
		for (int ani_count = 0; ani_count < _ani_count; ++ani_count) {
			sprintf_s(str, sizeof(str), "%s%04d.bmp", _str, _base + dir2 + (ani_count * 17));
			assert(texture = load_texture(str, color));
			add_texture(_clip, texture);
		}
	}
}

void UnitAnimation::init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num) {
	_clip->max_frame = _max_frame;
	char str[16];
	cocos2d::Texture2D* texture = nullptr;
	// ���� ��
	for (int dir = 0; dir < 9; ++dir) {
		int dir2 = dir * 2;
		int img_num1 = dir2 + 17;
		int img_num2 = dir2 + 34;
		sprintf_s(str, sizeof(str), "%s%04d.bmp", _str, img_num1);
		assert(texture = load_texture(str, color));
		add_texture(_clip, texture);
		sprintf_s(str, sizeof(str), "%s%04d.bmp", _str, img_num2);
		assert(texture = load_texture(str, color));
		add_texture(_clip, texture);
		for (int loop = 0; loop < _loop; ++loop) {
			// �ִϸ��̼� ��
			for (int ani_count = 0; ani_count < _ani_count; ++ani_count) {
				sprintf_s(str, sizeof(str), "%s%04d.bmp", _str, _base + dir2 + (ani_count * _num));
				assert(texture = load_texture(str, color));
				add_texture(_clip, texture);
			}
		}
	}
}

/* Ŭ������ ������� �̹����� �����ϴ� �Լ���.
�� �Լ��� ȣ���ϴ� run_action_aniamtion���� ������ ���¸� ���� Ȯ���ؼ�
�� ������ Ŭ���� �Ű������� �ѱ��.

�Լ��� �ѹ� ȣ��ɶ����� �ð��� ���ϴµ� 0.03�ʴ� ���ٸ� ���ؾ��� ���� ���ڶ� �ӽ����̴�
������ Header.h ���Ͽ� enum���� ���ǵǾ� �ִ�.

enum���� ���ǵ� ���ڸ� ���� up, down, right�� 10 ���� �۰�, left�� 10���� ũ��
�׷��� ������ �Ű������� ���� _dir�� 10���� ũ�� ���� 10���� ������ �������̴�.

�̷��� ������ Ȯ���� ������ _dir���� 10�� ���ִ� ������ 
�̹����� ������ �̹��� ���̱� �����̴�.

�̰� Ŭ���� �̹����� ���̴� ������ ���� �˾ƾ� �ϴµ�
���� ���� �ִϸ��̼��� ������� �׿��ִ�.

���� ��� 1~9���� ���� �ȴ� �ִϸ��̼� 10~18���� ���������� �ȴ� �ִϸ��̼� 
19~27���� �Ʒ��� �ȴ� �ִϸ��̼��ΰŴ�

�׸��� �������� �ȴ� �ִϸ��̼��� ����
���������� �ȴ� �ִϸ��̼��� �ҷ�����
Unit Sprite�� ���� ���ѹ�����.

now_frame�� ���� frame�� ����, �׸��� �ش� Ŭ�� �ִϸ��̼��� �ִ� �������� ���Ѵ�.
���� ��� 2���� �迭�� 1���� �迭�� ����� �����ϴ°Ͱ� ���� ����̴�.

�׸��� ���� �������� �ִ� ������(������ �ִϸ��̼�)�̸� 
�Ű������� ���� ������ ����� �������� ������ �ʱ�ȭ �ؼ� �ݺ��Ѵ�.

�� �κ��� �ٸ� �ִϸ��̼��� �� 0�ε� 
������ ������ �ݺ��Ҷ� 2~3�� �ִϸ��̼Ǹ� �ݺ��ؼ� �ۼ��Ǿ���.*/
bool UnitAnimation::run_clip_aniamtion(const clip* const _clip, const float _dt, const int _dir, const int _frame) {
	dt += _dt;
	if (0.03f > dt) return false;
	dt = 0;

	bool is_left = _dir > Direction::left_check;
	int tmp_dir = is_left ? _dir - 10 : _dir;
	flipped_sprite_x(is_left);
	
	int now_frame = frame++ + tmp_dir * _clip->max_frame;

	unit_sprite->setTexture(_clip->animation_vector[now_frame]);
	bool b = frame >= _clip->max_frame;
	if (b) {
		frame = _frame;
	}
	return b;
}

/* Sprite�� �̹����� �����Ҷ� ����ϴ� Texture2D�� ���ҽ� �Ŵ������� �ҷ��´�.
�ڼ��Ѱ� ���ҽ� �Ŵ��� �ڵ带 ���� ������ ����*/
cocos2d::Texture2D * UnitAnimation::load_texture(const char * const _str, const player_color _color)
{
	auto resources_manager = TemplateSingleton<ResourcesManager>::get_instance();
	return resources_manager->load_texture2d(_str, _color);
}

/* Ŭ���� �ؽ��ĸ� �߰��Ѵ�.*/
void UnitAnimation::add_texture(clip* const _clip, cocos2d::Texture2D* const _texture)
{
	_clip->animation_vector.push_back(_texture);
}
