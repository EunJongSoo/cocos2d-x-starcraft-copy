#ifndef MINI_NODE_H_
#define MINI_NODE_H_

// unsigned short flags - mini_tile_flags
// 0x0001 - Walkable
// 0x0002 - Mid
// 0x0004 - High(Mid and High unchecked = Low)
// 0x0008 - Blocks View
// 0x0010 - Ramp - Appears on the middle minitiles of most ramps/stairs.
// Rest unknown/unused

//struct VF4 {
//	struct vf4_data {
//		unsigned short flags[16];
//	} data[65536];
//};

class MiniNode {
public:
	enum class node_dir_check : char {
		up = 1,
		down = 2,
		left = 4,
		right = 8,
		up_left = 16,
		up_right = 32,
		down_left = 64,
		down_right = 128
	};

public:
	MiniNode();
	~MiniNode();
	
	bool is_walkable();
	bool is_open_node(char _dir);
	void set_open_node(char _dir);
	void set_mini_node(unsigned int _index, unsigned short _flag);
private:
	char open_node;
	unsigned int index;						// 노드 인덱스
	unsigned short mini_tile_flags;		// 미니 타일 플레그
};

#endif