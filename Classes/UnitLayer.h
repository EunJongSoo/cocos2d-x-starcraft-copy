#ifndef UNIT_LAYER_H_
#define UNIT_LAYER_H_

#include "cocos2d.h"
#include "Header.h"

// class 穿号識情
class UnitManager;
class PlayerUnitManager;

// namespace class 穿号識情
namespace eun {
	class Point;
}

class UnitLayer : public cocos2d::Layer {
public:
	UnitLayer();
	virtual ~UnitLayer();
	virtual bool init();
	CREATE_FUNC(UnitLayer);

	void create_unit(const unit_type _type, const player_color _color, const eun::Point& _point);
	std::vector<PlayerUnitManager*>& get_unit_manager_vector() const;

private:
	UnitManager* unit_manager;
};
#endif // !UNIT_LAYER_H_
