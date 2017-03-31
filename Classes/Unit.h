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

		unsigned int killing_count;				// 적 유닛 죽인수
		unsigned int hp;						// 체력
		unsigned int mp;						// 마력
		unsigned int shield;					// 쉴드
		unsigned int attack;					// 공격력
		unsigned int defence;						// 방어력
		unsigned int attack_upgrade_level;		// 공격 업그레이드 수준
		unsigned int defence_upgrade_level;		// 방어 업그레이드 수준
		unit_type unit_type;					// 유닛 종류
		upgrade_type upgrade_type;				// 업그레이드 종류
		std::string unit_name;					// 유닛 이름
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
		float move_speed;						// 이동속도
		float attack_speed;						// 공격속도
		float sight_range;						// 시야
		float min_attack_range;					// 최소_사정거리
		float max_attack_range;					// 최대_사정거리
	private:
		unit_info2();
	};
	struct production_info {
		float required_production_time;			// 필요 생산 시간
		unsigned int required_building;			// 필요 건물
		unsigned int required_mineral;			// 필요 미네랄
		unsigned int required_gas;				// 필요 가스
		unsigned int required_supply;			// 필요 인구수
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

	// 분리해야되는 기능
	void run_action_move();

	// 유닛 기본 정보들
	unit_info * _unit_info;						// 구조체 유닛 능력치 정보
	unit_info2 * _unit_info2;						// 구조체 유닛 능력치 정보2

	production_info * _production_info;			// 구조체 생성 정보

	races_type _races_type;						// enum 종족
	unit_state _unit_state;						// enum 유닛의 현재 상태
	
	Unit * _target_unit;							// 공격 목표
	cocos2d::Vec2 _move_vec2;					// 이동 목표
	cocos2d::Vec2 _my_pos_vec2;					// 시작위치, 정찰 명령시 사용
	unsigned int _tile_x;						// 타일 위치_x
	unsigned int _tile_y;						// 타일 위치_y
	
	float _production_time;						// 현재 생산 시간
	special_effects _unit_effects;				// 현재 특수이팩트
	
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