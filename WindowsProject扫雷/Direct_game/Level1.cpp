#include "Level1.h"
#include "game_controller.h"
#include "../Resource.h"

void Level1::Load()
{
	sprites1 = new SpriteSheet(L"../game_res/tiles.myres", graphics, sprite1_width, sprite1_height);
	sprites2 = new SpriteSheet(L"../game_res/numbers.myres", graphics, sprite2_width, sprite2_height);

	frame = 0;
	StartX = 0;
	StartY = 0;
	Field_Lv = 1;
	MineAmount_Lv = 1;

	a_MineField = new Gamemap(Field_Lv, MineAmount_Lv);

}
void Level1::Unload()
{
	delete sprites1;
	delete sprites2;
	delete a_MineField;

	sprites1 = NULL;
	sprites2 = NULL;
	a_MineField = NULL;
}
void Level1::Render()
{
	//���沿��
	//��ɫ����
	graphics->ClearScreen(0.9f, 0.9f, 0.9f);
	//ɨ��
	//��ʼ����λ��
	StartX = DrawX;
	StartY = DrawY;
	//���ƶ���
	//ѡ����Ƶ���
	if (a_MineField->GetExplode())
		frame = 12;
	else
		frame = 11;

	switch (Field_Lv)
	{
	case 1:sprites1->Draw(frame, StartX + 155, StartY, 1); break;
	case 2:sprites1->Draw(frame, StartX + 245, StartY, 1); break;
	case 3:sprites1->Draw(frame, StartX + 335, StartY, 1); break;
	case 4:sprites1->Draw(frame, StartX + 515, StartY, 1); break;
	}
	//������ʾ��ʣ��������
	n[0] = (a_MineField->Flag_left()) / 100;
	n[1] = (a_MineField->Flag_left()) % 100 / 10;
	n[2] = (a_MineField->Flag_left()) % 10;

	for (int i = 0; i < 3; i++)	sprites2->Draw(n[i], StartX + sprite2_width * i, StartY - 5, 1);

	//����ש��
	StartY += 60;
	for (int i = 0; i < a_MineField->GetMineField_Length(); i++)
	{
		for (int j = 0; j < a_MineField->GetMineField_Width(); j++)
		{
			switch (a_MineField->GetPlayerPoint(i, j))
			{
			case 0:frame = 14; break;//δ֪

			case 1://�ڿ�
				switch (a_MineField->GetMinePoint(i, j))
				{
				case -1:frame = 8; break;//����

				case 0:frame = 13; break;//�հ�

				default:frame = a_MineField->GetMinePoint(i, j) - 1;//��Դ�������ô��ŵ�
				}break;

			case 2:frame = 9; break;//����

			case 3:frame = 10; break;//�ʺ�
			}

			sprites1->Draw(frame, StartX + spacing * j, StartY, (float)block_size);
		}
		StartY += 36;
	}
}
void Level1::Update()//��ʱ�ò���
{}
void Level1::ChangeMineLevel(int target)
{
	switch (MineAmount_Lv)
	{
	case 1:EnableMenuItem(GetMenu(hWnd), IDM_MINE_AMOUNT_LV1, MF_ENABLED); break;
	case 2:EnableMenuItem(GetMenu(hWnd), IDM_MINE_AMOUNT_LV2, MF_ENABLED); break;
	case 3:EnableMenuItem(GetMenu(hWnd), IDM_MINE_AMOUNT_LV3, MF_ENABLED); break;
	case 4:EnableMenuItem(GetMenu(hWnd), IDM_MINE_AMOUNT_LV4, MF_ENABLED); break;
	}
	switch (target)
	{
	case 1:EnableMenuItem(GetMenu(hWnd), IDM_MINE_AMOUNT_LV1, MF_GRAYED); break;
	case 2:EnableMenuItem(GetMenu(hWnd), IDM_MINE_AMOUNT_LV2, MF_GRAYED); break;
	case 3:EnableMenuItem(GetMenu(hWnd), IDM_MINE_AMOUNT_LV3, MF_GRAYED); break;
	case 4:EnableMenuItem(GetMenu(hWnd), IDM_MINE_AMOUNT_LV4, MF_GRAYED); break;
	}

	MineAmount_Lv = target;//����

	ReStartLevel();
	DrawMenuBar(hWnd);			//������ʾ���ڲ˵�
}
void Level1::ChangeFieldLevel(int target)
{
	//����˵���
	switch (Field_Lv)
	{
	case 1:EnableMenuItem(GetMenu(hWnd), IDM_MINEFIELD_LV1, MF_ENABLED); break;
	case 2:EnableMenuItem(GetMenu(hWnd), IDM_MINEFIELD_LV2, MF_ENABLED); break;
	case 3:EnableMenuItem(GetMenu(hWnd), IDM_MINEFIELD_LV3, MF_ENABLED); break;
	case 4:EnableMenuItem(GetMenu(hWnd), IDM_MINEFIELD_LV4, MF_ENABLED); break;
	}
	switch (target)
	{
	case 1:EnableMenuItem(GetMenu(hWnd), IDM_MINEFIELD_LV1, MF_GRAYED); break;
	case 2:EnableMenuItem(GetMenu(hWnd), IDM_MINEFIELD_LV2, MF_GRAYED); break;
	case 3:EnableMenuItem(GetMenu(hWnd), IDM_MINEFIELD_LV3, MF_GRAYED); break;
	case 4:EnableMenuItem(GetMenu(hWnd), IDM_MINEFIELD_LV4, MF_GRAYED); break;
	}
	Field_Lv = target;

	ReStartLevel();//����

	SetWindowPos(hWnd, HWND_TOP, 0, 0, 40 + a_MineField->GetMineField_Width() * spacing, 146 + a_MineField->GetMineField_Length() * spacing, SWP_NOMOVE);
	graphics->ResizeRenderTarget(hWnd);

	DrawMenuBar(hWnd);			//������ʾ���ڲ˵�
}
void Level1::LBUTTONDOWN(int mouseX, int mouseY)
{
	//��������
	if (!a_MineField->GetExplode())
		if ((mouseX - DrawX) > 0 && (mouseX - DrawX) < spacing * a_MineField->GetMineField_Width() && (mouseY - 60 - DrawY) > 0 && (mouseY - 60 - DrawY) < spacing * a_MineField->GetMineField_Length())
			if (a_MineField->GetPlayerPoint((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing) != 1)//�ǹ���״̬
			{
				if (a_MineField->GetPlayerPoint((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing) == 2)//������
					a_MineField->cancelFlag();


				a_MineField->Player_act((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing, 1);

				//�˴��ж���ɢ���Ƿ�ը
				//��ը��
				if (a_MineField->GetMinePoint((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing) == -1)
					a_MineField->ItExplode();
				else
				{
					if (a_MineField->GetMinePoint((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing) == 0)//��ɢ
						a_MineField->Spread((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing);

					if (a_MineField->Flag_left() == 0 && a_MineField->judgeWin())//�˴��ж��Ƿ��ʤ
						MessageBox(hWnd, L"�ɹ����ף�", L"��ϲ��", 0);
				}
			}

	//�����ͼ���¿�ʼ
	switch (Field_Lv)
	{
	case 1:
	case 2:
	case 3:
		if (79 + Field_Lv * 90 < mouseX && mouseX < 127 + Field_Lv * 90 && DrawY < mouseY && mouseY < DrawY + sprite1_height)ReStartLevel();
		break;
	case 4:
		if (169 + Field_Lv * 90 < mouseX && mouseX < 217 + Field_Lv * 90 && DrawY < mouseY && mouseY < DrawY + sprite1_height)ReStartLevel();
		break;
	}
}
void Level1::RBUTTONDOWN(int mouseX, int mouseY)
{
	if (!a_MineField->GetExplode())
		if ((mouseX - DrawX) > 0 && (mouseX - DrawX) < spacing * a_MineField->GetMineField_Width() && (mouseY - 60 - DrawY) > 0 && (mouseY - 60 - DrawY) < spacing * a_MineField->GetMineField_Length())
		{
			if (a_MineField->GetPlayerPoint((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing) == 2)//ȥ������
			{
				a_MineField->Player_act((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing, 0);
				a_MineField->cancelFlag();
			}
			else
				if (a_MineField->Flag_left() > 0 && a_MineField->GetPlayerPoint((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing) != 1)
				{
					a_MineField->Player_act((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing, 2);
					a_MineField->useFlag();

					if (a_MineField->Flag_left() == 0 && a_MineField->judgeWin())//�˴��ж��Ƿ��ʤ
						MessageBox(hWnd, L"�ɹ����ף�", L"��ϲ��", 0);
				}
		}
}
void Level1::MBUTTONDOWN(int mouseX, int mouseY)
{
	if (!a_MineField->GetExplode())
		if ((mouseX - DrawX) > 0 && (mouseX - DrawX) < spacing * a_MineField->GetMineField_Width() && (mouseY - 60 - DrawY) > 0 && (mouseY - 60 - DrawY) < spacing * a_MineField->GetMineField_Length())
		{
			switch (a_MineField->GetPlayerPoint((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing))
			{
			case 2://����
				a_MineField->cancelFlag();
			case 0://����״̬
				a_MineField->Player_act((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing, 3);
				break;
			case 3:
				a_MineField->Player_act((mouseY - 60 - DrawY) / spacing, (mouseX - DrawX) / spacing, 0);
			}
		}
}
void Level1::ReStartLevel()
{
	a_MineField->~Gamemap();
	a_MineField = new Gamemap(Field_Lv, MineAmount_Lv);
}
void Level1::Cheating()
{
	a_MineField->ShowMines();
}
void Level1::ChangeDifficulty(int degree)
{
	ChangeMineLevel(degree);
}
void Level1::ChangeSize(int degree)
{
	ChangeFieldLevel(degree);
}
