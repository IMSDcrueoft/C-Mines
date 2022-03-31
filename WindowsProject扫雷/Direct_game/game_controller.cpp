#include"game_controller.h"

game_level* game_controller::currentlevel;
DWORD game_controller::start;
DWORD game_controller::end;
bool game_controller::Loading;

void game_controller::Init()
{
	Loading = true;
	currentlevel = 0;
}

void game_controller::LoadInitialLevel(game_level* Level) 
{
	Loading = true;
	currentlevel = Level;
	currentlevel->Load();
	Loading = false;
}
void game_controller::SwitchLevel(game_level* Level) 
{
	Loading = true;
	currentlevel->Unload();
	Level->Load();
	delete currentlevel;
	currentlevel = Level;
	Loading = false;
}

void game_controller::Render()
{
	if (Loading)return;

	start = (DWORD)GetTickCount64();

	currentlevel->Render();

	//限制刷新速度为最高1000/33即30帧
	end = (DWORD)GetTickCount64();

	if ((end - start) < interval)
		Sleep(end - start);
}
void game_controller::Update()
{
	if (Loading)return;
	currentlevel->Update();
}

game_level * game_controller::Getcurrentlevel()
{
	return currentlevel;
}
