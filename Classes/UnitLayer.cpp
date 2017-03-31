#include "UnitLayer.h"
#include "UnitManager.h"
#include "Unit.h"

using namespace cocos2d;

UnitLayer::UnitLayer()
{
}

UnitLayer::~UnitLayer()
{
}

bool UnitLayer::init()
{
	if (!Layer::init()) return false;


	unit_manager = new UnitManager();

	unit_manager->add_player();
	unit_manager->add_player();
	Unit* unit1 = unit_manager->create_unit(unit_type::marine, PlayerUnitManager::player_color::red, 100.0f, 100.0f);
	this->addChild(unit1);
	this->addChild(unit_manager->create_unit(unit_type::marine, PlayerUnitManager::player_color::blue, 100.0f, 150.0f));

	return true;
}

void UnitLayer::create_unit()
{

}
