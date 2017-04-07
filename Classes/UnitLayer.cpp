#include "UnitLayer.h"
#include "UnitManager.h"
#include "Unit.h"

UnitLayer::UnitLayer() {}
UnitLayer::~UnitLayer() {}

bool UnitLayer::init()
{
	if (!Layer::init()) return false;

	unit_manager = new UnitManager();

	// �ӽ� �ۼ� �κ�
	unit_manager->add_player();
	unit_manager->add_player();
	this->create_unit(unit_type::marine, player_color::red, cocos2d::Vec2(100.0f, 100.0f));
	this->create_unit(unit_type::marine, player_color::blue, cocos2d::Vec2(100.0f, 150.0f));
	
	return true;
}

// ���� ���� �Ѵ�.
void UnitLayer::create_unit(const unit_type _type, const player_color _color, const cocos2d::Vec2& _vec2) {
	// �Ű������� ������ �����Ѵ�. 
	Unit* unit = unit_manager->create_unit(_type, _color, _vec2);
	// ���̾� �ڽ����� �߰��Ѵ�.
	this->addChild(unit);
}

// �÷��̾� ���� �Ŵ��� ��ȯ
std::vector<PlayerUnitManager*>& UnitLayer::get_unit_manager_vector() const{
	return unit_manager->get_unit_manager_vector();
}
