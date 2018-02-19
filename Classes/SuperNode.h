#ifndef SUPER_NODE_H_
#define SUPER_NODE_H_

class MegaNode;

namespace std {
	template < typename T, typename A > class vector;
}

class SuperNode {
public:
	SuperNode();
	~SuperNode();

	MegaNode* get_mega_node(const int _num);
	void set_mega_node(MegaNode* _mega_node);
	void check_open_node();
	bool is_open_node(char _dir);
private:
	void set_open_node(char _dir);

	std::vector<MegaNode*> mega_node_vector;
	char open_node;

};

#endif
