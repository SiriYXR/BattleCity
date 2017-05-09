#include "isover_design.h"


struct isover_design_menber
{
	Picture picture;

	bool isover;
	int cursor_x, cursor_y;
	int w, h;
};

isover_design::isover_design()
{
	member = new isover_design_menber;
	member->isover = false;
	member->w = 300;
	member->h = 80;
	member->cursor_x = (Win_W - member->w) / 2+6;
	member->cursor_y = (Win_H - member->h) / 2+6;
}


isover_design::~isover_design()
{
	delete member;
}

void isover_design::onKey(key_msg key)
{
	if (key.key == key_right&&key.msg == key_msg_down&&member->cursor_x < ((Win_W - member->w) / 2 + 6 + ((member->w - 12) / 3) * 2))
	{
		member->cursor_x += ((member->w - 12) / 3+6);
		music.mu_Switch();
	}
	else if (key.key == key_left&&key.msg == key_msg_down&&member->cursor_x >((Win_W - member->w) / 2 + 6))
	{
		member->cursor_x -= ((member->w - 12) / 3+6);
		music.mu_Switch();
	}

	if (key.key == key_esc&&key.msg == key_msg_down)
	{
		member->isover = true;
	}
}

void isover_design::update()
{
}

void isover_design::render()
{
	rend_mainface();
	rendCursor();

}
void isover_design::rend_mainface()
{
	PIMAGE blackbar = newimage(Win_W, Win_H);
	putimage_alphablend(NULL, blackbar, 0, 0, 200);

	rend_bar((Win_W - member->w) / 2, (Win_H - member->h) / 2, member->w + 12, member->h);
	rend_bar((Win_W - member->w) / 2 + 8, (Win_H - member->h) / 2 + 8, (member->w - 24) / 3, member->h - 16, 2);
	rend_bar((Win_W - member->w) / 2 + 14 + (member->w - 12) / 3, (Win_H - member->h) / 2 + 8, (member->w - 24) / 3, member->h - 16, 2);
	rend_bar((Win_W - member->w) / 2 + 20 + ((member->w - 12) / 3) * 2, (Win_H - member->h) / 2 + 8, (member->w - 24) / 3, member->h - 16, 2);

	setcolor(WHITE);
	setfont(30, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(Win_W / 2 - 160, Win_H / 2 - 100, "您修改过的内容还未保存！");
	outtextxy((Win_W - member->w) / 2 + 8 + 8, (Win_H - member->h) / 2 + 8 + 15, "保 存");
	outtextxy((Win_W - member->w) / 2 + 16 + (member->w - 12) / 3 , (Win_H - member->h) / 2 + 8 + 15, "不保存");
	outtextxy((Win_W - member->w) / 2 + 24 + ((member->w - 12) / 3) * 2 + 8, (Win_H - member->h) / 2 + 8 + 15, "取 消");

	delimage(blackbar);
}

void isover_design::rendCursor()
{
	rend_bar(member->cursor_x, member->cursor_y, (member->w - 24) / 3+4, member->h - 12, 6, EGERGB(0x00, 0xFF, 0xFF));
}

bool isover_design::isOver()
{
	return member->isover;
}

int isover_design::getCursor_x()
{
	return member->cursor_x;
}

int isover_design::getCursor_y()
{
	return member->cursor_y;
}

int isover_design::get_w()
{
	return member->w;
}

void isover_design::rend_bar(int x, int y, int w, int h, int n, color_t color)
{
	setfillcolor(color);
	bar(x - n, y - n, x + w + n, y);
	bar(x - n, y + h, x + w + n, y + h + n);
	bar(x - n, y - n, x, y + h + n);
	bar(x + w + n, y - n, x + w, y + h + n);
}
