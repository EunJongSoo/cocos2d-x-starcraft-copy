/****************************
������ : 2018-03-20
�ۼ��� : ������
���ϸ� : Unit.cpp
****************************/

// h���Ͽ��� ���漱���ߴ� Ŭ�������� cpp���Ͽ��� �����ϰ� �ִ�.
#include "Unit.h"
#include "UnitAnimation.h"
#include "UnitWeapon.h"

/*�Ʒ����� �̱��� ������ ����� ����̴�.
�̱��� Ŭ������ ������ �ڵ��ε�, ���ϰ� �� ����ϸ�
���� ������ ���̱� ������ ���� �ʿ��Ҷ��� ����Ѵٰ� �����.
�ڵ�� ���ͳݿ��� ���ؼ� ��� ����̳���.
���ۿ� �˻������� �������� �ִ� �ּ��ϳ� �����.
http://vallista.tistory.com/entry/1-Singleton-Pattern-in-C */
#include "TemplateSingleton.h"
/*���� ����� �ִ� ��Ÿũ����Ʈ���� ���Ǵ� ���ҽ��� �����ϱ� ���ؼ� ������� Ŭ������.
���� ������ �� Ŭ������ ���캼�� ������ ����.*/
#include "ResourcesManager.h"

/*unig namespace�� ����ϸ� namespace�� �����Ҽ� �ִ�.
�� �𸦶��� ������������ �� �ٿ��� ����� �̾߱⸦ �����.
�׷����� �� �Լ����� ��� ������ �˼��ֱ� �����̴�.*/
using namespace cocos2d;

/*���� Ŭ������ �����ڴ�.
������ �������� �⺻������ �����ϸ鼭 �����ǰ� �ִ�.
�տ� ���ߵ� �̿ϼ� �κ��� ���Ƽ� ������ �޾ƿ��°� �ƴϰ�
���� ������ ���� �Է��صξ���.
�ٽú��� init �Լ��� ȣ���Ҷ� �Ű������� �ѱ�� �ƴϰ�
�����ڿ� �Ѱܾ� �����ʳ� �ͱ⵵ �ѵ�.. �Ʒ����� �� ���캸��*/
Unit::Unit() :
	_unit_dir(Direction::up),
	_production_time(0.0f),
	_select_unit(false),
	_player_color(kWhite),
	_races_type(RacesType::terran),
	_unit_state(UnitState::idle),
	_unit_effects(SpecialEffects::none),
	_unit_info(nullptr),
	_unit_info2(nullptr),
	_production_info(nullptr),
	_target_unit(nullptr),
	_unit_animation(nullptr),
	_weapon(nullptr)
{}

/*�Ҹ��ڴ�.
����Ŭ�������� �����Ǵ� �����͵��� �������� ���ְ� �ִ�.
define�� ������������ Header.h ���Ͽ� ���ǵǾ� �ִ�.
������ cocos2d-x���� ����ϴ� ���������� ������
�� �����ߴ��� ��Ծ���.

�ƴºп��� ���� �����ؼ� ����϶�� �̾߱⸦ �� ���Ǹ� �߾����� ����.
�׸��� Unit.h�� ����� ������ ������ 6���ε� ���� 3�����̴�.
������ 3���� ��𰬴��� Ȯ���غ���.

_target_unit, _production_info, _weapon 3���� �����͸� ���������� �����ִµ�
_target_unit�� ���⼭ �����Ҵ��� �ϴ°� �ƴϰ� ��� �ּҰ��� �޾ƴ� ���� ������ �����ʰ�
_production_info�� ������� �ʰ� �־ ���� �ѵ� �Ҿ��ϴ� �߰��صд�.
_weapon�� �����ϴ� ��� ���� �̿ϼ��� �ӽ÷� �ۼ��� �κ��̶� ���밡 Ȯ������ �ʾƼ� �ε��ϴ�.
�ϴ� ������ �ʿ����� ǥ���صΰ� �Ѿ��.*/
Unit::~Unit() {
	// ��� ���� �����Ҵ� ��������
	SAFE_DELETE(_unit_info);
	SAFE_DELETE(_unit_info2);
	SAFE_DELETE(_unit_animation);

	//SAFE_DELETE(_production_info);

}
/*cocos2d-x�� �������� �ִ� Node Ŭ������ �ִ� create �Լ��� �����ε� �ߴ�.
�����ڿ� �Ű������� �ѱ��� �ʰ� init�� �ѱ�� ������ �Ҹ�

�����ڿ� �Ű������� �Ѱܼ� ������ �ʱ�ȭ ���Ѽ� ����ϴ� ���� �� ���� ������?
��� ������ ���� ���.

cocos2d-x�� create �Լ� ����
�Ű������� ������ ������ Ÿ�԰� ��ġ�� �޴´�.*/
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

/*�Ű������� �Ѱܹ޴� init �Լ���.
������ init �Լ��� ������ �Ű������� �ѱ��� �ʴ´�.

������ ������ �ּ��� ���� �ӽ÷� �ۼ��ߴٴ� Ƽ�� ���� �����ִ�.
������ ������ü�� �ǹ����� ������ ������ �����ϸ�
�� ������ �Ѱ� �޾Ƽ� �������ٵ� �մܰ谡 ���� ������ ������ ���� ���Ѵ�.

�׷��� ������ ��� �κ��� ���Ƿ� ���� �ԷµǾ� �ִ�.
�ǹ����� ������ �Ѱ��ִ� �κ��� ��������� �𸦱�
����� ������ �ڷ� �и��� �κ��̴�.

cocos2d-x�� init �Լ� ����
�Ű������� ������ ������ Ÿ�԰� ��ġ�� �޴´�.*/
bool Unit::init(unit_type _type, const cocos2d::Vec2& _vec2, player_color _color) {

	// Ȥ�� ��ӹ޴� Sprite���� ������ ����� �����ϵ��� �߰��� �κ�
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
	this->initWithTexture(resources_manager->load_texture2d(str, _player_color));

	// �ӽ��ۼ�
	// ���� ������ �����Ѵ�.
	_unit_info = new UnitInfo(1, 1, 1, 1, 1, 1, 1, unit_type::marine, UpgradeType::bionic, "marine");
	_unit_info2 = new UnitInfo2(1, 1, 1, 1, 1);

	// �ӽ��ۼ�
	// ���� ������ ���� �޶���
	_unit_info2->move_speed = 2.0f;
	_unit_info2->attack_speed = 0.3f;

	return true;
}

/*�ܼ��ϴ�.
�Լ��� ȣ��Ǹ� ������ ���°��� �������� ����ǰ�
�Ű������� ���� Ÿ���� ��� ������ �����Ѵ�.
�׸��� ���� ������ ��ġ�� Ÿ���� ������ġ�� ������ Ȯ���ؼ�
������ �ٶ󺸴� ������ Ȯ���ϰ� �����Ѵ�.*/

// ���� ���� ���
void Unit::attack_unit(Unit* const _target) {
	// ������ ���� ���¸� �����Ѵ�.
	set_state(UnitState::attack);

	// Ÿ���� �����Ѵ�.
	_target_unit = _target;

	// Ÿ���� ��ġ�� ������ ��ġ�� ���� �����Ѵ�.
	Vec2 vec2 = _target_unit->getPosition() - this->getPosition();
	// ����ȭ �Ѵ�.
	vec2.normalize();
	// ������ Ȯ���Ѵ�.
	check_dir(vec2);
}

/*���⵵ �ܼ�
�ش� �Լ��� ȣ��Ǹ� ���°��� �������ְ� ��ǥ ��ġ���� �־��ش�.
���ֵ��� �ִϸ��̼��� ����ϱ� ���ؼ� ��� ���°��� Ȯ���ϱ� ������
���°��� �ٲ��ָ� ������ �ൿ�� ����ȴ�.
�߰��� �ʿ��� ���� ������ ���� �Ѱ��ش�.*/

// ���� �̵� ���
void Unit::move_unit(const cocos2d::Vec2& _vec2) {
	set_state(UnitState::move);
	_move_vec2 = _vec2;
}

// ���� ���� ���
void Unit::stop_unit() {
	set_state(UnitState::idle);
}

// ���� ��ġ�� �������� �Դٰ��� �̵��ؾ� �Ǳ� ������
// ���� ��ġ�� ���� �������ش�.

// ���� ���� ���
void Unit::patrol_unit(const cocos2d::Vec2& _vec2) {
	set_state(UnitState::patrol);
	_move_vec2 = _vec2;
	_my_pos_vec2 = this->getPosition();
}

// ���� ���� ���
void Unit::hold_unit() {
	set_state(UnitState::hold);
}

// ������ ������ ȣ��
void Unit::die_unit() {
	set_state(UnitState::die);
}

/*������ �ϸ� �� ��󿡰� �ڽ��� ���ݷ��� �Ѱ�����Ѵ�.
���� �ִ� attack_unit �Լ������� �� �κ��� �����Ǿ� �ִ�.
�׷��� �Ʒ��� hit �Լ��� ȣ����� �ʱ� ������ ������ �����ʴ´�
���� ���°��� �ٲٱ� ������ �����ϴ� �ִϸ��̼��� �ϰ��ִ�.*/

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

/*�����Ӹ��� ȣ��Ǵ� �Լ���
��Ÿũ����Ʈ�� 24������ �ϴ���
�ʴ� 24�� ȣ��Ǵ� �Լ���.
�ʿ� �ִ� ��������� �� �Լ��� ȣ��Ǵ� �󸶳� ���� ȣ�������...
AI �κп� ��Ȯ�� �κ��� ���Ƽ� ���� Ʋ�� �����ΰ� �ӽ÷� �ڵ��� �κ��� ����.
�˴� ��� ���ľ� �� �͵�*/

void Unit::run_action_animation(float _dt) {	
	_unit_animation->run_action_aniamtion(_unit_state, _dt, _unit_dir);
	weapon_animaiton(_dt);
	switch (_unit_state)
	{	
	case UnitState::production: 						break;
	case UnitState::idle:								break;
	case UnitState::move:	run_action_move();			break;
	case UnitState::attack: {
			_weapon = new UnitWeapon(_target_unit, unit_type::marine_weapon);
			this->getParent()->addChild(_weapon);
			_bullet_vector.push_back(_weapon);
		break;
	}
	case UnitState::patrol: run_action_move();			break;
	case UnitState::hold: 								break;
	case UnitState::die: _unit_dir = Direction::up;		break;
	default:											break;
	}
	
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

/*������ �����̴� �Լ��̴�.
���������� ������ ������ ���°��� �����Ű��
������ ���ߴٸ� ��ġ�� �����Ѵ�.

cocos2d�� �ִ� Rect�� ����ؼ� �浹üũ�� �ϴµ�
�̹����� ũ��� �ϴٺ��� ���� ���̴� ���ֺ��� �浹üũ ������ �� ũ��
������ ������ �������ϰ� ǥ���Ͽ� ���� �ٷ� Ȯ�εȴ�

������ �߽����� �浹 ������ �����ϵ��� ������ �ʿ��ϴ�.

�浹 �������� �̵��ϴ� �κ��� ���� ��ġ�� ��ǥ��ġ�� ����ȭ�ؼ� �̵��ϴ� ���̴�.
�� �κ��� �̷����ϸ� �̵��� �ȴٴ°� �ٸ������� ���� ������ �Ŷ�
��Ȯ�� ������ �� �𸥴�.
���� ����ȭ�� �ϸ� Vec2 dir�� x,y ���� -1~1 ���̷� ������
�� ������ ������ Ȯ���Ҽ� �ִ�.
�׸��� �� ���⿡ �ӵ��� ���ϰ� ���� ��ġ�� ���ϸ�
�̵��ӵ� ��ŭ �� �������� �̵��ϰ� �Ǵ°��̴�.*/

// �ӽ� �ۼ�, ��� �̰� �ؾߵȴ�.
void Unit::run_action_move() {
	Rect bounding = this->getBoundingBox();
	if (bounding.containsPoint(_move_vec2)) {
		if (_unit_state == UnitState::move) {
			set_state(UnitState::idle);
		}
		/*��Ʈ�� ���¸� ó���ϴ� �κ��̴�.
		��������� ���������� ���� �ٲ����.*/
		else if (_unit_state == UnitState::patrol) {
			std::swap(_move_vec2, _my_pos_vec2);
		}
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

		// ����ȭ�� ���� �̵��ӵ��� ���� �� ���� ��ġ�� ���Ѵ�.
		Vec2 tmp = unit_position + (dir * _unit_info2->move_speed);
		// ��ġ�� �����Ѵ�.
		this->setPosition(tmp);
	}
}

/*����ȭ�� ������ ������ Ȯ���ϴ� �Լ���
������ if���� ��ô ���� ���δ�.
������ ������ �ִٴ� ������ ������
������ ����ϴ� ���Ϳ� ����ȭ�� ���� ������ ��� �ܼ��ϰ� �ڵ��س���.

�� ���� ������ ����Ű�°͵� ���ڸ� �־�� ������� ���� �˰ԵȰ�
���� ������ ���̸� �����ؾ� �� �κ��̴�.*/

// ������ Ȯ���Ѵ�.
void Unit::check_dir(const cocos2d::Vec2 & _dir) {
	// ����ȭ�� ���� �޾ƾ��Ѵ�.

	// y���� 0.33f���� ������ Ȯ���Ѵ�.
	if (_dir.y > up_right_left2) {
		// y���� 0.99f ���� ������ Ȯ���Ѵ�.
		if (_dir.y > up)						_unit_dir = Direction::up;
		// y���� 0.66f ���� ������ Ȯ���Ѵ�.
		else if (_dir.y > up_right_left1) 		_unit_dir = (_dir.x > 0) ? Direction::up_right1 : Direction::up_left1;
		// �������� 0.33f���� ���� 0.66f���� ����.
		else                         			_unit_dir = (_dir.x > 0) ? Direction::up_right2 : Direction::up_left2;
	}
	// y���� -0.33f���� ������ Ȯ���Ѵ�.
	else if (_dir.y > down_right_left1) {
		// y���� 0.1f���� ������ Ȯ���Ѵ�.
		if (_dir.y > up_right_left3)			_unit_dir = (_dir.x > 0) ? Direction::up_right3 : Direction::up_left3;
		// y���� -0.1f ���� ������ Ȯ���Ѵ�.
		else if (_dir.y > right_left)			_unit_dir = (_dir.x > 0) ? Direction::right : Direction::left;
		// �������� -0.33���� ���� -0.1f���� ����.
		else									_unit_dir = (_dir.x > 0) ? Direction::down_right1 : Direction::down_left1;
	}
	// �������� -0.33���� ����.
	else {
		// y���� -0.66f���� ������ Ȯ���Ѵ�.
		if (_dir.y > -down_right_left2)			_unit_dir = (_dir.x > 0) ? Direction::down_right2 : Direction::down_left2;
		// y���� -0.99f���� ������ Ȯ���Ѵ�.
		else if (_dir.y > down_right_left3)		_unit_dir = (_dir.x > 0) ? Direction::down_right3 : Direction::down_left3;
		// �������� -0.99���� ����.
		else                             		_unit_dir = Direction::down;
	}
}

/*���¸� �����ϴ� �Լ�
���¸� �����ϸ鼭 ���� ������ ���� �ʱ�ȭ �ϰ� �ִ�.
�ִϸ��̼� ������ �ٲ� ������ �ʱ�ȭ�� ���� ������ ���ڿ������ų�
�߸��� ���� �����Ͽ� ������ ������ �� �ش� �Լ��� �����ؾ� �Ѵ�.

���¸� ǥ���ϴ� ���� ��ü�� private ������
��� ������ ������ �����ؼ� ������ �����ϴ�
������ ���� ���� �����ϴ� Ŭ������ ����
�ش� Ŭ������ ���ؼ��� ���°��� �����ϵ��� �Ѵٸ� �� �� ĸ��ȭ�� ���� ������ ������
Ŭ���� ������ �ʹ� �þ�°� ��������⵵ �ϴ�

������ set_state �Լ��� ��ġ���ʰ� ������ ���� ���Խ��� ������ ����°ͺ���
�� �����Ұ����� ���δ�.*/

// �������

// ���¸� �����Ѵ�.
void Unit::set_state(const UnitState _state) {
	if (_unit_state != _state) {
		// ���¸� �����Ѵ�.
		_unit_state = _state;
		// �ִϸ��̼� �������� �ʱ�ȭ�Ѵ�.
		_unit_animation->init_frame();
	}
}