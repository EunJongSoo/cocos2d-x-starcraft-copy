#include "CameraManager.h"
#include "cocos2d.h"

using namespace cocos2d;

CameraManager::CameraManager() :
	main_camera(nullptr),
	scroll_x(0.0f),
	scroll_y(0.0f),
	camera_origin_x(320.0f),
	camera_origin_y(240.0f),
	tile_size(32.0f),
	lower_limit(0.0f),
	higher_limit_x(0.0f),
	higher_limit_y(0.0f)
{
}
CameraManager::CameraManager(int _map_size_x, int _map_size_y):
	// cocos2d 기본 카메라 저장
	main_camera(nullptr),
	scroll_x(0.0f),
	scroll_y(0.0f),
	camera_origin_x(320.0f),
	camera_origin_y(240.0f),
	tile_size(32.0f),
	lower_limit(0.0f),
	higher_limit_x(tile_size * _map_size_x),
	higher_limit_y(tile_size * _map_size_y + (tile_size * 3))
	/*,tile_size(32.0f)*/
{
}

CameraManager::~CameraManager()
{
}

Vec2 CameraManager::camera_scroll(const Vec2 & _mouse_pos)
{
	// 마우스 위치로 스크롤 방향 확인
	check_dir(_mouse_pos);

	// 카메라 위치 임시저장
	Vec2 camera_pos = main_camera->getPosition();
	
	// 화면이 맵을 벗어나는지 확인
	check_screen_limit(camera_pos);
	
	// 이동 거리 계산
	Vec2 move_pos = Vec2(scroll_x, scroll_y) * tile_size;
	
	// 카메라 위치 변경
	main_camera->setPosition(camera_pos + move_pos);
	return move_pos;
}


void CameraManager::check_dir(const Vec2 & _pos) {
	// center
	set_scroll_direction(0.0f, 0.0f);
	if (_pos.y > 475.0f + get_origin().y) {						set_scroll_direction(0.0f, 1.0f);	// up
		if (_pos.x > 635.0f + get_origin().x)					set_scroll_direction(1.0f, 1.0f);	// up_rigth
		else if (_pos.x < 5.0f + get_origin().x) 				set_scroll_direction(-1.0f, 1.0f);	// up_left
	}
	else if (_pos.y < 5.0f + get_origin().y) {					set_scroll_direction(0.0f, -1.0f);	// down
		if (_pos.x > 635.0f + get_origin().x)					set_scroll_direction(1.0f, -1.0f);	// down_right
		else if (_pos.x < 5.0f + get_origin().x) 				set_scroll_direction(-1.0f, -1.0f);	// down_left
	}
	else if (_pos.x > 635.0f + get_origin().x)					set_scroll_direction(1.0f, 0.0f);			// right
	else if (_pos.x < 5.0f + get_origin().x) 					set_scroll_direction(-1.0f, 0.0f);		// left
}

void CameraManager::set_scroll_direction(float _x, float _y)
{
	scroll_x = _x;
	scroll_y = _y;
}

void CameraManager::check_screen_limit(const Vec2& _pos)
{
	float lower_limit_x = _pos.x - camera_origin_x + scroll_x;
	float lower_limit_y = _pos.y - camera_origin_y + scroll_y;

	float higher_limit_x = _pos.x + camera_origin_x + scroll_x;
	float higher_limit_y = _pos.y + camera_origin_y + scroll_y;

	if (lower_limit_x <= 0) {
		scroll_x = 0.0f;
	}
	if (lower_limit_y <= 0) {
		scroll_y = 0.0f;
	}
	if (higher_limit_x >= 4096.0f) {
		scroll_x = 0.0f;
	}
	if (higher_limit_y >= 4192.0f) {
		scroll_y = 0.0f;
	}
}


const Vec2& CameraManager::get_origin()
{
	if (!main_camera) main_camera = Camera::getDefaultCamera();
	return main_camera->getPosition() - Vec2(camera_origin_x, camera_origin_y);
}