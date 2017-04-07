#include <vector>
#include "PlayerUnitManager.h"
#include "UnitManager.h"
#include "Unit.h"
#include "cocos2d.h"

UnitManager::UnitManager() {}

UnitManager::~UnitManager() {
	// �Ŵ��� �����Ҵ� ����
	for (PlayerUnitManager* manager : player_unit_manager_vector) {
		SAFE_DELETE(manager);
	}
	// ���� ����
	player_unit_manager_vector.clear();
}

// �÷��̾� �߰�
bool UnitManager::add_player() {
	// �÷��̾� ������ �÷��̾��� ���ڷ� �����Ѵ�.
	// �÷��̾� ����(��)�� �����ϴ� Ŭ������ �ۼ� �ʿ�
	// �÷��̾� ����(��)�� �����ϴ� Ŭ������ �ۼ� �ʿ�
	// �÷��̾� ����(��)�� �����ϴ� Ŭ������ �ۼ� �ʿ�
	// �÷��̾� ����(��)�� �����ϴ� Ŭ������ �ۼ� �ʿ�
	// �÷��̾� ����(��)�� �����ϴ� Ŭ������ �ۼ� �ʿ�
	player_color color = (player_color)(player_unit_manager_vector.size());
	
	int manager_count = player_unit_manager_vector.size();
	// ������ ����ü ���� max ���� Ȯ���Ѵ�.
	return add_player_manager(max_player_manager == manager_count, color);
}


// ���� �����ϱ�
Unit* UnitManager::create_unit(const unit_type _type, const player_color _color, const cocos2d::Vec2& _vec2) {
	// �ӽ� ���� ��ü�� �����.
	Unit* unit = nullptr;
	// �÷��̾� �Ŵ��� ���͸� �˻��Ѵ�.
	for (PlayerUnitManager* manager : player_unit_manager_vector) {
		// �Ŵ����� ������ Ȯ���ؼ� �Ű������� ���Ѵ�.
		if (manager->get_color() == _color) {
			// ������ ������ ������ �����ϰ� �ӽ� ��ü�� ��ȯ���� ���� �����͸� �����Ѵ�.
			unit = manager->create_unit(_type, _vec2);
		}
	}
	// ���� �����͸� ��ȯ�Ѵ�.
	return unit;
}

// ���� ���͸� ��ȯ�Ѵ�.
std::vector<PlayerUnitManager*>& UnitManager::get_unit_manager_vector() {
	return player_unit_manager_vector;
}

// ���� �÷��̾� �Ŵ��� ���ڸ� Ȯ�� �� �÷��̾� �Ŵ����� �߰��Ѵ�.
bool UnitManager::add_player_manager(const bool _is_max, const player_color color)
{
	if (!_is_max) {
		// max�� �ƴϸ� �Ŵ����� �߰��Ѵ�.
		PlayerUnitManager* manager = new PlayerUnitManager(color, player_type::user);
		player_unit_manager_vector.push_back(manager);
	}
	// �÷��̾� �߰� ���θ� ��ȯ�Ѵ�.
	return !_is_max;
}
//
//int main()
//{
//	// �迭�� �ʱⰪ(���� �� �� ����)
//	int temp_arr[25] = { 0, }, temp, index_size = 24, n;
//	int i;
//
//	// �ӽ� �迭 �ʱ�ȭ
//	for (i = 0; i<25; i++)
//	{
//		temp_arr[i] = i + 1;
//	}
//	// rand()��� �ߺ����� �ʰ� �����
//	for (i = 0; i<25; i++)
//	{
//		n = rand() % (index_size + 1);
//
//		// ������ index�� ���� index swap�ϱ�
//		temp = temp_arr[n];
//		temp_arr[n] = temp_arr[index_size];
//		temp_arr[index_size] = temp;
//	}
//
//
//	return 0;
//}