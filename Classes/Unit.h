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
	


	int hp;									// 체력
	int mp;									// 마력
	int shield;								// 쉴드
	int armor;								// 방어력
	float move_speed;						// 이동속도
	float attack_speed;						// 공격속도
	float view_range;						// 시야
	float min_attack_range;					// 최소_사정거리
	float max_attack_range;					// 최대_사정거리

	UnitDirection unit_dir;					// 유닛이 보는 방향

	struct upgrade {
		upgrade_type upgrade_type;
		int attack_upgrade_level;
		int defence_upgrade_level;
	};
	

	float required_production_time;			// 필요 생산 시간
	float production_time1;

	// 상속받은 개체가 가져야한다.
	Weapon* unit_weapon;
	Animation* unit_animation;


};

#endif