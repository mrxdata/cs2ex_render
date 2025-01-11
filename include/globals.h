#pragma once
#include <wtypes.h>
#include "../generated/enemies.pb.h"
#include "local_player.h"
#include "time_counter.h"

namespace g {
	inline HDC hdcBuffer = NULL;
	inline HBITMAP hbmBuffer = NULL;
	inline FLOAT SCREEN_WIDTH = 1920.0f;
	inline FLOAT SCREEN_HEIGHT = 1080.0f;
	inline FLOAT ASPECT_RATIO = SCREEN_WIDTH / SCREEN_HEIGHT;
	inline Enemies entity_list;
	inline LocalPlayer local_player = LocalPlayer();
	inline Timer timer;
}