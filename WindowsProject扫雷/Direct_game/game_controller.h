#pragma once

#include"game_level.h"
#define interval 33

class game_controller
{
	game_controller(){}
	static game_level* currentlevel;

	static DWORD start, end;
public:
	static bool Loading;

	static void Init();

	static void LoadInitialLevel(game_level* Level);
	static void SwitchLevel(game_level* Level);

	static void Render();
	static void Update();
	static game_level* Getcurrentlevel();
};