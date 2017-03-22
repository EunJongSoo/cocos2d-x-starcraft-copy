#include "Unit.h"
#include "UnitAnimation.h"

using namespace cocos2d;

Unit::Unit() : _unit_state(unit_state::idle) {

	_unit_animation = UnitAnimation::create();
	this->addChild(_unit_animation);
}

Unit::~Unit() {
}

bool Unit::init() {

	assert(Node::init());

	return true;
}

void Unit::attack_unit() {
	_unit_state = unit_state::attack;
}

void Unit::move_unit() {
	_unit_state = unit_state::move;
	_unit_animation->run_action_animation();
}

void Unit::stop_unit() {
	_unit_state = unit_state::idle;
}

void Unit::patrol_unit() {
	_unit_state = unit_state::petrol;
}

void Unit::hold_unit() {
	_unit_state = unit_state::hold;
}
