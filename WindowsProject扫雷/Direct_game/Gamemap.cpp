#include "GameMap.h"

Gamemap::Gamemap(int Field_Lv, int MineAmount_Lv)
{
	MineField_Width = 0;
	MineField_Length = 0;
	MineAmount = 0;
	FlagUseage = 0;
	FlagUseage = 0;
	Explode = false;

	//设置地图尺寸
	switch (Field_Lv)
	{
	case 1:
		MineField_Width = 10;
		MineField_Length = 10;
		break;
	case 2:
		MineField_Width = 15;
		MineField_Length = 12;
		break;
	case 3:
		MineField_Width = 20;
		MineField_Length = 15;
		break;
	case 4:
		MineField_Width = 30;
		MineField_Length = 20;
		break;
	}
	//计算地雷数量
	MineAmount = MineField_Length * MineField_Width * (MineAmount_Lv * 6 + 9) / 100;//*10+5,最高难度约33%
	//创建矩阵
	MineField = new int*[MineField_Length];
	PlayerField = new int*[MineField_Length];
	//创建矩阵
	for (int i = 0; i < MineField_Length; i++)
	{
		MineField[i] = new int[MineField_Width];
		PlayerField[i] = new int[MineField_Width];
	}
	//初始化
	for (int i = 0; i < MineField_Length; i++)
		for (int j = 0; j < MineField_Width; j++)
		{
			MineField[i][j] = 0;
			PlayerField[i][j] = 0;
		}

	CreateMap();
}

void Gamemap::CreateMap()
{
	//获取地雷
	int *mines = Randperm((MineField_Length * MineField_Width - 1), MineAmount);

	//布雷
	for (int i = 0; i < MineAmount; i++)
		MineField[mines[i] / MineField_Width][mines[i] % MineField_Width] = -1;

	free(mines);//释放资源

	//计算数字
	for (int i = 0; i < MineField_Length; i++)
		for (int j = 0, temp; j < MineField_Width; j++)
		{
			temp = 0;
			if (MineField[i][j] != -1)
			{
				if (i - 1 >= 0 && j - 1 >= 0 && MineField[i - 1][j - 1] == -1)
					temp++;
				if (i - 1 >= 0 && j + 1 < MineField_Width && MineField[i - 1][j + 1] == -1)
					temp++;

				if (j - 1 >= 0 && MineField[i][j - 1] == -1)
					temp++;
				if (j + 1 < MineField_Width && MineField[i][j + 1] == -1)
					temp++;

				if (i - 1 >= 0 && MineField[i - 1][j] == -1)
					temp++;
				if (i + 1 < MineField_Length && MineField[i + 1][j] == -1)
					temp++;

				if (i + 1 < MineField_Length && j - 1 >= 0 && MineField[i + 1][j - 1] == -1)
					temp++;
				if (i + 1 < MineField_Length && j + 1 < MineField_Width && MineField[i + 1][j + 1] == -1)
					temp++;

				MineField[i][j] = temp;
			}
		}
}

Gamemap::~Gamemap()
{
	for (int i = 0; i < MineField_Length; i++)
	{
		delete[] MineField[i];
		delete[] PlayerField[i];
	}
	delete[] MineField;
	delete[] PlayerField;
}


int Gamemap::GetMineField_Width()
{
	return MineField_Width;
}

int Gamemap::GetMineField_Length()
{
	return MineField_Length;
}

int Gamemap::GetMinePoint(int x, int y)
{
	return MineField[x][y];
}

int Gamemap::GetPlayerPoint(int x, int y)
{
	return PlayerField[x][y];
}

bool Gamemap::GetExplode()
{
	return Explode;
}




using namespace std;

bool Gamemap::judgeWin()
{
	for (int i = 0; i < MineField_Length; i++)
		for (int j = 0; j < MineField_Width; j++)
		{
			if (MineField[i][j] == -1 && PlayerField[i][j] != 2)
				return false;
			else
				if (MineField[i][j] != -1 && PlayerField[i][j] != 1)
					return false;
		}

	return true;
}

void Gamemap::Spread(int x, int y)
{
	//上
	if (x - 1 >= 0 && PlayerField[x - 1][y] == 0 && MineField[x - 1][y] >= 0)
	{
		PlayerField[x - 1][y] = 1;

		if (MineField[x - 1][y] == 0)
			Spread(x - 1, y);
	}

	//下
	if (x + 1 < MineField_Length&&PlayerField[x + 1][y] == 0 && MineField[x + 1][y] >= 0)
	{
		PlayerField[x + 1][y] = 1;

		if (MineField[x + 1][y] == 0)
			Spread(x + 1, y);
	}

	//左
	if (y - 1 >= 0 && PlayerField[x][y - 1] == 0 && MineField[x][y - 1] >= 0)
	{
		PlayerField[x][y - 1] = 1;

		if (MineField[x][y - 1] == 0)
			Spread(x, y - 1);
	}

	//右
	if (y + 1 < MineField_Width&&PlayerField[x][y + 1] == 0 && MineField[x][y + 1] >= 0)
	{
		PlayerField[x][y + 1] = 1;

		if (MineField[x][y + 1] == 0)
			Spread(x, y + 1);
	}
}


void Gamemap::ShowMines()
{
	for (int i = 0; i < MineField_Length; i++)
		for (int j = 0; j < MineField_Width; j++)
		{
			if (MineField[i][j] == -1)
				PlayerField[i][j] = 2;
			else
				PlayerField[i][j] = 1;
		}
	FlagUseage = MineAmount;
}

int Gamemap::Flag_left()
{
	return ( MineAmount - FlagUseage);
}

void Gamemap::useFlag()
{
	FlagUseage++;
}

void Gamemap::cancelFlag()
{
	FlagUseage--;
}

void Gamemap::Player_act(int x, int y, int value)
{
	PlayerField[x][y] = value;
}

void Gamemap::ItExplode()
{
	Explode = true;
	for (int i = 0; i < MineField_Length; i++)
		for (int j = 0; j < MineField_Width; j++)
		{
			if (MineField[i][j] == -1)
				PlayerField[i][j] = 1;
		}
}
//rand()随机数,random_shuffle()乱序
int * Gamemap::Randperm(int Num, int amount)
{
	vector<int> temp;
	int *random = new int[amount];
	int i;

	for (i = 0; i <= Num; i++)
		temp.push_back(i);

	random_shuffle(temp.begin(), temp.end());

	for (i = 0; i < temp.size() && i < amount; i++)
		random[i] = temp[i];

	return random;
}
