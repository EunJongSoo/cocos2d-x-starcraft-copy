/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : Unit.h
****************************/

#ifndef UNIT_H_
#define UNIT_H_

#include "cocos2d.h"
#include "header.h"

// class 전방선언
class UnitWeapon;
class UnitAnimation;
class AIManager;

class Unit :public cocos2d::Sprite {
public:
	// 유닛 타입
	enum class UpgradeType {
		bionic, 
		mechanic, 
		air_force
	};

	// 종족 타입
	enum class RacesType {
		terran,
	};

	// 유닛 사이즈
	enum class UnitSizeType {
		small_unit, 
		medium_unit, 
		large_unit, 
		building
	};

	// 특수효과
	enum class SpecialEffects {
		none, 
		clockking,
	};

	struct UnitInfo {
		UnitInfo(int _hp, int _mp, int _shield, int _attack,
			int _defence, int _attack_lv, int _defence_lv, unit_type _unit_type,
			UpgradeType _up_type, char* _name) :
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

		unsigned int killing_count;					// 적 유닛 죽인수
		unsigned int hp;							// 체력
		unsigned int mp;							// 마력
		unsigned int shield;						// 쉴드
		unsigned int attack;						// 공격력
		unsigned int defence;						// 방어력
		unsigned int attack_upgrade_level;			// 공격 업그레이드 수준
		unsigned int defence_upgrade_level;			// 방어 업그레이드 수준
		unit_type unit_type;						// 유닛 종류
		UpgradeType upgrade_type;					// 업그레이드 종류
		std::string unit_name;						// 유닛 이름
	private:
		UnitInfo();
	};
	struct UnitInfo2 {
		UnitInfo2(float _move_speed, float _attack_speed,
			float _sight_range, float _min_attack_range,
			float _max_attack_range) :
			move_speed(_move_speed),
			attack_speed(_attack_speed),
			sight_range(_sight_range),
			min_attack_range(_min_attack_range),
			max_attack_range(_max_attack_range)
		{}
		float move_speed;							// 이동속도
		float attack_speed;							// 공격속도
		float sight_range;							// 시야
		float min_attack_range;						// 최소_사정거리
		float max_attack_range;						// 최대_사정거리
	private:
		UnitInfo2();
	};
	struct production_info {
		float required_production_time;				// 필요 생산 시간
		unsigned int required_building;				// 필요 건물
		unsigned int required_mineral;				// 필요 미네랄
		unsigned int required_gas;					// 필요 가스
		unsigned int required_supply;				// 필요 인구수
	};
public:
	virtual ~Unit();
	virtual bool init(const unit_type _type, const cocos2d::Vec2& _vec2, player_color _color);
	static Unit* create(const unit_type _type, const cocos2d::Vec2& _vec2, player_color _color);

	void attack_unit(Unit* const _target);
	void move_unit(const cocos2d::Vec2& _move_vec2);
	void stop_unit();
	void patrol_unit(const cocos2d::Vec2& _move_vec2);
	void hold_unit();
	void die_unit();
	void hit(int _dmg);
	void run_action_animation(float _dt);

	inline bool is_select() const { return _select_unit; }
	inline void set_select_unit(bool _selete) { _select_unit = _selete; }

	Direction _unit_dir;
	
private:
	Unit();
	void check_dir(const cocos2d::Vec2& _dir);
	void set_state(const UnitState _state);

	// 분리해야되는 기능
	void run_action_move();
	void weapon_animaiton(float _dt);
	
private:
	std::vector<UnitWeapon*> _bullet_vector;

	struct Point {
		Point(int _x = 0, int _y = 0) :
			x(_x),
			y(_y)
		{}
		unsigned int x;
		unsigned int y;
	};

	Point tile_point;								// 타일 위치_x
	float _production_time;							// 현재 생산 시간
	bool _select_unit;

	player_color _player_color;						// 플레이어 색상
	RacesType _races_type;							// enum 종족
	UnitState _unit_state;							// enum 유닛의 현재 상태
	SpecialEffects _unit_effects;					// 현재 특수이팩트

	cocos2d::Vec2 _move_vec2;						// 이동 목표
	cocos2d::Vec2 _my_pos_vec2;						// 시작위치, 정찰 명령시 사용
	UnitInfo * _unit_info;							// 구조체 유닛 능력치 정보
	UnitInfo2 * _unit_info2;						// 구조체 유닛 능력치 정보2
	production_info * _production_info;				// 구조체 생성 정보
	Unit * _target_unit;							// 공격 목표
	UnitAnimation * _unit_animation;
	UnitWeapon * _weapon;
	
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