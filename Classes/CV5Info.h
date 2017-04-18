#ifndef CV5_INFO_H_
#define CV5_INFO_H_

#include "Header.h"

class CV5Info {
public:
	// unsigned short index;
	// Unknwon

	// unsigned short flags;
	// 0x0001 = Edge?
	// 0x0004 = Cliff?
	// 0x0040 = Creep
	// 0x0080 = Unbuildable
	// 0x0n00 = Deprecated ground height?
	// 0x8000 = Buildable for Start Location and Beacons

	// unsigned short Left Edge
	// Not fully understood. Value matches Right Edge on connecting tiles.

	// unsigned short Top Edge
	// Not fully understood. Value matches Bottom Edge on connecting tiles.

	// unsigned short Right Edge
	// Not fully understood. Value matches Left Edge on connecting tiles.

	// unsigned short Bottom Edge
	// Not fully understood. Value matches Top Edge on connecting tiles.

	// unsigned short Unknown/Unused
	// Unknown/Unused

	// unsigned short Edge Up
	// Not fully understood. Edge piece has rows above it?
	// 1 = Basic edge piece.
	// 2 = Right edge piece.
	// 3 = Left edge piece.

	// unsigned short Unknown/Unused
	// Unknown/Unused

	// unsigned short Edge Down
	// Not fully understood. Edge piece has rows below it?
	// 1 = Basic edge piece.
	// 2 = Right edge piece.
	// 3 = Left edge piece.

	// unsigned short MegaTile References
	// 16 references to VF4 and VX4.

	struct CV5 {
		struct cv5_data {
			unsigned char something[20];
			unsigned short mega_tile_index[16];
		} group[4096];
	};
public:
	CV5Info();
	~CV5Info();
	
	bool load_data(const map_tile_set _tile);
	inline CV5* get_cv5_data() const { return cv5_data; }
private:
	CV5 * cv5_data;
};
#endif