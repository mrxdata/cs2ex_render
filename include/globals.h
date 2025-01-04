#pragma once
#include <wtypes.h>
#include "../generated/enemies.pb.h"

namespace g {
	inline HDC hdcBuffer = NULL;
	inline HBITMAP hbmBuffer = NULL;
	inline UINT32 SCREEN_WIDTH = 1920;
	inline UINT32 SCREEN_HEIGHT = 1080;
	inline Enemies entity_list;
}