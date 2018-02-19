/****************************
������ : 2017-02-19
�ۼ��� : ������
���ϸ� : AIManager.h
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

	// ���� ã�� �Լ�
	// �ڱ���ġ, ��ǥ��ġ�� �ݴϴ�.
	void path_finding(const cocos2d::Vec2& _start_pos, const cocos2d::Vec2& _end_pos);

private:
	PathFindingManager * path_finding_manager;

};

#endif
