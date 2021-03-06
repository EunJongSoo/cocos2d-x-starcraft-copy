#include "UnitLayer.h"
#include "UnitManager.h"
#include "Unit.h"

UnitLayer::UnitLayer() {}
UnitLayer::~UnitLayer() {}

bool UnitLayer::init()
{
	if (!Layer::init()) return false;

	unit_manager = new UnitManager();

	// 임시 작성 부분
	unit_manager->add_player();
	unit_manager->add_player();
	this->create_unit(unit_type::marine, player_color::kWhite, cocos2d::Vec2(100.0f, 100.0f));
	this->create_unit(unit_type::marine, player_color::kRed, cocos2d::Vec2(100.0f, 150.0f));
	
	return true;
}

// 유닛 생성 한다.
void UnitLayer::create_unit(const unit_type _type, const player_color _color, const cocos2d::Vec2& _vec2) {
	// 매개변수로 유닛을 생성한다. 
	Unit* unit = unit_manager->create_unit(_type, _color, _vec2);
	assert(unit);
	// 레이어 자식으로 추가한다.
	this->addChild(unit);
}

// 플레이어 유닛 매니저 반환
std::vector<PlayerUnitManager*>& UnitLayer::get_unit_manager_vector() const{
	return unit_manager->get_unit_manager_vector();
}
