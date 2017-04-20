#ifndef MAP_DATA_H_
#define MAP_DATA_H_

#include "MapFileInfo.h"
#include "CV5Info.h"
#include "VX4Info.h"
#include "VR4Info.h"
#include "WPEInfo.h"
#include "Header.h"

class MapData {
public:
	MapData(const char* _file_name) :
		mapfile_info(nullptr),
		cv5_info(nullptr),
		vx4_info(nullptr),
		vr4_info(nullptr),
		wpe_info(nullptr)
	{
		// 맵을 부르기 위해 필요한 정보
		mapfile_info = new MapFileInfo(_file_name);
		map_tile_set tile_set = mapfile_info->get_tile_set();

		if (cv5_info == nullptr) {
			cv5_info = new CV5Info();
			cv5_info->load_data(tile_set);
		}
		if (vx4_info == nullptr) {
			vx4_info = new VX4Info();
			vx4_info->load_data(tile_set);
		}

		if (vr4_info == nullptr) {
			vr4_info = new VR4Info();
			vr4_info->load_data(tile_set);
		}

		if (wpe_info == nullptr) {
			wpe_info = new WPEInfo();
			wpe_info->load_data(tile_set);
		}
	}
	~MapData() {
		SAFE_DELETE(mapfile_info);
		SAFE_DELETE(cv5_info);
		SAFE_DELETE(vx4_info);
		SAFE_DELETE(vr4_info);
		SAFE_DELETE(wpe_info);
	}

	MapFileInfo* mapfile_info;
	CV5Info* cv5_info;
	VX4Info* vx4_info;
	VR4Info* vr4_info;
	WPEInfo* wpe_info;
};

#endif // !MAP_DATA_H_