#include "escScene.h"



escScene::escScene()
{
	isover = false;
	state = false;
	w = 300;
	h = 80;
	cursor_x = (Win_W - w) / 2 + 6;
	cursor_y = (Win_H - h) / 2 + 6;
}


escScene::~escScene()
{
}

void escScene::onKey(key_msg key)
{
	if ((key.key == key_right|| key.key == key_D)&&key.msg == key_msg_down&&cursor_x < ((Win_W - w) / 2 + 6 + (w - 12) / 2))
	{
		cursor_x += ((w - 12) / 2 + 10);
		music.mu_Switch();
	}
	else if ((key.key == key_left|| key.key == key_A)&&key.msg == key_msg_down&& cursor_x > ((Win_W - w) / 2 + 6))
	{
		cursor_x -= ((w - 12) / 2 + 10);
		music.mu_Switch();
	}

	if ((key.key == key_enter || key.key == key_space) &&key.msg == key_msg_down)
		if (cursor_x < ((Win_W - w) / 2 + 6 + (w - 12) / 2))
		{
			state = false;
			isover = true;
		}
		else
		{
			state = true;
			isover = true;
		}

	if (key.key == key_esc&&key.msg == key_msg_down)
	{
		state = false;
		isover = true;
	}
}

void escScene::update()
{

}

void escScene::render()
{
	rend_mainface();
	rendCursor();
}

bool escScene::isOver()
{
	return isover;
}

void escScene::rend_mainface()
{
	PIMAGE blackbar = newimage(Win_W, Win_H);
	putimage_alphablend(NULL, blackbar, 0, 0, 200);
	delimage(blackbar);

	rend_bar((Win_W - w) / 2, (Win_H - h) / 2, w + 12, h);
	rend_bar((Win_W - w) / 2 + 8, (Win_H - h) / 2 + 8, (w - 12) / 2, h - 16, 2);
	rend_bar((Win_W - w) / 2 + 18 + (w - 12) / 2, (Win_H - h) / 2 + 8, (w - 12) / 2, h - 16, 2);

	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	setfont(30, 0, "楷体");

	outtextxy((Win_W - w) / 2 + 13, (Win_H - h) / 2 + 25, "继续游戏");
	outtextxy((Win_W - w) / 2 + 19 + (w - 8) / 2, (Win_H - h) / 2 + 25, "退出游戏");
}

void escScene::rendCursor()
{
	rend_bar(cursor_x, cursor_y, (w - 12) / 2 + 4, h - 12, 6, EGERGB(0x00, 0xFF, 0xFF));
}

void escScene::rend_bar(int x, int y, int w, int h, int n, color_t color)
{
	setfillcolor(color);
	bar(x - n, y - n, x + w + n, y);
	bar(x - n, y + h, x + w + n, y + h + n);
	bar(x - n, y - n, x, y + h + n);
	bar(x + w + n, y - n, x + w, y + h + n);
}
