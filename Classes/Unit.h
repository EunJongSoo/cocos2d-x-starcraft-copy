#ifndef UNIT_H_
#define UNIT_H_

#include <string>

class UnitWeapon;
class UnitAnimation;

class Unit {
public:
	Unit();
	~Unit();

public:
	enum direction {
		up, down, left, right, up_left, up_right, down_left, down_right,
	};
	enum unit_state {
		production, idle, move, attack, petrol
	};
	enum unit_type {
		marine,
	};
	enum building_type {

	};
	enum unit_size_type {
		small, medium, large, building
	};
	enum upgrade_type {
		bionic, mechanic, air_force
	};
	enum races_type {
		terran
	};
	enum special_effects {
		none, clockking, 
	};
	
	struct Unit_info {
		unit_type _unit_type;
		int _hp;								// ü��
		int _mp;								// ����
		int _shield;							// ����
		int _attack;							// ���ݷ�
		int _armor;								// ����
	};

	struct Upgrade_info {
		upgrade_type _upgrade_type;
		int _attack_upgrade_level;
		int _defence_upgrade_level;
	};

	struct production_info {
		float _required_production_time;		// �ʿ� ���� �ð�
		int _required_building;					// �ʿ� �α���
		int _required_mineral;					// �ʿ� �̳׶�
		int _required_gas;						// �ʿ� ����
		int _required_supply;					// �ʿ� �α���
	};
	
	void attack_unit();
	void move_unit();
	void stop_unit();
	void patrol_unit();
	void hold_unit();

private:
	std::string _unit_name;
	
	Unit_info _unit_info;
	Upgrade_info _upgrade_info;
	production_info _production_info;

	float _move_speed;							// �̵��ӵ�
	float _attack_speed;						// ���ݼӵ�
	float _view_range;							// �þ�
	float _min_attack_range;					// �ּ�_�����Ÿ�
	float _max_attack_range;					// �ִ�_�����Ÿ�
	
	direction _unit_dir;						// ������ ���� ����
	
	Unit* _target_unit;							// ���� ��ǥ
	float _move_x;								// �̵� ��ǥ_x
	float _move_y;								// �̵� ��ǥ_y
	float _pos_x;								// ���� ��ǥ_x
	float _pos_y;								// ���� ��ǥ_y
	int _tile_x;								// Ÿ�� ��ġ_x
	int _tile_y;								// Ÿ�� ��ġ_y
	
	float _production_time;						// �������� �ð�
	special_effects unit_effects;				// ���� Ư������Ʈ


	// ��ӹ��� ��ü�� �������Ѵ�.
	Weapon* _unit_weapon;
	UnitAnimation* _unit_animation;


};

#endif