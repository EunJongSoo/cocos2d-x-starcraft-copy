#ifndef PICKING_MANAGER_H_
#define PICKING_MANAGER_H_

#include <vector>

class Unit;
class input_info;

class PickingManager {
public:
	PickingManager();
	~PickingManager();

	void picking_unit(const input_info _input, const std::vector<Unit*> _unit_array);

private:


};

#endif
