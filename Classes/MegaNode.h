/****************************
수정일 : 2017-02-21
작성자 : 은종수
파일명 : MegaNode.h
****************************/

#ifndef MEGA_NODE_H_
#define MEGA_NODE_H_

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

namespace std {
	template < typename T, typename A > class vector;
}

class MiniNode;

class MegaNode {
public:
	MegaNode(int _index);
	~MegaNode();

	void set_mini_node(MiniNode* _mini_node);
	bool is_open_node(char _dir);
	void check_open_node();

private:
	MegaNode();
	void set_open_node(char _dir);
	
private:
	char open_node;								// 통행 가능한 방향을 표시함
	int index;									// 노드 인덱스
	std::vector<MiniNode*> mini_node_vector;

};

#endif