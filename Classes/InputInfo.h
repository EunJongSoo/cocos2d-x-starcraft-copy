#ifndef INPUT_INFO_H_
#define INPUT_INFO_H_

class MouseInfo;

class InputInfo {
public:
	InputInfo() : 
		mouse_order(false),
		mouse(nullptr)
		{}
	~InputInfo() {}

	inline bool get_mouse_order() const {	return mouse_order;	}
	inline MouseInfo * get_mouse_info() const { return mouse; }
	inline void set_mouse_order(const bool _order) { mouse_order = _order; }
	inline void set_mouse_info(MouseInfo * const _mouse) {	mouse = _mouse;	}

private:
	bool mouse_order;
	MouseInfo* mouse;

};

#endif // !INPUT_INFO_H_

