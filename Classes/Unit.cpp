/****************************
수정일 : 2018-03-20
작성자 : 은종수
파일명 : Unit.cpp
****************************/

// h파일에서 전방선언했던 클래스들을 cpp파일에서 포함하고 있다.
#include "Unit.h"
#include "UnitAnimation.h"
#include "UnitWeapon.h"

/*아래에서 싱글톤 패턴을 사용한 모양이다.
싱글톤 클래스는 간단한 코드인데, 편하게 막 사용하면
설계 구조가 꼬이기 때문에 정말 필요할때만 써야한다고 배웠다.
코드는 인터넷에서 구해서 썼던 기억이난다.
구글에 검색했을때 가장위에 있는 주소하나 남긴다.
http://vallista.tistory.com/entry/1-Singleton-Pattern-in-C */
#include "TemplateSingleton.h"
/*내가 만들고 있는 스타크래프트에서 사용되는 리소스를 관리하기 위해서 만들었던 클래스다.
상세한 내용은 이 클래스를 살펴볼때 보도록 하자.*/
#include "ResourcesManager.h"

/*unig namespace를 사용하면 namespace를 생략할수 있다.
잘 모를때는 생략하지말고 다 붙여서 쓰라는 이야기를 들었다.
그래야지 그 함수들이 어디서 나온지 알수있기 때문이다.*/
using namespace cocos2d;

/*유닛 클래스의 생성자다.
유닛의 정보들을 기본적으로 설정하면서 생성되고 있다.
앞에 말했듯 미완성 부분이 많아서 정보를 받아오는게 아니고
직접 임의의 값을 입력해두었다.
다시보니 init 함수를 호출할때 매개변수를 넘길게 아니고
생성자에 넘겨야 하지않나 싶기도 한데.. 아래쪽을 더 살펴보자*/
Unit::Unit() :
	_unit_dir(Direction::up),
	_production_time(0.0f),
	_select_unit(false),
	_player_color(kWhite),
	_races_type(RacesType::terran),
	_unit_state(UnitState::idle),
	_unit_effects(SpecialEffects::none),
	_unit_info(nullptr),
	_unit_info2(nullptr),
	_production_info(nullptr),
	_target_unit(nullptr),
	_unit_animation(nullptr),
	_weapon(nullptr)
{}

/*소멸자다.
유닛클래스에서 생성되는 포인터들을 안전해제 해주고 있다.
define된 안전해제문은 Header.h 파일에 정의되어 있다.
문구는 cocos2d-x에서 사용하는 안전해제와 같은데
왜 정의했는지 까먹었다.

아는분에게 따로 정의해서 사용하라는 이야기를 들어서 정의를 했었던거 같다.
그리고 Unit.h에 선언된 포인터 변수는 6개인데 여긴 3개뿐이다.
나머지 3개는 어디갔는지 확인해보자.

_target_unit, _production_info, _weapon 3개의 포인터를 안전해제를 안해주는데
_target_unit은 여기서 동적할당을 하는게 아니고 잠시 주소값만 받아다 쓰기 때문에 하지않고
_production_info는 사용하지 않고 있어서 없고 한데 불안하니 추가해둔다.
_weapon은 공격하는 모션 쪽이 미완성에 임시로 작성된 부분이라서 거취가 확정되지 않아서 인듯하다.
일단 수정이 필요함을 표시해두고 넘어간다.*/
Unit::~Unit() {
	// 멤버 변수 동적할당 안전해제
	SAFE_DELETE(_unit_info);
	SAFE_DELETE(_unit_info2);
	SAFE_DELETE(_unit_animation);

	//SAFE_DELETE(_production_info);

}
/*cocos2d-x의 가장위에 있는 Node 클래스에 있는 create 함수를 오버로딩 했다.
생성자에 매개변수를 넘기지 않고 init에 넘긴건 여전히 불명

생성자에 매개변수를 넘겨서 변수를 초기화 시켜서 사용하는 편이 더 좋지 않을까?
라는 생각이 문득 든다.

cocos2d-x의 create 함수 변경
매개변수로 생성할 유닛의 타입과 위치를 받는다.*/
Unit * Unit::create(const unit_type _type, const cocos2d::Vec2& _vec2, player_color _color) {
	Unit * pRet = new Unit();
	if (pRet && pRet->init(_type, _vec2, _color)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		return (pRet = nullptr);
	}
}

/*매개변수를 넘겨받는 init 함수다.
기존의 init 함수는 별도의 매개변수를 넘기지 않는다.

기존에 남겨진 주석만 봐도 임시로 작성했다는 티를 팍팍 내고있다.
유닛의 생성자체가 건물에서 생성할 유닛을 선택하면
그 정보를 넘겨 받아서 생성될텐데 앞단계가 전혀 없으니 정보를 받지 못한다.

그렇기 때문에 모든 부분이 임의로 값이 입력되어 있다.
건물에서 정보가 넘겨주는 부분이 만들어지면 모를까
현재는 순서가 뒤로 밀리는 부분이다.

cocos2d-x의 init 함수 변경
매개변수로 생성할 유닛의 타입과 위치를 받는다.*/
bool Unit::init(unit_type _type, const cocos2d::Vec2& _vec2, player_color _color) {

	// 혹시 상속받는 Sprite에서 문제가 생기면 정지하도록 추가된 부분
	assert(Sprite::init());

	// 유닛 색상 지정
	_player_color = _color;

	// 유닛 애니메이션 생성
	_unit_animation = new UnitAnimation(_type, _player_color, this);
	this->setPosition(_vec2);

	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~
	// 데이터 로드 ~~~~~~


	auto resources_manager = TemplateSingleton<ResourcesManager>::get_instance();

	// 임시작성
	// 마린의 이미지로 초기화한다.
	char str[16] = { 0, };
	sprintf_s(str, sizeof(str), "marine0016.bmp");
	auto sprite_cache = SpriteFrameCache::getInstance();
	this->initWithTexture(resources_manager->load_texture2d(str, _player_color));

	// 임시작성
	// 유닛 정보를 생성한다.
	_unit_info = new UnitInfo(1, 1, 1, 1, 1, 1, 1, unit_type::marine, UpgradeType::bionic, "marine");
	_unit_info2 = new UnitInfo2(1, 1, 1, 1, 1);

	// 임시작성
	// 유닛 종류에 따라 달라짐
	_unit_info2->move_speed = 2.0f;
	_unit_info2->attack_speed = 0.3f;

	return true;
}

/*단순하다.
함수가 호출되면 유닛의 상태값이 공격으로 변경되고
매개변수로 받은 타겟을 멤버 변수에 대입한다.
그리고 현재 유닛의 위치와 타겟의 유닛위치로 방향을 확인해서
유닛이 바라보는 방향을 확인하고 변경한다.*/

// 유닛 공격 명령
void Unit::attack_unit(Unit* const _target) {
	// 유닛의 현재 상태를 설정한다.
	set_state(UnitState::attack);

	// 타겟을 설정한다.
	_target_unit = _target;

	// 타겟의 위치와 유닛의 위치를 빼서 저장한다.
	Vec2 vec2 = _target_unit->getPosition() - this->getPosition();
	// 정규화 한다.
	vec2.normalize();
	// 방향을 확인한다.
	check_dir(vec2);
}

/*여기도 단순
해당 함수가 호출되면 상태값을 변경해주고 목표 위치값을 넣어준다.
유닛들의 애니메이션을 출력하기 위해서 계속 상태값을 확인하기 때문에
상태값만 바꿔주면 유닛의 행동이 변경된다.
추가로 필요한 값이 있으면 같이 넘겨준다.*/

// 유닛 이동 명령
void Unit::move_unit(const cocos2d::Vec2& _vec2) {
	set_state(UnitState::move);
	_move_vec2 = _vec2;
}

// 유닛 정지 명령
void Unit::stop_unit() {
	set_state(UnitState::idle);
}

// 현재 위치와 목적지를 왔다갔다 이동해야 되기 때문에
// 현재 위치도 같이 저장해준다.

// 유닛 순찰 명령
void Unit::patrol_unit(const cocos2d::Vec2& _vec2) {
	set_state(UnitState::patrol);
	_move_vec2 = _vec2;
	_my_pos_vec2 = this->getPosition();
}

// 유닛 고정 명령
void Unit::hold_unit() {
	set_state(UnitState::hold);
}

// 유닛이 죽으면 호출
void Unit::die_unit() {
	set_state(UnitState::die);
}

/*공격을 하면 그 대상에게 자신의 공격력을 넘겨줘야한다.
위에 있던 attack_unit 함수에서는 그 부분이 생략되어 있다.
그래서 아래의 hit 함수가 호출되지 않기 때문에 공격을 하지않는다
물론 상태값을 바꾸기 때문에 공격하는 애니메이션은 하고있다.*/

// 공격 당할때 호출된다.
void Unit::hit(int _dmg) {
	// 공격력에서 방어력을 뺀다.
	int dmg = _dmg - _unit_info->defence;
	// 공격력이 0이하이면 1로 만든다.
	if (dmg <= 0)
		dmg = 1;
	// 데미지 만큼 체력을 깍는다.
	_unit_info->hp -= dmg;

	// 체력이 0이하인지 확인한다.
	int hp = _unit_info->hp;
	if (hp <= 0) {
		// 체력을 0으로 만든다.
		_unit_info->hp = 0;
		// 유닛이 죽는다.
		die_unit();
	}
}

/*프레임마다 호출되는 함수다
스타크래프트는 24프레임 하던데
초당 24번 호출되는 함수다.
맵에 있는 모든유닛이 이 함수가 호출되니 얼마나 많이 호출될지는...
AI 부분에 미확정 부분이 많아서 대충 틀만 만들어두고 임시로 코딩된 부분이 많다.
죄다 뜯어 고쳐야 할 것들*/

void Unit::run_action_animation(float _dt) {	
	_unit_animation->run_action_aniamtion(_unit_state, _dt, _unit_dir);
	weapon_animaiton(_dt);
	switch (_unit_state)
	{	
	case UnitState::production: 						break;
	case UnitState::idle:								break;
	case UnitState::move:	run_action_move();			break;
	case UnitState::attack: {
			_weapon = new UnitWeapon(_target_unit, unit_type::marine_weapon);
			this->getParent()->addChild(_weapon);
			_bullet_vector.push_back(_weapon);
		break;
	}
	case UnitState::patrol: run_action_move();			break;
	case UnitState::hold: 								break;
	case UnitState::die: _unit_dir = Direction::up;		break;
	default:											break;
	}
	
}

// 임시 작성, 기능 이관 해야됨
void Unit::weapon_animaiton(float _dt) {

	for (UnitWeapon* weapon : _bullet_vector) {
		weapon->run_action_animation(_dt);
	}
	int i = 0, j = -1;
	for (UnitWeapon* weapon : _bullet_vector) {
		if (!weapon->isVisible()) {
			j = i;
		}
		++i;
	}
	if (j != -1) {
		this->getParent()->removeChild(_bullet_vector.at(j));
		delete _bullet_vector.at(j);
		_bullet_vector.erase(_bullet_vector.begin() + j);
	}
}

/*유닛을 움직이는 함수이다.
목적지점과 유닛이 만나면 상태값을 변경시키고
만나지 못했다면 위치를 변경한다.

cocos2d에 있는 Rect를 사용해서 충돌체크를 하는데
이미지의 크기로 하다보니 눈에 보이는 유닛보다 충돌체크 범위가 더 크다
유닛을 여백을 불투명하게 표시하여 보면 바로 확인된다

유닛의 중심점과 충돌 했을때 정지하도록 개선이 필요하다.

충돌 안했을때 이동하는 부분은 현재 위치와 목표위치를 정규화해서 이동하는 것이다.
이 부분은 이렇게하면 이동이 된다는걸 다른곳에서 봐서 따라한 거라
정확한 원리를 잘 모른다.
단지 정규화를 하면 Vec2 dir의 x,y 값이 -1~1 사이로 나오며
그 값으로 방향을 확인할수 있다.
그리고 그 방향에 속도를 곱하고 현재 위치에 더하면
이동속도 만큼 그 방향으로 이동하게 되는것이다.*/

// 임시 작성, 기능 이관 해야된다.
void Unit::run_action_move() {
	Rect bounding = this->getBoundingBox();
	if (bounding.containsPoint(_move_vec2)) {
		if (_unit_state == UnitState::move) {
			set_state(UnitState::idle);
		}
		/*패트롤 상태를 처리하는 부분이다.
		출발지점과 도착지점의 값을 바꿔줬다.*/
		else if (_unit_state == UnitState::patrol) {
			std::swap(_move_vec2, _my_pos_vec2);
		}
	}
	else {
		// 현재 유닛 위치를 저장
		Vec2 unit_position = this->getPosition();
		// 목표 위치에서 유닛 위치를 뺀다
		Vec2 dir = _move_vec2 - unit_position;
		// 결과값을 정규화한다.
		dir.normalize();
		// 정규화 후 방향을 확인한다.
		check_dir(dir);

		// 정규화한 값에 이동속도를 곱한 후 현재 위치에 더한다.
		Vec2 tmp = unit_position + (dir * _unit_info2->move_speed);
		// 위치를 변경한다.
		this->setPosition(tmp);
	}
}

/*정규화된 값으로 방향을 확인하는 함수다
안쪽의 if문이 무척 많아 보인다.
개선의 여지가 있다는 느낌은 있지만
방향을 계산하는 벡터와 정규화에 대한 지식이 얕아 단순하게 코딩해놨다.

각 값이 방향을 가르키는것도 숫자를 넣어보고 결과값을 보고 알게된것
관련 지식이 쌓이면 수정해야 될 부분이다.*/

// 방향을 확인한다.
void Unit::check_dir(const cocos2d::Vec2 & _dir) {
	// 정규화된 값을 받아야한다.

	// y값이 0.33f보다 높은지 확인한다.
	if (_dir.y > up_right_left2) {
		// y값이 0.99f 보다 높은지 확인한다.
		if (_dir.y > up)						_unit_dir = Direction::up;
		// y값이 0.66f 보다 높은지 확인한다.
		else if (_dir.y > up_right_left1) 		_unit_dir = (_dir.x > 0) ? Direction::up_right1 : Direction::up_left1;
		// 나머지는 0.33f보다 높고 0.66f보다 낮다.
		else                         			_unit_dir = (_dir.x > 0) ? Direction::up_right2 : Direction::up_left2;
	}
	// y값이 -0.33f보다 높은지 확인한다.
	else if (_dir.y > down_right_left1) {
		// y값이 0.1f보다 높은지 확인한다.
		if (_dir.y > up_right_left3)			_unit_dir = (_dir.x > 0) ? Direction::up_right3 : Direction::up_left3;
		// y값이 -0.1f 보다 높은지 확인한다.
		else if (_dir.y > right_left)			_unit_dir = (_dir.x > 0) ? Direction::right : Direction::left;
		// 나머지는 -0.33보다 높고 -0.1f보다 낮다.
		else									_unit_dir = (_dir.x > 0) ? Direction::down_right1 : Direction::down_left1;
	}
	// 나머지는 -0.33보다 낮다.
	else {
		// y값이 -0.66f보다 높은지 확인한다.
		if (_dir.y > -down_right_left2)			_unit_dir = (_dir.x > 0) ? Direction::down_right2 : Direction::down_left2;
		// y값이 -0.99f보다 높은지 확인한다.
		else if (_dir.y > down_right_left3)		_unit_dir = (_dir.x > 0) ? Direction::down_right3 : Direction::down_left3;
		// 나머지는 -0.99보다 낮다.
		else                             		_unit_dir = Direction::down;
	}
}

/*상태를 설정하는 함수
상태를 설정하면서 현재 프레임 값도 초기화 하고 있다.
애니메이션 종류가 바뀔때 프레임 초기화를 하지 않으면 부자연스럽거나
잘못된 값에 접근하여 터지기 때문에 꼭 해당 함수로 접근해야 한다.

상태를 표현하는 변수 자체는 private 이지만
멤버 변수라서 언제든 접근해서 변경이 가능하다
유닛의 상태 값을 관리하는 클래스를 만들어서
해당 클래스를 통해서만 상태값을 조작하도록 한다면 좀 더 캡슐화가 되지 않을까 하지만
클래스 개수가 너무 늘어나는게 우려스럽기도 하다

하지만 set_state 함수를 거치지않고 변수에 직접 대입시켜 문제가 생기는것보단
더 안전할것으로 보인다.*/

// 수정요망

// 상태를 설정한다.
void Unit::set_state(const UnitState _state) {
	if (_unit_state != _state) {
		// 상태를 설정한다.
		_unit_state = _state;
		// 애니메이션 프레임을 초기화한다.
		_unit_animation->init_frame();
	}
}