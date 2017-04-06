#include "UnitLayer.h"
#include "UnitManager.h"
#include "Unit.h"
#include "Point.h"

using namespace cocos2d;

UnitLayer::UnitLayer() {}
UnitLayer::~UnitLayer() {}

bool UnitLayer::init()
{
	if (!Layer::init()) return false;

	unit_manager = new UnitManager();

	// �ӽ� �ۼ� �κ�
	unit_manager->add_player();
	unit_manager->add_player();
	this->create_unit(unit_type::marine, player_color::red, eun::Point(100.0f, 100.0f));
	this->create_unit(unit_type::marine, player_color::blue, eun::Point(100.0f, 100.0f));
	
	return true;
}

// ���� ���� �Ѵ�.
void UnitLayer::create_unit(const unit_type _type, const player_color _color, const eun::Point& _point) {
	// �Ű������� ������ �����Ѵ�. 
	Unit* unit = unit_manager->create_unit(_type, _color, _point);
	// ���̾� �ڽ����� �߰��Ѵ�.
	this->addChild(unit);
}

// �÷��̾� ���� �Ŵ��� ��ȯ
std::vector<PlayerUnitManager*>& UnitLayer::get_unit_manager_vector() const{
	return unit_manager->get_unit_manager_vector();
}
