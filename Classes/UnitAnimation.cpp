/****************************
수정일 : 2018-03-20
작성자 : 은종수
파일명 : UnitAnimation.cpp
****************************/

#include "UnitAnimation.h"
#include "TemplateSingleton.h"
#include "ResourcesManager.h"

using namespace cocos2d;

/* 유닛 애니메이션의 생성자
멤버 변수의 초기화와 초기화 함수를 호출한다.
색상을 받지 않았을때의 생성자이지만 실제 게임에선 색상이 없을수 없으니
의미가 없을수도 있다.*/
UnitAnimation::UnitAnimation(const unit_type _type, cocos2d::Sprite * const _sprite):
	frame(0),
	dt(0.0f),
	color(player_color::none),
	unit_sprite(_sprite)
{
	this->init_unit_animation(_type);
}

/* 위와 같은데 색상을 받는 점이 다르다*/
UnitAnimation::UnitAnimation(const unit_type _type, player_color _color, Sprite* const _sprite) :
	frame(0), 
	dt(0.0f),
	color(_color),
	unit_sprite(_sprite)
{
	this->init_unit_animation(_type);
}

/* 만들어진 유닛 또는 이팩트가 소멸하면 동적할당한 클립도 같이 없애준다.*/
UnitAnimation::~UnitAnimation() {
	for (clip* _clip : clip_vector) {
		SAFE_DELETE(_clip);
	}
	clip_vector.clear();
}

/* 유닛 애니메이션을 초기화하는 함수다.
미완성 부분이다 데이터를 불러오는 부분이 직접 입력되어 있는데
유닛별로 별도의 지정된 값을 불러올 체계를 구축해되는 부분이다.

당장은 마린만 이미지를 등록했기 때문에 마린의 대기, 이동, 공격, 죽었을때와 공격 이팩트
애니메이션 클립을 초기화 시키고 있다.*/
void UnitAnimation::init_unit_animation(const unit_type _type) {
	// 데이터 불러오는 부분
	//dataload(_type);
	/*char str[16];
	int i;
	int j;
	int k;*/

	// 불러온 데이터로 세팅
	//this->init_animation(move, str, i, j, k);

	switch (_type)
	{
	case marine: {
		this->init_clip(create_clip(UnitState::idle), "marine", 1, 0, 1);
		this->init_clip(create_clip(UnitState::move), "marine", 9, 68, 9);
		this->init_clip(create_clip(UnitState::attack), "marine", 8, 51, 2, 3, -17);
		this->init_clip(create_clip(UnitState::die), "marine", 8, 221);
		break;
	}
	case marine_weapon: {
		this->init_clip(create_clip(UnitState::idle), "tspark", 15, 0);
	}
	default:
		break;
	}
	
}

/* 클립 벡터에서 매개변수로 받은 상태의 클립을 찾고 
찾아서 run_clip_aniamtion에 시간과 방향 프레임 값을 넘기는데
기본은 0 프레임이다.

그런데 마린이 공격할때만 2라는 프레임을 던진다.
처음 재생할때는 0 프레임부터 재생을 시키지만
그 다음부터는 2프레임부터 재생시키게 하기 위해서 2라는 숫자를 던져준다.

매개변수를 넘기는 부분이 유닛 클래스이기 때문에 뭔가 부적절한 상태인데
당장 방법이 없어서 땜빵식으로 처리된 부분이다.

case UnitState::attack: {
_unit_animation->run_action_aniamtion(UnitState::attack, _dt, _unit_dir, 2);

유닛 클래스의 어택 처리 부분을 보면 가장 마지막에 2라고 
직접 입력한 숫자가 보이는데 잘못되었다.

어디선가 데이터를 끌고오게 해서 유닛별로 적용되도록 해야될 부분이며
유닛 애니메이션 내에서 정해져야 할 부분이다

수정이 필요한데 아직 유닛별 데이터를 관리할 부분이 작업되지 않아
수정순서가 뒤로 밀린다.
*/
bool UnitAnimation::run_action_aniamtion(UnitState _state, const float _dt, const int _dir) {
	int frame = 0;
	
	if (_state == UnitState::attack) {
		frame = 2;
	}
	else if (_state == UnitState::patrol) {
		_state = UnitState::move;
	}

	for (clip* _clip : clip_vector) {
		if (_clip->state == _state) {
			return run_clip_aniamtion(_clip, _dt, _dir, frame);
		}
	}
}

/* 프레임과 시간을 0으로 초기화 한다.
애니메이션의 상태가 변경될때 호출되고 있다.
*/
void UnitAnimation::init_frame() {
	frame = 0;
	dt = 0;
}

/* 이미지를 반전 시키는 함수다
코코스의 Sprite에서 제공되는 기능이다.
매개변수로 왼쪽인지 확인하고 현재 이미지가 좌우반전됬는지 확인한다.

기본 이미지가 오른쪽만 있기 때문에 좌우반전이 되지 않았다면 오른쪽 이미지이며
오른쪽 이미지는 좌우반전이 되지 않았기 때문에 false가 반환된다

그리고 왼쪽이 true일 경우 서로 다르기 때문에 좌우 반전을 시켜서
이미지를 왼쪽이미지로 바꾼다.
*/
void UnitAnimation::flipped_sprite_x(const bool _is_left) {
	if (_is_left != unit_sprite->isFlippedX()) {
		unit_sprite->setFlippedX(_is_left);
	}
}

/* 클립을 만들어 클립 벡터에 넣어준다.
만들어진 클립은 초기화 시켜줘야 하기 때문에 반환해준다.*/
UnitAnimation::clip * UnitAnimation::create_clip(const UnitState _state)
{
	clip* _clip = new clip();
	_clip->state = _state;
	clip_vector.push_back(_clip);
	return _clip;
}

/* 클립을 초기화 해준다.
애니메이션에 따라서 클립을 초기화 하는 방법이 다르다
정확하게는 추출한 이미지의 순서에 맞춰서 초기화 하는 방법이 다르다

클립은 한 애니메이션이 순서대로 담아 만든다
하지만 스타크래프트에서 추출한 이미지는 애니메이션 별로 정렬되어 있지 않고
그 때문에 이미지가 정렬된 규칙대로 불러와서 클립에 저장하고 있다.

마린을 보면 0~16번 이미지가 모두 대기 이미지다.
그런데 위에서 시계방향으로 아래쪽까지 9방향의 이미지가 나열되는데
아래쪽을 빼고는 모두 2장씩이며 위 아래를 제외한 나머지 7방향을 좌우 반전 시키면
총 16방향을 바라보는 마린 이미지가 나온다

어쨋든 17장이 방향만 다른 같은 그림이고
이걸 애니메이션으로 만들려면 17장씩 건너띄면서 클립에 저장해야 된다.

그런데 공격 모습이나 죽는 모습은 또 다르다.
해서 각 각 애니메이션에 맞게 클립을 불러오게 만들다 보니 3개가 만들어졌다.

현재는 클립을 유닛 애니메이션에서 만들어서 초기화 한다.
그런데 이 클립이 유닛이 만들어 질때마다 만들어지면
똑같은걸 계속 만드니까 낭비가 된다.

아무래도 클립도 리소스 매니저에 넘겨버리고
유닛이 만들어지면 리소스 매니저에 클립을 불러와서 사용하도록 만들어야겠다.
*/
void UnitAnimation::init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base) {
	cocos2d::Texture2D* texture = nullptr;
	_clip->max_frame = _max_frame;
	char str[16];
	// 모션 수
	for (int ani_count = 0; ani_count < _max_frame; ++ani_count) {
		sprintf_s(str, sizeof(str), "%s%04d.bmp", _str, _base + ani_count);
		assert(texture = load_texture(str, color));
		add_texture(_clip, texture);
	}
}

void UnitAnimation::init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count) {
	cocos2d::Texture2D* texture = nullptr;
	_clip->max_frame = _max_frame;
	char str[16];
	// 방향 수
	for (int dir = 0; dir < 9; ++dir) {
		int dir2 = dir * 2;
		// 애니메이션 수
		for (int ani_count = 0; ani_count < _ani_count; ++ani_count) {
			sprintf_s(str, sizeof(str), "%s%04d.bmp", _str, _base + dir2 + (ani_count * 17));
			assert(texture = load_texture(str, color));
			add_texture(_clip, texture);
		}
	}
}

void UnitAnimation::init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num) {
	_clip->max_frame = _max_frame;
	char str[16];
	cocos2d::Texture2D* texture = nullptr;
	// 방향 수
	for (int dir = 0; dir < 9; ++dir) {
		int dir2 = dir * 2;
		int img_num1 = dir2 + 17;
		int img_num2 = dir2 + 34;
		sprintf_s(str, sizeof(str), "%s%04d.bmp", _str, img_num1);
		assert(texture = load_texture(str, color));
		add_texture(_clip, texture);
		sprintf_s(str, sizeof(str), "%s%04d.bmp", _str, img_num2);
		assert(texture = load_texture(str, color));
		add_texture(_clip, texture);
		for (int loop = 0; loop < _loop; ++loop) {
			// 애니메이션 수
			for (int ani_count = 0; ani_count < _ani_count; ++ani_count) {
				sprintf_s(str, sizeof(str), "%s%04d.bmp", _str, _base + dir2 + (ani_count * _num));
				assert(texture = load_texture(str, color));
				add_texture(_clip, texture);
			}
		}
	}
}

/* 클립에서 순서대로 이미지를 변경하는 함수다.
이 함수를 호출하는 run_action_aniamtion에서 유닛의 상태를 먼저 확인해서
그 상태의 클립을 매개변수로 넘긴다.

함수가 한번 호출될때마다 시간을 더하는데 0.03초는 별다른 기준없이 정한 숫자라서 임시적이다
방향은 Header.h 파일에 enum으로 정의되어 있다.

enum으로 정의된 숫자를 보면 up, down, right는 10 보다 작고, left는 10보다 크다
그렇기 때문에 매개변수로 받은 _dir이 10보다 크면 왼쪽 10보다 작으면 오른쪽이다.

이렇게 방향을 확인한 다음에 _dir에서 10을 빼주는 이유는 
이미지가 오른쪽 이미지 뿐이기 때문이다.

이건 클립에 이미지가 쌓이는 순서를 먼저 알아야 하는데
방향 별로 애니메이션이 순서대로 쌓여있다.

예를 들면 1~9까지 위로 걷는 애니메이션 10~18까지 오른쪽으로 걷는 애니메이션 
19~27까지 아래로 걷는 애니메이션인거다

그리고 왼쪽으로 걷는 애니메이션은 없다
오른쪽으로 걷는 애니메이션을 불러오고
Unit Sprite를 반전 시켜버린다.

now_frame은 현재 frame에 방향, 그리고 해당 클립 애니메이션의 최대 프레임을 곱한다.
예를 들면 2차원 배열을 1차원 배열로 만들어 접근하는것과 같은 방식이다.

그리고 현재 프레임이 최대 프레임(마지막 애니메이션)이면 
매개변수로 받은 프레임 재시작 시점으로 변수를 초기화 해서 반복한다.

이 부분은 다른 애니메이션은 다 0인데 
마린이 공격을 반복할때 2~3번 애니메이션만 반복해서 작성되었다.*/
bool UnitAnimation::run_clip_aniamtion(const clip* const _clip, const float _dt, const int _dir, const int _frame) {
	dt += _dt;
	if (0.03f > dt) return false;
	dt = 0;

	bool is_left = _dir > Direction::left_check;
	int tmp_dir = is_left ? _dir - 10 : _dir;
	flipped_sprite_x(is_left);
	
	int now_frame = frame++ + tmp_dir * _clip->max_frame;

	unit_sprite->setTexture(_clip->animation_vector[now_frame]);
	bool b = frame >= _clip->max_frame;
	if (b) {
		frame = _frame;
	}
	return b;
}

/* Sprite의 이미지를 변경할때 사용하는 Texture2D를 리소스 매니저에서 불러온다.
자세한건 리소스 매니저 코드를 볼때 보도록 하자*/
cocos2d::Texture2D * UnitAnimation::load_texture(const char * const _str, const player_color _color)
{
	auto resources_manager = TemplateSingleton<ResourcesManager>::get_instance();
	return resources_manager->load_texture2d(_str, _color);
}

/* 클립에 텍스쳐를 추가한다.*/
void UnitAnimation::add_texture(clip* const _clip, cocos2d::Texture2D* const _texture)
{
	_clip->animation_vector.push_back(_texture);
}
