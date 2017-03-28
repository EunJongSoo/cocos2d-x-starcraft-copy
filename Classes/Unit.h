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
		unsigned int killing_count;				// 적 유닛 죽인수
		unsigned int hp;						// 체력
		unsigned int mp;						// 마력
		unsigned int shield;					// 쉴드
		unsigned int attack;					// 공격력
		unsigned int armor;						// 방어력
		unsigned int attack_upgrade_level;		// 공격 업그레이드 수준
		unsigned int defence_upgrade_level;		// 방어 업그레이드 수준
		unit_type unit_type;					// 유닛 종류
		upgrade_type upgrade_type;				// 업그레이드 종류
		std::string unit_name;					// 유닛 이름
	};

	struct production_info {
		float required_production_time;			// 필요 생산 시간
		unsigned int required_building;			// 필요 건물
		unsigned int required_mineral;			// 필요 미네랄
		unsigned int required_gas;				// 필요 가스
		unsigned int required_supply;			// 필요 인구수
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
	races_type races_type;						// 종족
	unit_state unit_state;						// 유닛의 현재 상태
	

	unit_info unit_info;
	production_info production_info;

	float move_speed;							// 이동속도
	float attack_speed;							// 공격속도
	float view_range;							// 시야
	float min_attack_range;						// 최소_사정거리
	float max_attack_range;						// 최대_사정거리
	
	Unit* target_unit;							// 공격 목표
	cocos2d::Vec2 move_vec2;
	cocos2d::Vec2 my_pos_vec2;
	unsigned int tile_x;						// 타일 위치_x
	unsigned int tile_y;						// 타일 위치_y
	
	float production_time;						// 현재 생산 시간
	special_effects unit_effects;				// 현재 특수이팩트
	
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