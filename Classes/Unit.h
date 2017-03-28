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
		unit_info() : killing_count(0), hp(10), mp(0), shield(0), attack(5), armor(1),
		attack_upgrade_level(0), defence_upgrade_level(0) {}
		unsigned int killing_count;				// �� ���� ���μ�
		unsigned int hp;						// ü��
		unsigned int mp;						// ����
		unsigned int shield;					// ����
		unsigned int attack;					// ���ݷ�
		unsigned int armor;						// ����
		unsigned int attack_upgrade_level;		// ���� ���׷��̵� ����
		unsigned int defence_upgrade_level;		// ��� ���׷��̵� ����
		unit_type unit_type;					// ���� ����
		upgrade_type upgrade_type;				// ���׷��̵� ����
		std::string unit_name;					// ���� �̸�
	};

	struct production_info {
		float required_production_time;			// �ʿ� ���� �ð�
		unsigned int required_building;			// �ʿ� �ǹ�
		unsigned int required_mineral;			// �ʿ� �̳׶�
		unsigned int required_gas;				// �ʿ� ����
		unsigned int required_supply;			// �ʿ� �α���
	};
	
	void attack_unit(Unit* const _target);
	void move_unit(const cocos2d::Vec2& _move_pos);
	void stop_unit();
	void patrol_unit(const cocos2d::Vec2& _move_pos);
	void hold_unit();
	void die_unit();
	void hit(int _dmg);

	void run_action_animation(float _dt);
	

	direction unit_dir;
	int unit_dir2;
private:
	races_type races_type;						// ����
	unit_state unit_state;						// ������ ���� ����
	

	unit_info unit_info;
	production_info production_info;

	float move_speed;							// �̵��ӵ�
	float attack_speed;							// ���ݼӵ�
	float view_range;							// �þ�
	float min_attack_range;						// �ּ�_�����Ÿ�
	float max_attack_range;						// �ִ�_�����Ÿ�
	
	Unit* target_unit;							// ���� ��ǥ
	cocos2d::Vec2 move_vec2;
	cocos2d::Vec2 my_pos_vec2;
	unsigned int tile_x;						// Ÿ�� ��ġ_x
	unsigned int tile_y;						// Ÿ�� ��ġ_y
	
	float production_time;						// ���� ���� �ð�
	special_effects unit_effects;				// ���� Ư������Ʈ
	
	UnitAnimation* unit_animation;
	//UnitAnimation* attack_animation;
	//UnitAnimation* die_animation;
	
	UnitWeapon* weapon;
	std::vector<UnitWeapon*> bullet_vector;
	bool fire;

	void run_action_move();
	void check_dir(const cocos2d::Vec2 & _dir);
	void init_frame();
};

#endif