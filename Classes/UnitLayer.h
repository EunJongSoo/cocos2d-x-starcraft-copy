#ifndef UNIT_LAYER_H_
#define UNIT_LAYER_H_

#include "cocos2d.h"

class UnitManager;
class Unit;

class UnitLayer : public cocos2d::Layer {
public:
	UnitLayer();
	virtual ~UnitLayer();
	virtual bool init();
	CREATE_FUNC(UnitLayer);

	void create_unit();
	std::vector<Unit*>& get_unit_array() const;
private:
	UnitManager* unit_manager;

};

#endif // !UNIT_LAYER_H_