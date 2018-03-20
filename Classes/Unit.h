/****************************
수정일 : 2018-03-19
작성자 : 은종수
파일명 : Unit.h
****************************/

#ifndef UNIT_H_
#define UNIT_H_

// cocos2d-x를 기반으로 코딩했으니 빠질수 없다.
#include "cocos2d.h"
//header.h는 나름 머리를 짜봤는데 따로 쓰기 힘든 부분을 모아둔 헤더 파일이다.
#include "header.h"


// 클래스는 어지간하면 전부 전방선언을 했다. 
// 아는 분이 프로그래머는 최고의 효율 ? 성능 ? 뭐라고했지..
// 추구해야 한다고 해서 신경써본 부분이다.

// 전방선언을 했을때 장점이 컴파일을 할때 헤더 파일을 쭉 돌면서 확인하는데
// 포함된 클래스가 많으면 해당 클래스를 다 확인하기 때문에 시간이 오래걸리는데
// h파일에 전방선언을 하고 cpp파일에서 포함하면 다른 클래스를 확인하는 
// 시간이 절약된다 라고 기억한다.

// 인터넷에서는 의존성을 최소화하기 위해서 라는데 말이 어렵다.
// 그래서 모르면 전방선언하는게 빠르다 정도로 기억했던거 같기도 하다.

// Effective C++ 31번 항목에서 이 전방선언에 대해서 나온다.
// 말이 어려운데.. 요약하면 전방선언으로 속도를 이득보는건 컴파일 할때
// 실제로 게임이 만들어져서 서비스를 하고자 할때는 전방선언을 사용해서 생기는 비용으로
// 문제가 될수 있으니 바꾸는게 좋은지는 판단하는게 좋다. 라는거 같다.

// class 전방선언

// 각 유닛마다 공격하는 형태가 다르다.
// 그래서 그 무기에 대한 정보를 가지는 클래스.
class UnitWeapon;

// 이동, 대기, 공격, 죽음 의 애니메이션을 실행하기 위한 클래스.
class UnitAnimation;

// 유닛의 머리, 길을 찾고, 주변 유닛을 감지하고, 싸우는 일을 하는 클래스.
class AIManager;

class Unit :public cocos2d::Sprite {
public:
	// 유닛 타입
	// 필요할거 같아서 만들어는 뒀지만 아직 사용은 못했다.
	enum class UpgradeType {
		bionic, 
		mechanic, 
		air_force
	};

	// 종족 타입
	// 유닛 타입과 같다. 그리고 마린만 만들어서 다른 종족은 기록하지도 않았다.
	enum class RacesType {
		terran,
	};

	// 유닛 사이즈
	// 마린이 소형, 벌쳐 골리앗이 중형, 탱크가 대형, 그리고 건물이 있다.
	// 이 크기에 따라 차지하는 공간이 다르다.
	enum class UnitSizeType {
		small_unit, 
		medium_unit, 
		large_unit, 
		building
	};

	// 특수효과
	// 유닛의 상태를 구분한다. 고스트의 클록킹과 일반적인 상태
	// 저그를 생각하면 인스네어나 플레이그도 있지 않나 싶다.
	enum class SpecialEffects {
		none, 
		clockking,
	};

	// 유닛의 정보가 들어있는 구조체
	// 체력, 마력, 쉴드, 공격력, 방어력, 업그레이드 수준, 
	// 유닛의 종류, 업그레이드 종류, 유닛의 이름, 죽인수를 가진다.
	// 변수가 너무 많아서 유사한 종류를 하나의 구조체에 모아두었다.
	// 솔직히 잘한짓인지는 나도 모르겠다.
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

	// 유닛정보 두번째, 이동속도, 공격속도, 시야, 사정거리의 정보를 가진다
	// 위와 유닛정보 첫번째와 동일한 이유로 작성했다.
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

	// 이건 생산정보이다.
	// 해당 유닛을 생산할때 필요한 시간, 요구 건물, 자원인데
	// 필요 건물의 변수가 왜 int지..??
	// 아직 사용하지 않으니 일단 넘어간다.
	struct production_info {
		float required_production_time;				// 필요 생산 시간
		unsigned int required_building;				// 필요 건물
		unsigned int required_mineral;				// 필요 미네랄
		unsigned int required_gas;					// 필요 가스
		unsigned int required_supply;				// 필요 인구수
	};

public:
	// 소멸자다.
	virtual ~Unit();
	
	// 이건 init 함수, cocos2d-x에서 처음 사용할때 초기화 시키는 함수다.
	// 개체가 생성되면 이 함수가 가장먼저 호출된다.
	// 원래 init 함수에서는 인자값을 요구하지 않는데 Unit 클래스를 만들때 필요해서
	// Unit 클래스를 만들며 init 함수를 호출하는 부분을 오버로딩 했다?라고 말하는게 맞나
	virtual bool init(const unit_type _type, const cocos2d::Vec2& _vec2, player_color _color);
	static Unit* create(const unit_type _type, const cocos2d::Vec2& _vec2, player_color _color);

	//이 밑으로는 거의 유닛의 행동과 관련된 함수들이다. 
	// 공격, 이동, 정지, 정찰, 고정, 죽음, 공격받았을때, 애니메이션을 진행하는 함수들이다.
	// 대부분 필요해서 만들어는 뒀지만 AI 부분이 완전치 않아서 함수를 선언만 해둔게 대부분이다.
	// 끝난건 애니메이션이 동작되는 부분..???
	void attack_unit(Unit* const _target);
	void move_unit(const cocos2d::Vec2& _move_vec2);
	void stop_unit();
	void patrol_unit(const cocos2d::Vec2& _move_vec2);
	void hold_unit();
	void die_unit();
	void hit(int _dmg);
	void run_action_animation(float _dt);

	// 유닛이 선택되었는지를 확인할때 호출하는 함수다.
	// 플레이어가 선택했다 안했다를 구분해준다.
	// 바로 밑은 선택을 했을때 상태값을 바꿔주는 함수다.
	inline bool is_select() const { return _select_unit; }
	inline void set_select_unit(bool _selete) { _select_unit = _selete; }

	// 현재 이 유닛이 바라보고 있는 방향을 저장하는 변수다.
	Direction _unit_dir;
	
private:
	// 위의 함수들과 달리 아래는 유닛 클래스에서 사용하는 함수라서 private에 등록했다.
	// 유닛의 정보없이 클래스 생성이 안되도록 생성자를 private에 넣었다.
	Unit();
	
	// 현재 방향을 확인하는 함수
	void check_dir(const cocos2d::Vec2& _dir);

	// 현재 상태를 설정하는 함수다.
	void set_state(const UnitState _state);

	// 유닛을 움직이거나 무기의 애니메이션을 동작시키는 함수인데
	// 그 위치를 어디로 해야될지 고민했었던 함수들이다.
	// 다만 당장 동작되게 하기위해 작성해서 넣어두었다.
	// 위치를 확정시키면 이동되거나 보완이 필요한 부분이다.
	void run_action_move();
	void weapon_animaiton(float _dt);
	
private:
	// 바로 위의 run_action_move와 weapon_animaiton에서 사용하는 변수인데
	// 어떤 용도로 만들었는지 모르겠다.
	// cpp 파일에서 코드를 보면서 확인하자.
	std::vector<UnitWeapon*> _bullet_vector;

	// 현재 유닛의 위치값을 저장하기 위해서 만든 구조체이다.
	// 유닛의 위치값을 쓸데가 있을거 같아 만들었는데 사용하지 않고있다.
	// 처음 다때려 박을때 만들었던 값이며, 이동할때 사용하는 좌표값은 또 따로있다.
	// 사용처를 확실하게 못한다면 삭제해야 될거 같다.
	struct Point {
		Point(int _x = 0, int _y = 0) :
			x(_x),
			y(_y)
		{}
		unsigned int x;
		unsigned int y;
	};

	// 위의 구조체를 변수를 만든것이다.
	Point tile_point;								// 타일 위치_x
	
	// 해당 유닛을 건물에서 생산한다면 걸린? 시간이다.
	// 이 시간이 필요시간과 같아지면 생산이 완료된다.
	float _production_time;							// 현재 생산 시간
	// 이 유닛이 선택되었는지 구분하는 변수다.
	// 플레이어의 화면에 정보창을 띄울때 사용한다.
	bool _select_unit;

	// 플레이어의 색상, 이 색상으로 유닛의 색을 결정한다.
	// 그 외 처음 나왔던 enum class 의 정보들이다.
	// 이 외에 유닛정보에 들어갔던 변수들도 이런식으로 선언되어있었는데
	// 유사한 값들을 모아서 UnitInfo에 이동시켰다.
	// 남은 변수들은 위치를 제대로 정하지 못한것들이다.
	player_color _player_color;						// 플레이어 색상
	RacesType _races_type;							// enum 종족
	UnitState _unit_state;							// enum 유닛의 현재 상태
	SpecialEffects _unit_effects;					// 현재 특수이팩트

	// 이동될때 사용되는 좌표값이다.
	// AI에서 길찾기를 수행하는 부분이 제대로 만들어지지 않아
	// 지형정보를 신경쓰지 않고 직선으로만 이동한다.
	// 그렇기 때문에 해당 변수들이 사용되는 함수도 미완성이다.
	cocos2d::Vec2 _move_vec2;						// 이동 목표
	cocos2d::Vec2 _my_pos_vec2;						// 시작위치, 정찰 명령시 사용

	// 유닛의 정보가 모여있는 구조체와 
	// 전방선언을 했던 클래스의 포인터 변수이다.
	
	// 전방선언을 한것들은 포인터 변수로 만들수 밖에 없다
	// 클래스의 정의를 모르기 때문이다.

	// 구조체 부분이 포인터인건 왜 그렇게 했는지 기억이 안난다.
	// 정의가 헤더파일에 있기 때문에 일반 변수로 만들어도 될텐데 포인터로 선언되어 있다.

	// 이럴땐 해당 변수를 포인터로 쓰는게 맞는지, 일반 변수로 쓰는게 맞는지를 판단해야 될텐데
	// 판단기준을 자세히 모르니 판단이 안된다.

	// 얼핏 생각나는건 편의성, 속도, 용량 정도인데
	// 이런건 뭐라고 검색해야지 답을 알수있는건지...
	UnitInfo * _unit_info;							// 구조체 유닛 능력치 정보
	UnitInfo2 * _unit_info2;						// 구조체 유닛 능력치 정보2
	production_info * _production_info;				// 구조체 생성 정보
	Unit * _target_unit;							// 공격 목표
	UnitAnimation * _unit_animation;
	UnitWeapon * _weapon;
	
	// 유닛이 보고있는 방향을 결정하기 위한 상수이다.
	// define을 사용하지 않고 const를 사용했는데
	// 왜 그렇게 했는지 까먹었다.
	// 잘은 기억안나는데 define을 사용하면 에러가 생겼을때 
	// 정의된 숫자만 뜨기 때문에 뭔지 모른다는 소리를 어디서 들은거 같다.
	// const로 해두면 변수 이름이 뜨기 때문에 대응이 쉽다고 했던가..???
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