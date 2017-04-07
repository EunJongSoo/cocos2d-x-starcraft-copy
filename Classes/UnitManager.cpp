#include <vector>
#include "PlayerUnitManager.h"
#include "UnitManager.h"
#include "Unit.h"
#include "cocos2d.h"

UnitManager::UnitManager() {}

UnitManager::~UnitManager() {
	// 매니저 동적할당 해제
	for (PlayerUnitManager* manager : player_unit_manager_vector) {
		SAFE_DELETE(manager);
	}
	// 벡터 비우기
	player_unit_manager_vector.clear();
}

// 플레이어 추가
bool UnitManager::add_player() {
	// 플레이어 색상은 플레이어의 숫자로 결정한다.
	// 플레이어 색상(팀)을 관리하는 클래스의 작성 필요
	// 플레이어 색상(팀)을 관리하는 클래스의 작성 필요
	// 플레이어 색상(팀)을 관리하는 클래스의 작성 필요
	// 플레이어 색상(팀)을 관리하는 클래스의 작성 필요
	// 플레이어 색상(팀)을 관리하는 클래스의 작성 필요
	player_color color = (player_color)(player_unit_manager_vector.size());
	
	int manager_count = player_unit_manager_vector.size();
	// 색상이 열거체 값이 max 인지 확인한다.
	return add_player_manager(max_player_manager == manager_count, color);
}


// 유닛 생성하기
Unit* UnitManager::create_unit(const unit_type _type, const player_color _color, const cocos2d::Vec2& _vec2) {
	// 임시 유닛 객체를 만든다.
	Unit* unit = nullptr;
	// 플레이어 매니저 벡터를 검사한다.
	for (PlayerUnitManager* manager : player_unit_manager_vector) {
		// 매니저의 색상을 확인해서 매개변수와 비교한다.
		if (manager->get_color() == _color) {
			// 색상이 같으면 유닛을 생성하고 임시 객체에 반환받은 유닛 포인터를 저장한다.
			unit = manager->create_unit(_type, _vec2);
		}
	}
	// 유닛 포인터를 반환한다.
	return unit;
}

// 유닛 벡터를 받환한다.
std::vector<PlayerUnitManager*>& UnitManager::get_unit_manager_vector() {
	return player_unit_manager_vector;
}

// 현재 플레이어 매니저 숫자를 확인 후 플레이어 매니저를 추가한다.
bool UnitManager::add_player_manager(const bool _is_max, const player_color color)
{
	if (!_is_max) {
		// max가 아니면 매니저를 추가한다.
		PlayerUnitManager* manager = new PlayerUnitManager(color, player_type::user);
		player_unit_manager_vector.push_back(manager);
	}
	// 플레이어 추가 여부를 반환한다.
	return !_is_max;
}
//
//int main()
//{
//	// 배열로 초기값(정렬 안 된 상태)
//	int temp_arr[25] = { 0, }, temp, index_size = 24, n;
//	int i;
//
//	// 임시 배열 초기화
//	for (i = 0; i<25; i++)
//	{
//		temp_arr[i] = i + 1;
//	}
//	// rand()사용 중복되지 않게 만들기
//	for (i = 0; i<25; i++)
//	{
//		n = rand() % (index_size + 1);
//
//		// 마지막 index와 나온 index swap하기
//		temp = temp_arr[n];
//		temp_arr[n] = temp_arr[index_size];
//		temp_arr[index_size] = temp;
//	}
//
//
//	return 0;
//}