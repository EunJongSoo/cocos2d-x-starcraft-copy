/****************************
수정일 : 2018-03-20
작성자 : 은종수
파일명 : UnitAnimation.h
****************************/

#ifndef UNIT_ANIMATION_H_
#define UNIT_ANIMATION_H_

#include "cocos2d.h"
#include "header.h"

 /* 유닛의 이미지를 변경해주는 클래스이다.
코코스에 있는 애니메이션을 사용하려고 하다가..
뭔지 기억이 안나는데 문제가 생겼다.에러가 엄청 터졌었다.

원인은 잘모르겠고 동작은 시켜야했고.. 
그래서 전에 다니던 학원 선생님께 배운 방법으로 클래스를 새로 만들었다.*/
class UnitAnimation {
public:
	/* 클립이라고 이름붙인 구조체를 하나 만들었다.
	클립이 뭐였더라..??;;
	
	구글에 검색하니 종이 찝어두는 클립이 나온다.;;
	이런 클립이 아니고 이미지? 영상? 을 모아두는걸 의미하는 클립이다.
	
	이 클립은 어떤 상태의 이미지인지 표시할 변수와
	이 클입에 있는 최대 이미지 숫자와
	이미지를 담아둘 벡터로 구성되어 있다.

	Texture2D는 코코스에서 이미지의 정보를 담아두는 클래스인데..
	이미지 하나하나의 기본정보를 담는달까..?? 

	코코스에서 제공되는 애니메이션 클래스도 f12눌러서 쭉쭉 내려가다보면 결국 이거 바꿔 먹었던거 같다.
	*/
	struct clip {
		UnitState state;
		unsigned int max_frame;
		std::vector<cocos2d::Texture2D*> animation_vector;
	};

	/* 이건 생성자, 유닛 마다 이미지 다르다.
	이 클래스는 유닛 하나하나에 다 붙어있다.
	
	당연히 유닛마다 불러오는 이미지가 달라야 하기 때문에 어떤 유닛인지를 구분하기 위해
	유닛 타입을 매개변수로 받는다 그리고 저 코코스 스프라이트는 유닛 자신을 받는다
	그래야 유닛의 그림을 바꿔주기 때문이다.
	
	유닛 애니메이션은 설계 구조상 유닛 클래스가 뭔지 모르기 때문에 
	유닛 애니메이션을 포함하고 있는 유닛 클래스가 자기 자신을 알려주는거다.

	아이고 주절주절..

	그 밑에 있는 오버로딩은 색상이다.
	스타크래프트는 플레이어마다 색상이 다르기 때문에 
	그 색상도 받아야지 색상에 맞는 이미지를 불러올수있다. 

	그렇게 생각하니 위에껀 쓸모가 없지 않은가 싶다.. 색상을 못던지면 무슨 쓸모란 말인가
	*/
	UnitAnimation(const unit_type _type, cocos2d::Sprite* const _sprite);
	UnitAnimation(const unit_type _type, const player_color _color, cocos2d::Sprite* const _sprite);
	~UnitAnimation();

	/* 유닛클래스에서 이 run_action_aniamtion을 호출해서 자신의 그림을 변경해준다.
	상태값은 어떤 애니메이션을 불러올지 필요하고
	
	_dt는 게임의 메인 루프문에서 쭉 타고 내려와서 더 아래쪽에서 시간을 체크할때 사용한다.
	0.05초가 되면 애니메이션을 그림을 하나씩 바꾸는데.. 이건 따로 기준을 정해놓은게 아니다
	지금 다시 보니까.. 좀 뭐가 이상하다

	dir은 현재 유닛이 바라보는 방향, 이 값으로 불러올 그림을 결정한다.
	
	마지막으로 프레임은 특정 프레임부터 애니메이션을 재생할때 사용하기 위해서 넣었다.
	공격을 할때 공격 준비 자세와 공격 자세가 있는데
	처음 쏠때나 공격 준비 자세가 필요하지 이 후에는 공격 자세만 반복하기 때문에 필요했다.

	성공적으로 애니메이션을 재생하면 성공여부를 반환해주고 있다.
	*/
	bool run_action_aniamtion(UnitState _state, const float _dt, int _dir = 0);

	/* 애니메이션을 출력할때 프레임이라는 변수를 1개씩 더하면서 출력하고 있다.
	그런데 상태값이 바뀌어 다른 애니메이션이 되면 프레임을 0번부터 출력해야되기 때문에
	초기화 함수를 만들었다.*/
	void init_frame();
private:
	UnitAnimation() {};
	/* 처음 애니메이션이 만들어졌을때 초기화 하는 함수다.*/
	void init_unit_animation(const unit_type _type);
	
	/* 이 함수는 이미지를 좌우 반전 시키는 함수다
	스타크래프트 이미지를 추출했는데 오른쪽 이미지만 있지 않은가
	
	내가 참고한 블로그는 직접 유닛들 이미지를 반전시켜서 저장하고 각각 불러오게 하던데
	나는 코드에서 반전 시켜 사용하기로 했다.

	과연 내가 유닛을 몇종이나 추가할지 모르겠지만 언제 그걸 다 반전시켜서 저장해둔단 말인가.
	*/
	void flipped_sprite_x(const bool _is_left);

	/* 유닛의 애니메이션을 저장할 클립을 만드는 함수다.
	그냥 상태값만 받아서 구조체하나 만드는 거라서 별건 없다.*/
	clip* create_clip(const UnitState _state);

	/*
	애니메이션 클립 하나 하나를 초기화 하는 함수다.
	클립 마다 들어가는 이미지 숫자가 다르다

	그리고 특정 구간만 반복해야되는 애니메이션이 있고
	특정 구간을 한번만 재생하는 애니메이션
	한번 재생하는 애니메이션과 반복되는 애니메이션이 같이 있는 애니메이션도 있다.

	마린만 구분했는데 3종류 였다

	순서대로 이동, 죽음, 공격이다.
	그래도 다른유닛도 저 3가지 분류를 벗어나지 않을거라 생각한다.

	어쨋든 분류에 따라서 요구하는 매개변수가 달라서 함수오버로딩으로
	3개를 만들었는데 잘했는지 아닌지 판단이 안된다

	일단.. 동작은 잘 된다
	*/
	void init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base);
	void init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count);
	void init_clip(clip* const _clip, const char* _str, const int _max_frame, const int _base, const int _ani_count, const int _loop, const int _num);

	/* run_action_aniamtion이 호출하는 함수다.
	run_action_aniamtion이 상태값으로 클립을 찾는다면 그 클립에서 이미지를 찾아서
	좌우반전 확인, 몇번째 이미지인지 확인하고 유닛의 이미지를 바꾼다.
	그리고 성공 여부를 반환하고 있다.*/
	bool run_clip_aniamtion(const clip* const _clip, const float _dt, const int _dir, const int _frame);

	/* 싱글톤으로 만든 리소스 매니저에서 리소스를 불러오는 함수다
	리소스 매니저의 함수를 호출한다*/
	cocos2d::Texture2D* load_texture(const char* const _str, const player_color _color);

	/* 애니메이션 클립에 이미지를 추가하는 함수다.*/
	void add_texture(clip* const _clip, cocos2d::Texture2D* const _texture);

	/* 생성자에서 받은 정보를 저장할 변수*/
	player_color color;
	unsigned int frame;
	float dt;

	/* 클립들을 저장해둘 벡터다
	특정 상태의 애니메이션을 요구하면 
	이 벡터에서 해당 상태의 클립을 찾고 이미지를 바꿔준다.*/
	std::vector<clip*> clip_vector;
	/* 생성자에서 받은 정보를 저장할 변수*/
	cocos2d::Sprite* unit_sprite;
};

#endif