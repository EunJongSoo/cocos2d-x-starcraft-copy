#ifndef UNIT_H_
#define UNIT_H_

#include "cocos2d.h"
#include "header.h"

class UnitWeapon;
class UnitAnimation;

class Unit :public cocos2d::Sprite {
public:
	Unit();
	virtual ~Unit();
	virtual bool init();
	CREATE_FUNC(Unit);

public:
	enum races_type {
		terran,
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
	
	void attack_unit(Unit* const _target);
	void move_unit(const float _x, const float _y);
	void stop_unit();
	void patrol_unit();
	void hold_unit();
	void die_unit();

	void run_action_animation(float _dt);
	

	direction _unit_dir;
	int _unit_dir2;
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
	
	Unit* _target_unit;							// ���� ��ǥ
	cocos2d::Vec2 move_vec2;
	float _move_x;								// �̵� ��ǥ_x
	float _move_y;								// �̵� ��ǥ_y
	float _pos_x;								// ���� ��ǥ_x
	float _pos_y;								// ���� ��ǥ_y
	unsigned int _tile_x;						// Ÿ�� ��ġ_x
	unsigned int _tile_y;						// Ÿ�� ��ġ_y
	
	float _production_time;						// ���� ���� �ð�
	special_effects _unit_effects;				// ���� Ư������Ʈ
	
	UnitAnimation* move_animation;
	UnitAnimation* attack_animation;
	UnitAnimation* die_animation;
	
	UnitWeapon* weapon;
	std::vector<UnitWeapon*> bullet_vector;
	
	void run_action_move();
	void check_dir(const cocos2d::Vec2 & _dir);
	bool _fire;
};

#endif