#include "PVEselectlevelScene.h"



PVEselectlevelScene::PVEselectlevelScene(int maxlevel)
{
	this->maxlevel = maxlevel;
	level = 1;
	n = -1;

	isover = false;
}


PVEselectlevelScene::~PVEselectlevelScene()
{
}

void PVEselectlevelScene::onKey(key_msg key)
{

	if (key.key == key_esc&&key.msg == key_msg_down)
	{
		isover = true;
		n = -1;
	}

	if ((key.key == key_left|| key.key == key_A)&&key.msg == key_msg_down)
		if (level > 1)
			level--;

	if ((key.key == key_right || key.key == key_D) && key.msg == key_msg_down)
		if (level <20)
			level++;

	if ((key.key == key_space || key.key == key_enter) && key.msg == key_msg_down)
		if (level <= maxlevel)
		{
			isover = true;
			n =level;
		}

}

void PVEselectlevelScene::update()
{
}

void PVEselectlevelScene::render()
{
	picture.clear();

	rend_map();
	rend_information();

	picture.rend();
}

void PVEselectlevelScene::rend_map()
{
	int x, y;
	x = (Win_W - 300) / 2;
	y = 150;

	switch (level)
	{
	case 1:
		putimage(x, y, picture.map_PVE_1);
		break;
	case 2:
		putimage(x, y, picture.map_PVE_2);
		break;
	case 3:
		putimage(x, y, picture.map_PVE_3);
		break;
	case 4:
		putimage(x, y, picture.map_PVE_4);
		break;
	case 5:
		putimage(x, y, picture.map_PVE_5);
		break;
	case 6:
		putimage(x, y, picture.map_PVE_6);
		break;
	case 7:
		putimage(x, y, picture.map_PVE_7);
		break;
	case 8:
		putimage(x, y, picture.map_PVE_8);
		break;
	case 9:
		putimage(x, y, picture.map_PVE_9);
		break;
	case 10:
		putimage(x, y, picture.map_PVE_10);
		break;
	case 11:
		putimage(x, y, picture.map_PVE_11);
		break;
	case 12:
		putimage(x, y, picture.map_PVE_12);
		break;
	case 13:
		putimage(x, y, picture.map_PVE_13);
		break;
	case 14:
		putimage(x, y, picture.map_PVE_14);
		break;
	case 15:
		putimage(x, y, picture.map_PVE_15);
		break;
	case 16:
		putimage(x, y, picture.map_PVE_16);
		break;
	case 17:
		putimage(x, y, picture.map_PVE_17);
		break;
	case 18:
		putimage(x, y, picture.map_PVE_18);
		break;
	case 19:
		putimage(x, y, picture.map_PVE_19);
		break;
	case 20:
		putimage(x, y, picture.map_PVE_20);
		break;
	default:
		break;
	}

	if (level > maxlevel)
		putimage_alphablend(NULL, picture.map_lock, x, y, 200);

}

void PVEselectlevelScene::rend_information()
{
	setcolor(WHITE);
	setfont(50, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy((Win_W-200)/2,60, "选择关卡");

	setfont(40, 0, "楷体");
	char str[10];
	sprintf(str, "第%d关",level);
	outtextxy((Win_W - 120) / 2, Win_H-120, str);

	if (level != 1)
		putimage_withalpha(NULL,picture.player_1_A,150,300);
	if (level != 20)
		putimage_withalpha(NULL, picture.player_1_D, 600, 300);
}

int PVEselectlevelScene::get_n()
{
	return n;
}

bool PVEselectlevelScene::isOver()
{
	return isover;
}
