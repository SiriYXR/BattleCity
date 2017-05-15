#include "PVPselectlevelScene.h"



PVPselectlevelScene::PVPselectlevelScene()
{
	level = 1;
	n = -1;

	isover = false;
}


PVPselectlevelScene::~PVPselectlevelScene()
{
}

void PVPselectlevelScene::onKey(key_msg key)
{
	if (key.key == key_esc&&key.msg == key_msg_down)
	{
		isover = true;
		n = -1;
	}

	if ((key.key == key_left || key.key == key_A) && key.msg == key_msg_down)
		if (level > 1)
			level--;

	if ((key.key == key_right || key.key == key_D) && key.msg == key_msg_down)
		if (level <5)
			level++;

	if ((key.key == key_space || key.key == key_enter) && key.msg == key_msg_down)
		{
			isover = true;
			n = level;
		}
}

void PVPselectlevelScene::update()
{
	
}

void PVPselectlevelScene::render()
{
	picture.clear();

	rend_map();
	rend_information();

	picture.rend();
	
}

void PVPselectlevelScene::rend_map()
{
	int x, y;
	x = (Win_W - 300) / 2;
	y = 150;

	switch (level)
	{
	case 1:
		putimage(x, y, picture.map_PVP_1);
		break;
	case 2:
		putimage(x, y, picture.map_PVP_2);
		break;
	case 3:
		putimage(x, y, picture.map_PVP_3);
		break;
	case 4:
		putimage(x, y, picture.map_PVP_4);
		break;
	case 5:
		putimage(x, y, picture.map_PVP_5);
		break;
	default:
		break;
	}
}

void PVPselectlevelScene::rend_information()
{
	setcolor(WHITE);
	setfont(50, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy((Win_W - 200) / 2, 60, "选择关卡");

	setfont(40, 0, "楷体");
	char str[10];
	sprintf(str, "第%d关", level);
	outtextxy((Win_W - 120) / 2, Win_H - 120, str);

	if (level != 1)
		putimage_withalpha(NULL, picture.player_1_A, 150, 300);
	if (level != 20)
		putimage_withalpha(NULL, picture.player_1_D, 600, 300);
}

int PVPselectlevelScene::get_n()
{
	return n;
}

bool PVPselectlevelScene::isOver()
{
	return isover;
}
