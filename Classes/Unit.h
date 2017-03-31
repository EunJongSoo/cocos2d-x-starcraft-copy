#ifndef UNIT_H_
#define UNIT_H_

#include "cocos2d.h"
#include "header.h"

class UnitWeapon;
class UnitAnimation;

//enum upgrade_type;
//enum special_effects;
//enum races_type;
//struct unit_info;
//struct unit_info2;
//struct production_info;

class Unit :public cocos2d::Sprite {
public:
	enum upgrade_type {
		bionic, mechanic, air_force
	};
	enum races_type {
		terran,
	};
	enum unit_size_type {
		small_unit, medium_unit, large_unit, building
	};
	enum special_effects {
		none, clockking,
	};
	struct unit_info {
		unit_info(int _hp, int _mp, int _shield, int _attack,
			int _defence, int _attack_lv, int _defence_lv, unit_type _unit_type,
			upgrade_type _up_type, char* _name) :
			killing_count(0),
			hp(_hp),
			mp(_mp),
			shield(_shield),
			attack(_attack),
			defence(_defence),
			attack_upgrade_level(_attack_lv),
			defence_upgrade_level(_defence_lv),
			unit_type(_unit_type),
			upgrade_type(_up_type),
			unit_name(_name) {}

		unsigned int killing_count;				// �� ���� ���μ�
		unsigned int hp;						// ü��
		unsigned int mp;						// ����
		unsigned int shield;					// ����
		unsigned int attack;					// ���ݷ�
		unsigned int defence;						// ����
		unsigned int attack_upgrade_level;		// ���� ���׷��̵� ����
		unsigned int defence_upgrade_level;		// ��� ���׷��̵� ����
		unit_type unit_type;					// ���� ����
		upgrade_type upgrade_type;				// ���׷��̵� ����
		std::string unit_name;					// ���� �̸�
	private:
		unit_info();
	};
	struct unit_info2 {
		unit_info2(float _move_speed, float _attack_speed,
			float _sight_range, float _min_attack_range,
			float _max_attack_range) :
			move_speed(_move_speed),
			attack_speed(_attack_speed),
			sight_range(_sight_range),
			min_attack_range(_min_attack_range),
			max_attack_range(_max_attack_range)
		{}
		float move_speed;						// �̵��ӵ�
		float attack_speed;						// ���ݼӵ�
		float sight_range;						// �þ�
		float min_attack_range;					// �ּ�_�����Ÿ�
		float max_attack_range;					// �ִ�_�����Ÿ�
	private:
		unit_info2();
	};
	struct production_info {
		float required_production_time;			// �ʿ� ���� �ð�
		unsigned int required_building;			// �ʿ� �ǹ�
		unsigned int required_mineral;			// �ʿ� �̳׶�
		unsigned int required_gas;				// �ʿ� ����
		unsigned int required_supply;			// �ʿ� �α���
	};
public:
	virtual ~Unit();
	virtual bool init(const unit_type _type);
	static Unit* create(const unit_type _type);

	void attack_unit(Unit* const _target);
	void move_unit(const cocos2d::Vec2& _move_pos);
	void stop_unit();
	void patrol_unit(const cocos2d::Vec2& _move_pos);
	void hold_unit();
	void die_unit();
	void hit(int _dmg);
	void run_action_animation(float _dt);

	direction _unit_dir;
	
private:
	Unit();
	void check_dir(const cocos2d::Vec2 & _dir);
	void chang_order(const unit_state _state);

	// �и��ؾߵǴ� ���
	void run_action_move();

	// ���� �⺻ ������
	unit_info * _unit_info;						// ����ü ���� �ɷ�ġ ����
	unit_info2 * _unit_info2;						// ����ü ���� �ɷ�ġ ����2

	production_info * _production_info;			// ����ü ���� ����

	races_type _races_type;						// enum ����
	unit_state _unit_state;						// enum ������ ���� ����
	
	Unit * _target_unit;							// ���� ��ǥ
	cocos2d::Vec2 _move_vec2;					// �̵� ��ǥ
	cocos2d::Vec2 _my_pos_vec2;					// ������ġ, ���� ��ɽ� ���
	unsigned int _tile_x;						// Ÿ�� ��ġ_x
	unsigned int _tile_y;						// Ÿ�� ��ġ_y
	
	float _production_time;						// ���� ���� �ð�
	special_effects _unit_effects;				// ���� Ư������Ʈ
	
	UnitAnimation * _unit_animation;
	UnitWeapon * _weapon;

	std::vector<UnitWeapon*> _bullet_vector;
	void weapon_animaiton(float _dt);

	const float up =				0.99f;
	const float up_right_left1 =	0.66666666f;
	const float up_right_left2 =	0.33333333f;
	const float up_right_left3 =	0.1f;
	const float right_left =	   -0.1f;
	const float down_right_left1 = -0.33333333f;
	const float down_right_left2 = -0.66666666f;
	const float down_right_left3 = -0.99f;
};

#endif