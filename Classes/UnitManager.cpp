#include <vector>
#include "PlayerUnitManager.h"
#include "UnitManager.h"
#include "Unit.h"
#include "Point.h"

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
Unit* UnitManager::create_unit(const unit_type _type, const player_color _color, const eun::Point& _point) {
	// �ӽ� ���� ��ü�� �����.
	Unit* unit = nullptr;
	// �÷��̾� �Ŵ��� ���͸� �˻��Ѵ�.
	for (PlayerUnitManager* manager : player_unit_manager_vector) {
		// �Ŵ����� ������ Ȯ���ؼ� �Ű������� ���Ѵ�.
		if (manager->get_color() == _color) {
			// ������ ������ ������ �����ϰ� �ӽ� ��ü�� ��ȯ���� ���� �����͸� �����Ѵ�.
			unit = manager->create_unit(_type, _point);
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
bool UnitManager::add_player_manager(const bool _b, const player_color color)
{
	if (!_b) {
		// max�� �ƴϸ� �Ŵ����� �߰��Ѵ�.
		PlayerUnitManager* manager = new PlayerUnitManager(color, player_type::user);
		player_unit_manager_vector.push_back(manager);
	}
	// �÷��̾� �߰� ���θ� ��ȯ�Ѵ�.
	return !_b;
}

