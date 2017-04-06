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
// �Լ� ������ �� �������ؼ� ������ �ʿ��ϴ�.
bool UnitManager::add_player() {
	// �÷��̾� ������ �÷��̾��� ���ڷ� �����Ѵ�.
	player_color color = (player_color)(player_unit_manager_vector.size());
	
	// ������ ����ü ���� max ���� Ȯ���Ѵ�.
	bool is_max = (color == player_color::max);

	// max�� �ƴϸ� �Ŵ����� �߰��Ѵ�.
	if (!is_max) {
		PlayerUnitManager* manager = new PlayerUnitManager(color, player_type::user);
		player_unit_manager_vector.push_back(manager);
	}
	
	// �÷��̾� �߰� ���θ� ��ȯ�Ѵ�.
	// max�� �Ǹ� ������ �����ϱ� ������ !�� �ٿ��ش�.
	return !is_max;

	// �ʿ���
	// �÷��̾� ���ڰ� �ִ밡 �ƴϸ� �÷��̾ �߰��ϰ�
	// �ִ�� �÷��̾ �߰� ���� �ʴ´�.
	// �÷��̾� �߰� ���θ� ��ȯ�Ѵ�.
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
std::vector<PlayerUnitManager*>& UnitManager::get_unit_vector() {
	return player_unit_manager_vector;
}

