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

	void set_super_node(SuperNode* _super_node);
private:
	std::vector<SuperNode*> super_node_vector;

};

#endif