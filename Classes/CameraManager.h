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
	// ����Ʈ ī�޶� ������ ����
	cocos2d::Camera* main_camera;

	// ��ũ�� �Ǵ� ������ ��Ÿ���� ����
	float scroll_x;
	float scroll_y;

	// ī�޶� �⺻ ��ǥ��, ó�� ī�޶� ��ǥ�� 320, 240 �̴�.
	const float camera_origin_x;
	const float camera_origin_y;

	// ī�޶� ��ũ�ѽ� �̵��ӵ�
	const float tile_size;
	const float lower_limit;
	const float higher_limit_x;
	const float higher_limit_y;
};

#endif // !CAMERA_MANAGER_H_
