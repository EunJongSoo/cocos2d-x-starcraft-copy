#ifndef UNIT_LAYER_H_
#define UNIT_LAYER_H_

#include "cocos2d.h"
#include "Header.h"

// class 전방선언
class UnitManager;
class PlayerUnitManager;

class UnitLayer : public cocos2d::Layer {
public:
	UnitLayer();
	virtual ~UnitLayer();
	virtual bool init();
	CREATE_FUNC(UnitLayer);

	void create_unit(const unit_type _type, const player_color _color, const cocos2d::Vec2& _point);
	std::vector<PlayerUnitManager*>& get_unit_manager_vector() const;

private:
	UnitManager* unit_manager;
};
#endif // !UNIT_LAYER_H_
