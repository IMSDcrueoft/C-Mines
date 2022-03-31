#pragma once
#include"Graphics.h"
#include"SpriteSheet.h"
#include<time.h>

class game_level
{
protected:
	static Graphics* graphics;
	static HWND hWnd;
public:
	static void Init(HWND hwnd,Graphics* gfx)
	{
		srand((unsigned int)time(0));//用于初始化随机数种子

		hWnd = hwnd;
		graphics = gfx;
	}

	virtual void Load() =  0 ;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
/// <remarks>
/// You may have some additional information about this class.
/// </remarks>
	virtual void LBUTTONDOWN(int mouseX, int mouseY) = 0;
	virtual void RBUTTONDOWN(int mouseX, int mouseY) = 0;
	virtual void MBUTTONDOWN(int mouseX, int mouseY) = 0;
	virtual void ReStartLevel() = 0;
	virtual void Cheating() = 0;
	virtual void ChangeDifficulty(int degree) = 0;
	virtual void ChangeSize(int degree) = 0;

};