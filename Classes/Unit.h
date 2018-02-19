/****************************
������ : 2017-02-19
�ۼ��� : ������
���ϸ� : Unit.h
****************************/

#ifndef UNIT_H_
#define UNIT_H_

#include "cocos2d.h"
#include "header.h"

// class ���漱��
class UnitWeapon;
class UnitAnimation;
class AIManager;

class Unit :public cocos2d::Sprite {
public:
	// ���� Ÿ��
	enum class UpgradeType {
		bionic, 
		mechanic, 
		air_force
	};

	// ���� Ÿ��
	enum class RacesType {
		terran,
	};

	// ���� ������
	enum class UnitSizeType {
		small_unit, 
		medium_unit, 
		large_unit, 
		building
	};

	// Ư��ȿ��
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

		unsigned int killing_count;					// �� ���� ���μ�
		unsigned int hp;							// ü��
		unsigned int mp;							// ����
		unsigned int shield;						// ����
		unsigned int attack;						// ���ݷ�
		unsigned int defence;						// ����
		unsigned int attack_upgrade_level;			// ���� ���׷��̵� ����
		unsigned int defence_upgrade_level;			// ��� ���׷��̵� ����
		unit_type unit_type;						// ���� ����
		UpgradeType upgrade_type;					// ���׷��̵� ����
		std::string unit_name;						// ���� �̸�
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
		float move_speed;							// �̵��ӵ�
		float attack_speed;							// ���ݼӵ�
		float sight_range;							// �þ�
		float min_attack_range;						// �ּ�_�����Ÿ�
		float max_attack_range;						// �ִ�_�����Ÿ�
	private:
		UnitInfo2();
	};
	struct production_info {
		float required_production_time;				// �ʿ� ���� �ð�
		unsigned int required_building;				// �ʿ� �ǹ�
		unsigned int required_mineral;				// �ʿ� �̳׶�
		unsigned int required_gas;					// �ʿ� ����
		unsigned int required_supply;				// �ʿ� �α���
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

	// �и��ؾߵǴ� ���
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

	Point tile_point;								// Ÿ�� ��ġ_x
	float _production_time;							// ���� ���� �ð�
	bool _select_unit;

	player_color _player_color;						// �÷��̾� ����
	RacesType _races_type;							// enum ����
	UnitState _unit_state;							// enum ������ ���� ����
	SpecialEffects _unit_effects;					// ���� Ư������Ʈ

	cocos2d::Vec2 _move_vec2;						// �̵� ��ǥ
	cocos2d::Vec2 _my_pos_vec2;						// ������ġ, ���� ��ɽ� ���
	UnitInfo * _unit_info;							// ����ü ���� �ɷ�ġ ����
	UnitInfo2 * _unit_info2;						// ����ü ���� �ɷ�ġ ����2
	production_info * _production_info;				// ����ü ���� ����
	Unit * _target_unit;							// ���� ��ǥ
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