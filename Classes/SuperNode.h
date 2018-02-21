/****************************
수정일 : 2017-02-21
작성자 : 은종수
파일명 : SuperNode.h
****************************/

#ifndef SUPER_NODE_H_
#define SUPER_NODE_H_

class MegaNode;

namespace std {
	template < typename T, typename A > class vector;
}

class SuperNode {
public:
	SuperNode(int _index);
	~SuperNode();

	MegaNode* get_mega_node(const int _num);
	void set_mega_node(MegaNode* _mega_node);
	void check_open_node();
	bool is_open_node(char _dir);
private:
	SuperNode();
	void set_open_node(char _dir);
	
	char open_node;
	int index;
	std::vector<MegaNode*> mega_node_vector;
};

#endif
