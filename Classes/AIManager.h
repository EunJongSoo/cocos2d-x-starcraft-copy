/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : AIManager.h
****************************/

#ifndef AI_MANAGER_H_
#define AI_MANAGER_H_

class MapTree;

class AIManager {
public:
	AIManager();
	~AIManager();

	void set_map_tree(MapTree* _map_tree);


private:
	MapTree* map_tree;


};

#endif
