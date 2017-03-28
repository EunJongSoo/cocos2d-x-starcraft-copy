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
		unit_type _unit_type;					// 유닛 종류
		upgrade_type _upgrade_type;				// 업그레이드 종류
		std::string _unit_name;					// 유닛 이름
		unsigned int _killing_count;			// 적 유닛 죽인수
		unsigned int _hp;						// 체력
		unsigned int _mp;						// 마력
		unsigned int _shield;					// 쉴드
		unsigned int _attack;					// 공격력
		unsigned int _armor;					// 방어력
		unsigned int _attack_upgrade_level;		// 공격 업그레이드 수준
		unsigned int _defence_upgrade_level;	// 방어 업그레이드 수준
	};

	struct production_info {
		float _required_production_time;		// 필요 생산 시간
		unsigned int _required_building;		// 필요 건물
		unsigned int _required_mineral;			// 필요 미네랄
		unsigned int _required_gas;				// 필요 가스
		unsigned int _required_supply;			// 필요 인구수
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
	races_type _races_type;						// 종족
	unit_state _unit_state;						// 유닛의 현재 상태
	

	unit_info _unit_info;
	production_info _production_info;

	float _move_speed;							// 이동속도
	float _attack_speed;						// 공격속도
	float _view_range;							// 시야
	float _min_attack_range;					// 최소_사정거리
	float _max_attack_range;					// 최대_사정거리
	
	Unit* _target_unit;							// 공격 목표
	cocos2d::Vec2 move_vec2;
	float _move_x;								// 이동 목표_x
	float _move_y;								// 이동 목표_y
	float _pos_x;								// 유닛 좌표_x
	float _pos_y;								// 유닛 좌표_y
	unsigned int _tile_x;						// 타일 위치_x
	unsigned int _tile_y;						// 타일 위치_y
	
	float _production_time;						// 현재 생산 시간
	special_effects _unit_effects;				// 현재 특수이팩트
	
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