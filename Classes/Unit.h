/****************************
������ : 2018-03-19
�ۼ��� : ������
���ϸ� : Unit.h
****************************/

#ifndef UNIT_H_
#define UNIT_H_

// cocos2d-x�� ������� �ڵ������� ������ ����.
#include "cocos2d.h"
//header.h�� ���� �Ӹ��� ¥�ôµ� ���� ���� ���� �κ��� ��Ƶ� ��� �����̴�.
#include "header.h"


// Ŭ������ �������ϸ� ���� ���漱���� �ߴ�. 
// �ƴ� ���� ���α׷��Ӵ� �ְ��� ȿ�� ? ���� ? ���������..
// �߱��ؾ� �Ѵٰ� �ؼ� �Ű�ẻ �κ��̴�.

// ���漱���� ������ ������ �������� �Ҷ� ��� ������ �� ���鼭 Ȯ���ϴµ�
// ���Ե� Ŭ������ ������ �ش� Ŭ������ �� Ȯ���ϱ� ������ �ð��� �����ɸ��µ�
// h���Ͽ� ���漱���� �ϰ� cpp���Ͽ��� �����ϸ� �ٸ� Ŭ������ Ȯ���ϴ� 
// �ð��� ����ȴ� ��� ����Ѵ�.

// ���ͳݿ����� �������� �ּ�ȭ�ϱ� ���ؼ� ��µ� ���� ��ƴ�.
// �׷��� �𸣸� ���漱���ϴ°� ������ ������ ����ߴ��� ���⵵ �ϴ�.

// Effective C++ 31�� �׸񿡼� �� ���漱�� ���ؼ� ���´�.
// ���� ����.. ����ϸ� ���漱������ �ӵ��� �̵溸�°� ������ �Ҷ�
// ������ ������ ��������� ���񽺸� �ϰ��� �Ҷ��� ���漱���� ����ؼ� ����� �������
// ������ �ɼ� ������ �ٲٴ°� �������� �Ǵ��ϴ°� ����. ��°� ����.

// class ���漱��

// �� ���ָ��� �����ϴ� ���°� �ٸ���.
// �׷��� �� ���⿡ ���� ������ ������ Ŭ����.
class UnitWeapon;

// �̵�, ���, ����, ���� �� �ִϸ��̼��� �����ϱ� ���� Ŭ����.
class UnitAnimation;

// ������ �Ӹ�, ���� ã��, �ֺ� ������ �����ϰ�, �ο�� ���� �ϴ� Ŭ����.
class AIManager;

class Unit :public cocos2d::Sprite {
public:
	// ���� Ÿ��
	// �ʿ��Ұ� ���Ƽ� ������ ������ ���� ����� ���ߴ�.
	enum class UpgradeType {
		bionic, 
		mechanic, 
		air_force
	};

	// ���� Ÿ��
	// ���� Ÿ�԰� ����. �׸��� ������ ���� �ٸ� ������ ��������� �ʾҴ�.
	enum class RacesType {
		terran,
	};

	// ���� ������
	// ������ ����, ���� �񸮾��� ����, ��ũ�� ����, �׸��� �ǹ��� �ִ�.
	// �� ũ�⿡ ���� �����ϴ� ������ �ٸ���.
	enum class UnitSizeType {
		small_unit, 
		medium_unit, 
		large_unit, 
		building
	};

	// Ư��ȿ��
	// ������ ���¸� �����Ѵ�. ��Ʈ�� Ŭ��ŷ�� �Ϲ����� ����
	// ���׸� �����ϸ� �ν��׾ �÷��̱׵� ���� �ʳ� �ʹ�.
	enum class SpecialEffects {
		none, 
		clockking,
	};

	// ������ ������ ����ִ� ����ü
	// ü��, ����, ����, ���ݷ�, ����, ���׷��̵� ����, 
	// ������ ����, ���׷��̵� ����, ������ �̸�, ���μ��� ������.
	// ������ �ʹ� ���Ƽ� ������ ������ �ϳ��� ����ü�� ��Ƶξ���.
	// ������ ������������ ���� �𸣰ڴ�.
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

	// �������� �ι�°, �̵��ӵ�, ���ݼӵ�, �þ�, �����Ÿ��� ������ ������
	// ���� �������� ù��°�� ������ ������ �ۼ��ߴ�.
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

	// �̰� ���������̴�.
	// �ش� ������ �����Ҷ� �ʿ��� �ð�, �䱸 �ǹ�, �ڿ��ε�
	// �ʿ� �ǹ��� ������ �� int��..??
	// ���� ������� ������ �ϴ� �Ѿ��.
	struct production_info {
		float required_production_time;				// �ʿ� ���� �ð�
		unsigned int required_building;				// �ʿ� �ǹ�
		unsigned int required_mineral;				// �ʿ� �̳׶�
		unsigned int required_gas;					// �ʿ� ����
		unsigned int required_supply;				// �ʿ� �α���
	};

public:
	// �Ҹ��ڴ�.
	virtual ~Unit();
	
	// �̰� init �Լ�, cocos2d-x���� ó�� ����Ҷ� �ʱ�ȭ ��Ű�� �Լ���.
	// ��ü�� �����Ǹ� �� �Լ��� ������� ȣ��ȴ�.
	// ���� init �Լ������� ���ڰ��� �䱸���� �ʴµ� Unit Ŭ������ ���鶧 �ʿ��ؼ�
	// Unit Ŭ������ ����� init �Լ��� ȣ���ϴ� �κ��� �����ε� �ߴ�?��� ���ϴ°� �³�
	virtual bool init(const unit_type _type, const cocos2d::Vec2& _vec2, player_color _color);
	static Unit* create(const unit_type _type, const cocos2d::Vec2& _vec2, player_color _color);

	//�� �����δ� ���� ������ �ൿ�� ���õ� �Լ����̴�. 
	// ����, �̵�, ����, ����, ����, ����, ���ݹ޾�����, �ִϸ��̼��� �����ϴ� �Լ����̴�.
	// ��κ� �ʿ��ؼ� ������ ������ AI �κ��� ����ġ �ʾƼ� �Լ��� ���� �صа� ��κ��̴�.
	// ������ �ִϸ��̼��� ���۵Ǵ� �κ�..???
	void attack_unit(Unit* const _target);
	void move_unit(const cocos2d::Vec2& _move_vec2);
	void stop_unit();
	void patrol_unit(const cocos2d::Vec2& _move_vec2);
	void hold_unit();
	void die_unit();
	void hit(int _dmg);
	void run_action_animation(float _dt);

	// ������ ���õǾ������� Ȯ���Ҷ� ȣ���ϴ� �Լ���.
	// �÷��̾ �����ߴ� ���ߴٸ� �������ش�.
	// �ٷ� ���� ������ ������ ���°��� �ٲ��ִ� �Լ���.
	inline bool is_select() const { return _select_unit; }
	inline void set_select_unit(bool _selete) { _select_unit = _selete; }

	// ���� �� ������ �ٶ󺸰� �ִ� ������ �����ϴ� ������.
	Direction _unit_dir;
	
private:
	// ���� �Լ���� �޸� �Ʒ��� ���� Ŭ�������� ����ϴ� �Լ��� private�� ����ߴ�.
	// ������ �������� Ŭ���� ������ �ȵǵ��� �����ڸ� private�� �־���.
	Unit();
	
	// ���� ������ Ȯ���ϴ� �Լ�
	void check_dir(const cocos2d::Vec2& _dir);

	// ���� ���¸� �����ϴ� �Լ���.
	void set_state(const UnitState _state);

	// ������ �����̰ų� ������ �ִϸ��̼��� ���۽�Ű�� �Լ��ε�
	// �� ��ġ�� ���� �ؾߵ��� ����߾��� �Լ����̴�.
	// �ٸ� ���� ���۵ǰ� �ϱ����� �ۼ��ؼ� �־�ξ���.
	// ��ġ�� Ȯ����Ű�� �̵��ǰų� ������ �ʿ��� �κ��̴�.
	void run_action_move();
	void weapon_animaiton(float _dt);
	
private:
	// �ٷ� ���� run_action_move�� weapon_animaiton���� ����ϴ� �����ε�
	// � �뵵�� ��������� �𸣰ڴ�.
	// cpp ���Ͽ��� �ڵ带 ���鼭 Ȯ������.
	std::vector<UnitWeapon*> _bullet_vector;

	// ���� ������ ��ġ���� �����ϱ� ���ؼ� ���� ����ü�̴�.
	// ������ ��ġ���� ������ ������ ���� ������µ� ������� �ʰ��ִ�.
	// ó�� �ٶ��� ������ ������� ���̸�, �̵��Ҷ� ����ϴ� ��ǥ���� �� �����ִ�.
	// ���ó�� Ȯ���ϰ� ���Ѵٸ� �����ؾ� �ɰ� ����.
	struct Point {
		Point(int _x = 0, int _y = 0) :
			x(_x),
			y(_y)
		{}
		unsigned int x;
		unsigned int y;
	};

	// ���� ����ü�� ������ ������̴�.
	Point tile_point;								// Ÿ�� ��ġ_x
	
	// �ش� ������ �ǹ����� �����Ѵٸ� �ɸ�? �ð��̴�.
	// �� �ð��� �ʿ�ð��� �������� ������ �Ϸ�ȴ�.
	float _production_time;							// ���� ���� �ð�
	// �� ������ ���õǾ����� �����ϴ� ������.
	// �÷��̾��� ȭ�鿡 ����â�� ��ﶧ ����Ѵ�.
	bool _select_unit;

	// �÷��̾��� ����, �� �������� ������ ���� �����Ѵ�.
	// �� �� ó�� ���Դ� enum class �� �������̴�.
	// �� �ܿ� ���������� ���� �����鵵 �̷������� ����Ǿ��־��µ�
	// ������ ������ ��Ƽ� UnitInfo�� �̵����״�.
	// ���� �������� ��ġ�� ����� ������ ���Ѱ͵��̴�.
	player_color _player_color;						// �÷��̾� ����
	RacesType _races_type;							// enum ����
	UnitState _unit_state;							// enum ������ ���� ����
	SpecialEffects _unit_effects;					// ���� Ư������Ʈ

	// �̵��ɶ� ���Ǵ� ��ǥ���̴�.
	// AI���� ��ã�⸦ �����ϴ� �κ��� ����� ��������� �ʾ�
	// ���������� �Ű澲�� �ʰ� �������θ� �̵��Ѵ�.
	// �׷��� ������ �ش� �������� ���Ǵ� �Լ��� �̿ϼ��̴�.
	cocos2d::Vec2 _move_vec2;						// �̵� ��ǥ
	cocos2d::Vec2 _my_pos_vec2;						// ������ġ, ���� ��ɽ� ���

	// ������ ������ ���ִ� ����ü�� 
	// ���漱���� �ߴ� Ŭ������ ������ �����̴�.
	
	// ���漱���� �Ѱ͵��� ������ ������ ����� �ۿ� ����
	// Ŭ������ ���Ǹ� �𸣱� �����̴�.

	// ����ü �κ��� �������ΰ� �� �׷��� �ߴ��� ����� �ȳ���.
	// ���ǰ� ������Ͽ� �ֱ� ������ �Ϲ� ������ ���� ���ٵ� �����ͷ� ����Ǿ� �ִ�.

	// �̷��� �ش� ������ �����ͷ� ���°� �´���, �Ϲ� ������ ���°� �´����� �Ǵ��ؾ� ���ٵ�
	// �Ǵܱ����� �ڼ��� �𸣴� �Ǵ��� �ȵȴ�.

	// ���� �������°� ���Ǽ�, �ӵ�, �뷮 �����ε�
	// �̷��� ����� �˻��ؾ��� ���� �˼��ִ°���...
	UnitInfo * _unit_info;							// ����ü ���� �ɷ�ġ ����
	UnitInfo2 * _unit_info2;						// ����ü ���� �ɷ�ġ ����2
	production_info * _production_info;				// ����ü ���� ����
	Unit * _target_unit;							// ���� ��ǥ
	UnitAnimation * _unit_animation;
	UnitWeapon * _weapon;
	
	// ������ �����ִ� ������ �����ϱ� ���� ����̴�.
	// define�� ������� �ʰ� const�� ����ߴµ�
	// �� �׷��� �ߴ��� ��Ծ���.
	// ���� ���ȳ��µ� define�� ����ϸ� ������ �������� 
	// ���ǵ� ���ڸ� �߱� ������ ���� �𸥴ٴ� �Ҹ��� ��� ������ ����.
	// const�� �صθ� ���� �̸��� �߱� ������ ������ ���ٰ� �ߴ���..???
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