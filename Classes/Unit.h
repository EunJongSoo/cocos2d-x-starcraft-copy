#ifndef UNIT_H_
#define UNIT_H_

#include <string>
#include "cocos2d.h"

class UnitWeapon;
class UnitAnimation;

class Unit :public cocos2d::Node {
public:
	Unit();
	virtual ~Unit();
	virtual bool init();
	CREATE_FUNC(Unit);

public:
	enum races_type {
		terran,
	};
	enum unit_state {
		production, idle, move, attack, petrol, hold
	};
	enum direction {
		up, down, left, right, up_left, up_right, down_left, down_right,
	};
	typedef enum unit_type {
		marine,
	} building_type;
	enum upgrade_type {
		bionic, mechanic, air_force
	};
	enum unit_size_type {
		small_unit, medium_unit, large_unit, building
	};
	
	enum special_effects {
		none, clockking, 
	};
	
	struct unit_info {
		unit_type _unit_type;					// ���� ����
		upgrade_type _upgrade_type;				// ���׷��̵� ����
		std::string _unit_name;					// ���� �̸�
		unsigned int _killing_count;			// �� ���� ���μ�
		unsigned int _hp;						// ü��
		unsigned int _mp;						// ����
		unsigned int _shield;					// ����
		unsigned int _attack;					// ���ݷ�
		unsigned int _armor;					// ����
		unsigned int _attack_upgrade_level;		// ���� ���׷��̵� ����
		unsigned int _defence_upgrade_level;	// ��� ���׷��̵� ����
	};

	struct production_info {
		float _required_production_time;		// �ʿ� ���� �ð�
		unsigned int _required_building;		// �ʿ� �ǹ�
		unsigned int _required_mineral;			// �ʿ� �̳׶�
		unsigned int _required_gas;				// �ʿ� ����
		unsigned int _required_supply;			// �ʿ� �α���
	};
	
	void attack_unit();
	void move_unit();
	void stop_unit();
	void patrol_unit();
	void hold_unit();

private:
	races_type _races_type;						// ����
	unit_state _unit_state;						// ������ ���� ����
	
	unit_info _unit_info;
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
	unsigned int _tile_x;						// Ÿ�� ��ġ_x
	unsigned int _tile_y;						// Ÿ�� ��ġ_y
	
	float _production_time;						// ���� ���� �ð�
	special_effects _unit_effects;				// ���� Ư������Ʈ


	// ��ӹ��� ��ü�� �������Ѵ�.
	UnitWeapon* _unit_weapon;
	UnitAnimation* _unit_animation;
};

#endif