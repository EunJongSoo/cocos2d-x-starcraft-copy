/****************************
수정일 : 2017-02-19
작성자 : 은종수
파일명 : AIManager.cpp
****************************/

#include "cocos2d.h"
#include "AIManager.h"
#include "PathFindingManager.h"

AIManager::AIManager() 
{
}

AIManager::~AIManager()
{
}


void AIManager::path_finding(const cocos2d::Vec2 & _start_pos, const cocos2d::Vec2 & _end_pos)
{
	// AiManager에서 어느 수준의 길찾기를 할건지 판단해서 node_size를 던져줘야함
	// AiManager에서 어느 수준의 길찾기를 할건지 판단해서 node_size를 던져줘야함
	// AiManager에서 어느 수준의 길찾기를 할건지 판단해서 node_size를 던져줘야함
	// AiManager에서 어느 수준의 길찾기를 할건지 판단해서 node_size를 던져줘야함

	path_finding_manager->finding_path(_start_pos.x, _start_pos.x, _end_pos.x, _end_pos.y, 1);

}