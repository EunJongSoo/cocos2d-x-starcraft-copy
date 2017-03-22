#ifndef UNIT_H_
#define UNIT_H_

//#include <string>

class Weapon;
class Animation;

class Unit {
public:
	Unit();
	~Unit();

	enum unit_state {
		production, idle, move, attack,
	};
	enum unit_size_type {
		small, medium, large, building
	};
	enum upgrade_type {
		infantry, mechanic, air_force, skill
	};
	typedef enum direction {
		up, down, left, right, up_left, up_right, down_left, down_right,
	}UnitDirection;

	void attack_unit();
	void move_unit();
	void stop_unit();
	void patrol_unit();
	void hold_unit();

private:
	std::string unit_name;
	


	int hp;									// ü��
	int mp;									// ����
	int shield;								// ����
	int armor;								// ����
	float move_speed;						// �̵��ӵ�
	float attack_speed;						// ���ݼӵ�
	float view_range;						// �þ�
	float min_attack_range;					// �ּ�_�����Ÿ�
	float max_attack_range;					// �ִ�_�����Ÿ�

	UnitDirection unit_dir;					// ������ ���� ����

	struct upgrade {
		upgrade_type upgrade_type;
		int attack_upgrade_level;
		int defence_upgrade_level;
	};
	

	float required_production_time;			// �ʿ� ���� �ð�
	float production_time1;

	// ��ӹ��� ��ü�� �������Ѵ�.
	Weapon* unit_weapon;
	Animation* unit_animation;


};

#endif