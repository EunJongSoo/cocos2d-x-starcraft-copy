/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : MapTree.h
****************************/

#ifndef MAP_TREE_H_
#define MAP_TREE_H_

class SuperNode;

namespace std {
	template < typename T, typename A > class vector;
}

class MapTree {
public:
	MapTree();
	~MapTree();

	enum class NodeSize {
		mini_node = 1,
		mega_node = 4,
		super_node = 8

	};

	void set_super_node(SuperNode* _super_node);
	bool is_open_node(const float x, const float y, const char _dir, const int _node_size);
private:
	std::vector<SuperNode*> super_node_vector;

};

#endif