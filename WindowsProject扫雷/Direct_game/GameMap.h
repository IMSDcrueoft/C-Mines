#pragma once

#include <algorithm>//获取随机数用
#include <vector>
class Gamemap {

	int MineField_Width;	//雷区的宽度
	int MineField_Length;	//雷区的高度
	int MineAmount;		//地雷数量
	int FlagUseage;		//旗帜使用数量
	int ** MineField = nullptr;	//雷区矩阵
	int ** PlayerField = nullptr;	//玩家矩阵,0：未知，1：点开，2：falg，3：unknown
	bool Explode;
public:

	Gamemap(int Field_Lv, int MineAmount_Lv);
	~Gamemap();

	void CreateMap();

	int GetMineField_Width();
	int GetMineField_Length();
	int GetMinePoint(int x, int y);
	int GetPlayerPoint(int x, int y);
	bool GetExplode();

	bool judgeWin();//判断是否获胜
	void Spread(int x, int y);
	void ShowMines();
	int Flag_left();
	void useFlag();
	void cancelFlag();
	void Player_act(int x, int y, int value);
	void ItExplode();
	static int* Randperm(int Num, int amount);
};