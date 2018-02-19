/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : AIManager.h
****************************/

#ifndef AI_MANAGER_H_
#define AI_MANAGER_H_

class PathFindingManager;

namespace cocos2d {
	class Vec2;
}

class AIManager {
public:
	AIManager();
	~AIManager();

	// 길을 찾는 함수
	// 자기위치, 목표위치를 줍니다.
	void path_finding(const cocos2d::Vec2& _start_pos, const cocos2d::Vec2& _end_pos);

private:
	PathFindingManager * path_finding_manager;

};

#endif
