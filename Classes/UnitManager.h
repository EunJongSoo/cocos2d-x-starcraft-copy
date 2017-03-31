#ifndef UNIT_MANAGER_H_
#define UNIT_MANAGER_H_

#include "Header.h"

class UnitManager {
public:
	UnitManager();
	~UnitManager();

	void create_unit(unit_type _type, const float _pos_x, const float _pos_y);

private:
	std::vector<Unit*> unit_vector;

};

#endif // !UNIT_MANAGER_H_
