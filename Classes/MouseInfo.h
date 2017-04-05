#ifndef MOUSE_INFO_H_
#define MOUSE_INFO_H_

class MouseInfo {
public:
	enum mouse_state {
		none, L_down, L_dragging, L_drag, L_double, L_up, R_down, R_up
	};
public:
	MouseInfo() :
		state(mouse_state::none),
		start_pos_x(0.0f),
		start_pos_y(0.0f),
		end_pos_x(0.0f),
		end_pos_y(0.0f)
	{}
	~MouseInfo() {}

	inline void set_mouse_state(const int _state) {
		state = (mouse_state)(_state);
	}

	inline void set_start_pos(float _x, float _y) {
		start_pos_x = _x;
		start_pos_y = _y;
	}
	inline void set_end_pos(float _x, float _y) {
		end_pos_x = _x;
		end_pos_y = _y;
	}

	// 埃立 立辟
	inline mouse_state get_mouse_state() const { return state; }
	inline float get_start_pos_x() const { return start_pos_x; }
	inline float get_start_pos_y() const { return start_pos_y; }
	inline float get_end_pos_x() const { return end_pos_x; }
	inline float get_end_pos_y() const { return end_pos_y; }

	// 流立 立辟
	mouse_state state;
	float start_pos_x;
	float start_pos_y;
	float end_pos_x;
	float end_pos_y;
};

#endif // !MOUSE_INFO_H_
