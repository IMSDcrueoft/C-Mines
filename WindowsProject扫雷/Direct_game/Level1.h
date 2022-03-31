#pragma once
#include"game_level.h"
#include"GameMap.h"

#define block_size 0.70
#define sprite1_width 48
#define sprite1_height 48
#define sprite2_width 32
#define sprite2_height 56

//起始绘图位置
#define DrawX 13
#define DrawY 17
//绘制间隔
#define spacing 36
class Level1 :public game_level
{
	SpriteSheet * sprites1 =NULL;
	SpriteSheet * sprites2 =NULL;

	int frame = 0;
	int StartX = 0,StartY = 0;//绘图点
	int n[3] = {0,0,0};//用于存储数字

	Gamemap* a_MineField = NULL;
	int Field_Lv = 1;	//雷区尺寸
	int MineAmount_Lv = 1;	//地雷数量级别

public:
	void Load()	override;
	void Unload()  override;
	void Render()  override;
	void Update()  override;

	void LBUTTONDOWN(int mouseX,int mouseY) override;
	void RBUTTONDOWN(int mouseX, int mouseY) override;
	void MBUTTONDOWN(int mouseX, int mouseY) override;

	void ReStartLevel() override;
	void Cheating() override;
	void ChangeDifficulty(int degree)override;
	void ChangeSize(int degree)override;

	void ChangeMineLevel(int target);//更改难度:地雷数量
	void ChangeFieldLevel(int target);//改变地图尺寸	
};