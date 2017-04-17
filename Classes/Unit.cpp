#include "Unit.h"
#include "UnitAnimation.h"
#include "UnitWeapon.h"

#include "TemplateSingleton.h"
#include "ResourcesManager.h"

using namespace cocos2d;

Unit::Unit() :
	_unit_dir(direction::up),
	_production_time(0.0f),
	_select_unit(false),
	_player_color(kWhite),
	_races_type(races_type::terran),
	_unit_state(unit_state::idle),
	_unit_effects(special_effects::none),
	_unit_info(nullptr),
	_unit_info2(nullptr),
	_production_info(nullptr),
	_target_unit(nullptr),
	_unit_animation(nullptr),
	_weapon(nullptr)
{}

Unit::~Unit() {
	// ��� ���� �����Ҵ� ��������
	SAFE_DELETE(_unit_animation);
	SAFE_DELETE(_unit_info);
	SAFE_DELETE(_unit_info2);
}

// cocos2d-x�� create �Լ� ����
// �Ű������� ������ ������ Ÿ�԰� ��ġ�� �޴´�.
Unit * Unit::create(const unit_type _type, const cocos2d::Vec2& _vec2, player_color _color) {
	Unit * pRet = new Unit();
	if (pRet && pRet->init(_type, _vec2, _color)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		return (pRet = nullptr);
	}
}

// cocos2d-x�� init �Լ� ����
// �Ű������� ������ ������ Ÿ�԰� ��ġ�� �޴´�.
bool Unit::init(unit_type _type, const cocos2d::Vec2& _vec2, player_color _color) {
	assert(Sprite::init());

	// ���� ���� ����
	_player_color = _color;

	// ���� �ִϸ��̼� ����
	_unit_animation = new UnitAnimation(_type, _player_color, this);
	this->setPosition(_vec2);

	// ������ �ε� ~~~~~~
	// ������ �ε� ~~~~~~
	// ������ �ε� ~~~~~~
	// ������ �ε� ~~~~~~
	// ������ �ε� ~~~~~~


	auto resources_manager = TemplateSingleton<ResourcesManager>::get_instance();

	// �ӽ��ۼ�
	// ������ �̹����� �ʱ�ȭ�Ѵ�.
	char str[16] = { 0, };
	sprintf_s(str, sizeof(str), "marine0016.bmp");
	auto sprite_cache = SpriteFrameCache::getInstance();
	this->initWithTexture(resources_manager->load_resources(_player_color, str));

	// �ӽ��ۼ�
	// ���� ������ �����Ѵ�.
	_unit_info = new unit_info(1, 1, 1, 1, 1, 1, 1, unit_type::marine, upgrade_type::bionic, "marine");
	_unit_info2 = new unit_info2(1, 1, 1, 1, 1);

	// �ӽ��ۼ�
	// ���� ������ ���� �޶���
	_unit_info2->move_speed = 2.0f;
	_unit_info2->attack_speed = 0.3f;
	
	return true;
}

// ���� ���� ���
void Unit::attack_unit(Unit* const _target) {
	// ������ ���� ���¸� �����Ѵ�.
	set_state(unit_state::attack);
	
	// Ÿ���� �����Ѵ�.
	_target_unit = _target;

	// Ÿ���� ��ġ�� ������ ��ġ�� ���� �����Ѵ�.
	Vec2 vec2 = _target_unit->getPosition() - this->getPosition();
	// ����ȭ �Ѵ�.
	vec2.normalize();
	// ������ Ȯ���Ѵ�.
	check_dir(vec2);
}

// ���� �̵� ���
void Unit::move_unit(const cocos2d::Vec2& _vec2) {
	set_state(unit_state::move);
	_move_vec2 = _vec2;
}

// ���� ���� ���
void Unit::stop_unit() {
	set_state(unit_state::idle);
}

// ���� ���� ���
void Unit::patrol_unit(const cocos2d::Vec2& _vec2) {
	set_state(unit_state::patrol);
	_move_vec2 = _vec2;
	_my_pos_vec2 = this->getPosition();
}

// ���� ���� ���
void Unit::hold_unit() {
	set_state(unit_state::hold);
}

// ������ ������ ȣ��
void Unit::die_unit() {
	set_state(unit_state::die);
}

// ���� ���Ҷ� ȣ��ȴ�.
void Unit::hit(int _dmg) {
	// ���ݷ¿��� ������ ����.
	int dmg = _dmg - _unit_info->defence;
	// ���ݷ��� 0�����̸� 1�� �����.
	if (dmg <= 0)
		dmg = 1;
	// ������ ��ŭ ü���� ��´�.
	_unit_info->hp -= dmg;

	// ü���� 0�������� Ȯ���Ѵ�.
	int hp = _unit_info->hp;
	if (hp <= 0) {
		// ü���� 0���� �����.
		_unit_info->hp = 0;
		// ������ �״´�.
		die_unit();
	}
}

void Unit::run_action_animation(float _dt) {
	// ��ó���� �ٸ� ������..
	// unit_animation->run_action_aniamtion(unit_state, this, _dt, unit_dir);

	switch (_unit_state)
	{
	case production: 		break;
	case idle:				break;
	case move:
		run_action_move();														// �̵�ó��
		_unit_animation->run_action_aniamtion(move, this, _dt, _unit_dir);		// �ִϸ��̼� ó��
		break;
	case attack: {
		_unit_animation->run_action_aniamtion(attack, this, _dt, _unit_dir, 2);	// �ִϸ��̼� ó��		
		{																		// ���� �����ʿ��ѵ�..
			_weapon = new UnitWeapon(_target_unit, unit_type::marine_weapon);
			this->getParent()->addChild(_weapon);
			_bullet_vector.push_back(_weapon);
		}
		break;
	}
	case patrol: {
		run_action_move();														// �̵�ó��, ��� �̰� �ؾߵ�
		if (_unit_state == idle) {
			_unit_state = patrol;
			std::swap(_move_vec2, _my_pos_vec2);
		}
		_unit_animation->run_action_aniamtion(move, this, _dt, _unit_dir);		// �ִϸ��̼� ó��
		break;
	}
	case hold: 		break;
	case die: 		_unit_animation->run_action_aniamtion(die, this, _dt); 		break;
	default:
		break;
	}
	weapon_animaiton(_dt);
}

// �ӽ� �ۼ�, ��� �̰� �ؾߵ�
void Unit::weapon_animaiton(float _dt) {
	
	for (UnitWeapon* weapon : _bullet_vector) {
		weapon->run_action_animation(_dt);
	}
	int i = 0, j = -1;
	for (UnitWeapon* weapon : _bullet_vector) {
		if (!weapon->isVisible()) {
			j = i;
		}
		++i;
	}
	if (j != -1) {
		this->getParent()->removeChild(_bullet_vector.at(j));
		delete _bullet_vector.at(j);
		_bullet_vector.erase(_bullet_vector.begin() + j);
	}
}

// �ӽ� �ۼ�, ��� �̰� �ؾߵȴ�.
void Unit::run_action_move() {
	Rect bounding = this->getBoundingBox();
	if (bounding.containsPoint(_move_vec2)) {
		_unit_state = idle;
	}
	else {
		// ���� ���� ��ġ�� ����
		Vec2 unit_position = this->getPosition();
		// ��ǥ ��ġ���� ���� ��ġ�� ����
		Vec2 dir = _move_vec2 - unit_position;
		// ������� ����ȭ�Ѵ�.
		dir.normalize();
		// ����ȭ �� ������ Ȯ���Ѵ�.
		check_dir(dir);

		// ���⿡ �̵��ӵ��� ���� �� ���� ��ġ�� ���Ѵ�.
		Vec2 tmp = unit_position + (dir * _unit_info2->move_speed);
		// ��ġ�� �����Ѵ�.
		this->setPosition(tmp);
	}
}

// ������ Ȯ���Ѵ�.
void Unit::check_dir(const cocos2d::Vec2 & _dir) {
	// ����ȭ�� ���� �޾ƾ��Ѵ�.

	// y���� 0.33f���� ������ Ȯ���Ѵ�.
	if (_dir.y > up_right_left2) {
		// y���� 0.99f ���� ������ Ȯ���Ѵ�.
		if (_dir.y > up)						_unit_dir = direction::up;
		// y���� 0.66f ���� ������ Ȯ���Ѵ�.
		else if (_dir.y > up_right_left1) 		_unit_dir = (_dir.x > 0) ? direction::up_right1 : direction::up_left1;
		// �������� 0.33f���� ���� 0.66f���� ����.
		else                         			_unit_dir = (_dir.x > 0) ? direction::up_right2 : direction::up_left2;
	}
	// y���� -0.33f���� ������ Ȯ���Ѵ�.
	else if (_dir.y > down_right_left1) {
		// y���� 0.1f���� ������ Ȯ���Ѵ�.
		if (_dir.y > up_right_left3)			_unit_dir = (_dir.x > 0) ? direction::up_right3 : direction::up_left3;
		// y���� -0.1f ���� ������ Ȯ���Ѵ�.
		else if (_dir.y > right_left)			_unit_dir = (_dir.x > 0) ? direction::right : direction::left;
		// �������� -0.33���� ���� -0.1f���� ����.
		else									_unit_dir = (_dir.x > 0) ? direction::down_right1 : direction::down_left1;
	}
	// �������� -0.33���� ����.
	else {
		// y���� -0.66f���� ������ Ȯ���Ѵ�.
		if (_dir.y > -down_right_left2)			_unit_dir = (_dir.x > 0) ? direction::down_right2 : direction::down_left2;
		// y���� -0.99f���� ������ Ȯ���Ѵ�.
		else if (_dir.y > down_right_left3)		_unit_dir = (_dir.x > 0) ? direction::down_right3 : direction::down_left3;
		// �������� -0.99���� ����.
		else                             		_unit_dir = direction::down;
	}
}

// ���¸� �����Ѵ�.
void Unit::set_state(const unit_state _state) {
	// �ִϸ��̼� �������� �ʱ�ȭ�Ѵ�.
	_unit_animation->init_frame();
	// ���¸� �����Ѵ�.
	_unit_state = _state;
}
