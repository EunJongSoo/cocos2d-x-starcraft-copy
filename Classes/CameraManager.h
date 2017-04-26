#ifndef CAMERA_MANAGER_H_
#define CAMERA_MANAGER_H_

#include "Header.h"

namespace cocos2d {
	class Vec2;
	class Camera;
}

class CameraManager {
public:
	CameraManager(int _map_size_x, int _map_size_y);
	~CameraManager();

	cocos2d::Vec2 camera_scroll(const cocos2d::Vec2& _mouse_pos);
	const cocos2d::Vec2& get_origin();

private:
	CameraManager();
	void check_dir(const cocos2d::Vec2& _pos);
	void set_scroll_direction(float _x, float _y);
	void check_screen_limit(const cocos2d::Vec2& _pos);
	// 디폴트 카메라를 저장할 변수
	cocos2d::Camera* main_camera;

	// 스크롤 되는 방향을 나타내는 변수
	float scroll_x;
	float scroll_y;

	// 카메라 기본 좌표값, 처음 카메라 좌표는 320, 240 이다.
	const float camera_origin_x;
	const float camera_origin_y;

	// 카메라 스크롤시 이동속도
	const float tile_size;
	const float lower_limit;
	const float higher_limit_x;
	const float higher_limit_y;
};

#endif // !CAMERA_MANAGER_H_
